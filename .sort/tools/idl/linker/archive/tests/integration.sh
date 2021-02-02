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

function test_it_works() {
    echo "IT WORKS!"
}

run_suite "Archive linker integration tests"
