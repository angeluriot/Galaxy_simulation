#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if ! command -v xvfb-run >/dev/null 2>&1; then
  echo "Error: xvfb-run not found. Install xvfb first."
  exit 1
fi

export LIBGL_ALWAYS_SOFTWARE="${LIBGL_ALWAYS_SOFTWARE:-1}"

exec xvfb-run -a -s "-screen 0 1920x1080x24" \
  bash "${ROOT_DIR}/run_batch.sh" "$@"
