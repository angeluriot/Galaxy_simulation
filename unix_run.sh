#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"

# Required third-party code is provided via submodules.
git -C "${ROOT_DIR}" submodule update --init --recursive

cmake -G "Unix Makefiles" -B "${BUILD_DIR}" "${ROOT_DIR}" \
  -DOpenCL_INCLUDE_DIR="${ROOT_DIR}/includes" \
  -DOpenCL_LIBRARY="${ROOT_DIR}/includes/CL/lib/libOpenCL.so"

cmake --build "${BUILD_DIR}" -j"$(nproc)"
