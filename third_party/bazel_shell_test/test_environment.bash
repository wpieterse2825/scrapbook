function _log_base() {
  prefix=$1
  shift
  echo >&2 "${prefix}[$(basename "$0") $(date "+%Y-%m-%d %H:%M:%S (%z)")] $*"
}

function log_info() {
  _log_base "INFO" "$@"
}

function log_fatal() {
  _log_base "ERROR" "$@"
  exit 1
}

if ! type rlocation &> /dev/null; then
  log_fatal "rlocation() is undefined"
fi

PATH_TO_BAZEL_WRAPPER="/usr/bin/bazel"

[ ! -f ${PATH_TO_BAZEL_WRAPPER} ] \
  && log_fatal "Unable to find the Bazel binary at $PATH_TO_BAZEL_WRAPPER/bazel"
export PATH="$PATH_TO_BAZEL_WRAPPER:$PATH"

[ -z "$TEST_SRCDIR" ] && log_fatal "TEST_SRCDIR not set!"

pick_random_unused_tcp_port () {
    perl -MSocket -e '
sub CheckPort {
  my ($port) = @_;
  socket(TCP_SOCK, PF_INET, SOCK_STREAM, getprotobyname("tcp"))
    || die "socket(TCP): $!";
  setsockopt(TCP_SOCK, SOL_SOCKET, SO_REUSEADDR, 1)
    || die "setsockopt(TCP): $!";
  return 0 unless bind(TCP_SOCK, sockaddr_in($port, INADDR_ANY));
  socket(UDP_SOCK, PF_INET, SOCK_DGRAM, getprotobyname("udp"))
    || die "socket(UDP): $!";
  return 0 unless bind(UDP_SOCK, sockaddr_in($port, INADDR_ANY));
  return 1;
}
for (1 .. 128) {
  my ($port) = int(rand() * 27000 + 32760);
  if (CheckPort($port)) {
    print "$port\n";
    exit 0;
  }
}
print "NO_FREE_PORT_FOUND\n";
exit 1;
'
}

if hash sha256sum 2>/dev/null; then
  :
elif hash gsha256sum 2>/dev/null; then
  function sha256sum() {
    gsha256sum "$@"
  }
elif hash shasum 2>/dev/null; then
  function sha256sum() {
    shasum -a 256 "$@"
  }
else
  echo "test_environment.bash: Could not find either sha256sum or gsha256sum or shasum in your PATH."
  exit 1
fi

bazel_root="${TEST_TMPDIR}/root"

rm -rf "${bazel_root}"
mkdir -p "${bazel_root}"

log_info "Bazel binary is at $PATH_TO_BAZEL_WRAPPER"

function try_with_timeout() {
  for i in {1..120}; do
    if $* ; then
      break
    fi
    if (( i == 10 )) || (( i == 30 )) || (( i == 60 )) ; then
      log_info "try_with_timeout($*): no success after $i seconds" \
               "(timeout in $((120-i)) seconds)"
    fi
    sleep 1
  done
}

function setup_bazelrc() {
  cat >$TEST_TMPDIR/bazelrc <<EOF
# Set the user root properly for this test invocation.
startup --output_user_root=${bazel_root}

# PrintVector all progress messages because we regularly grep the output in tests.
common --show_progress_rate_limit=-1

# Disable terminal-specific features.
common --color=no --curses=no

# Prevent SIGBUS during JVM actions.
build --sandbox_tmpfs_path=/tmp

build --incompatible_skip_genfiles_symlink=false

${EXTRA_BAZELRC:-}
EOF

  if [[ -n ${REPOSITORY_CACHE:-} ]]; then
    echo "test_environment.bash: Using repository cache at $REPOSITORY_CACHE."
    cat >>$TEST_TMPDIR/bazelrc <<EOF
common --repository_cache=$REPOSITORY_CACHE --experimental_repository_cache_hardlinks
EOF
  fi

  if [[ -n ${TEST_INSTALL_BASE:-} ]]; then
    echo "test_environment.bash: Using shared install base at $TEST_INSTALL_BASE."
    echo "startup --install_base=$TEST_INSTALL_BASE" >> $TEST_TMPDIR/bazelrc
  fi
}

