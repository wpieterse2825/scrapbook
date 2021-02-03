#!/usr/bin/env bash

# --- begin runfiles.bash initialization v2 ---
# Copy-pasted from the Bazel Bash runfiles library v2.
set -uo pipefail; f=bazel_tools/tools/bash/runfiles/runfiles.bash
source "${RUNFILES_DIR:-/dev/null}/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "${RUNFILES_MANIFEST_FILE:-/dev/null}" | cut -f2- -d' ')" 2>/dev/null || \
  source "$0.runfiles/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.exe.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  { echo>&2 "ERROR: cannot find $f"; exit 1; }; f=; set -e
# --- end runfiles.bash initialization v2 ---

export TESTENV_DONT_BAZEL_CLEAN=1

source "$(rlocation "compusim/tools/test/shell/unit_test.bash")" || { echo "unit_test.bash not found!" >&2; exit 1; }
source "$(rlocation "compusim/tools/test/shell/test_environment.bash")" || { echo "test_environment.bash not found!" >&2; exit 1; }

function test_correct() {
    cat > handle.yaml <<'EOF'
---
name: Device
documentation:
    english: Documentation - English
    french: Documentation - French
    spanish: Documentation - Spanish
EOF

    $(rlocation "compusim/idl_compiler/compiler/handle/driver") \
        --input handle.yaml \
        --output handle.bin \
        2>&1 >> $TEST_log || fail "Could not launch compiler driver."

    if [[ $? != 0 ]];
    then
        fail "Command exited with a non-zero status code."
    fi

    if [[ ! -e handle.bin ]];
    then
        fail "Output file not written."
    fi
}

run_suite "Handle compiler driver tests"
