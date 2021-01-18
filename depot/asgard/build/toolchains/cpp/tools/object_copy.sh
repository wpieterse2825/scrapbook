#!/usr/bin/env bash
#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

set -euo pipefail

export PATH=third_party/llvm/bin:$PATH

exec llvm-objcopy "$@"
