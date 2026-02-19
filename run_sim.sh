#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEFAULT_SIM_CONFIG="${ROOT_DIR}/simulation.cfg"

if [[ ! -x "${ROOT_DIR}/build/Galaxy_simulation" ]]; then
  bash "${ROOT_DIR}/unix_run.sh"
fi

if [[ $# -eq 0 && -f "${DEFAULT_SIM_CONFIG}" ]]; then
  exec "${ROOT_DIR}/build/Galaxy_simulation" --config "${DEFAULT_SIM_CONFIG}"
else
  exec "${ROOT_DIR}/build/Galaxy_simulation" "$@"
fi