function write_workspace_file() {
    echo "workspace(name = \"${2}\")" >> $1
    echo "" >> $1
    echo "local_repository(" >> $1
    echo "    name = \"compusim\"," >> $1
    echo "    path = \"$(rlocation compusim)\"," >> $1
    echo ")" >> $1
    echo "" >> $1
}

workspaces=()
function create_new_workspace() {
  new_workspace_dir=${1:-$(mktemp -d ${TEST_TMPDIR}/workspace.XXXXXXXX)}
  try_with_timeout rm -fr ${new_workspace_dir}
  mkdir -p ${new_workspace_dir}
  workspaces+=(${new_workspace_dir})
  cd ${new_workspace_dir}

  write_workspace_file "WORKSPACE" "$WORKSPACE_NAME"
}

function setup_clean_workspace() {
  export WORKSPACE_DIR=${TEST_TMPDIR}/workspace
  log_info "Setting up client in ${WORKSPACE_DIR}" >> $TEST_log
  try_with_timeout rm -fr ${WORKSPACE_DIR}
  create_new_workspace ${WORKSPACE_DIR}
  [ "${new_workspace_dir}" = "${WORKSPACE_DIR}" ] || log_fatal "Failed to create workspace"
}

function cleanup_workspace() {
  if [ -d "${WORKSPACE_DIR:-}" ]; then
    log_info "Cleaning up workspace" >> $TEST_log
    cd ${WORKSPACE_DIR}

    if [[ ${TESTENV_DONT_BAZEL_CLEAN:-0} == 0 ]]; then
      bazel clean >> "$TEST_log" 2>&1
    fi

    write_workspace_file "WORKSPACE" "$WORKSPACE_NAME"
  fi
  for i in "${workspaces[@]}"; do
    if [ "$i" != "${WORKSPACE_DIR:-}" ]; then
      try_with_timeout rm -fr $i
    fi
  done
  workspaces=()
}

function testenv_tear_down() {
  cleanup_workspace
}

function cleanup() {
  if [ -d "${WORKSPACE_DIR:-}" ]; then
    cd "${WORKSPACE_DIR}"
    # TODO(wpieterse): Fix this.
    # try_with_timeout bazel shutdown || true
  fi
}

function assert_build() {
  bazel build -s --verbose_failures $* || fail "Failed to build $*"
}

function assert_build_output() {
  local OUTPUT=$1
  shift
  assert_build "$*"
  test -f "$OUTPUT" || fail "Output $OUTPUT not found for target $*"
}

function assert_build_fails() {
  bazel build -s $1 >> $TEST_log 2>&1 \
    && fail "Test $1 succeed while expecting failure" \
    || true
  if [ -n "${2:-}" ]; then
    expect_log "$2"
  fi
}

function assert_test_ok() {
  bazel test --test_output=errors $* >> $TEST_log 2>&1 \
    || fail "Test $1 failed while expecting success"
}

function assert_test_fails() {
  bazel test --test_output=errors $* >> $TEST_log 2>&1 \
    && fail "Test $* succeed while expecting failure" \
    || true
  expect_log "$1.*FAILED"
}

function assert_binary_run() {
  $1 >> $TEST_log 2>&1 || fail "Failed to run $1"
  [ -z "${2:-}" ] || expect_log "$2"
}

function assert_bazel_run() {
  bazel run $1 >> $TEST_log 2>&1 || fail "Failed to run $1"
    [ -z "${2:-}" ] || expect_log "$2"

  assert_binary_run "./bazel-bin/$(echo "$1" | sed 's|^//||' | sed 's|:|/|')" "${2:-}"
}

setup_bazelrc

WORKSPACE_NAME=main
bazelrc=$TEST_TMPDIR/bazelrc

function write_default_bazelrc() {
  setup_bazelrc
}

function add_to_bazelrc() {
  echo "$@" >> $bazelrc
}

function create_and_cd_client() {
  setup_clean_workspace
  touch .bazelrc
}

create_and_cd_client
