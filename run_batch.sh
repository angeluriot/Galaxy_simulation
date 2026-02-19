#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEFAULT_BATCH_CONFIG="${ROOT_DIR}/batch_jobs.cfg"

if [[ "${1:-}" == "--batch-config" && -n "${2:-}" ]]; then
  BATCH_CONFIG="${2}"
  shift 2
  STEPS="${1:-2000}"
  SNAPSHOTS="${2:-4}"
  OUT_DIR="${3:-outputs}"
else
  if [[ -f "${DEFAULT_BATCH_CONFIG}" ]]; then
    BATCH_CONFIG="${DEFAULT_BATCH_CONFIG}"
  else
    BATCH_CONFIG=""
  fi
  STEPS="${1:-2000}"
  SNAPSHOTS="${2:-4}"
  OUT_DIR="${3:-outputs}"
fi

if [[ ! -x "${ROOT_DIR}/build/Galaxy_simulation" ]]; then
  bash "${ROOT_DIR}/unix_run.sh"
fi

if [[ -n "${BATCH_CONFIG}" ]]; then
  exec "${ROOT_DIR}/build/Galaxy_simulation" \
    --batch-config "${BATCH_CONFIG}" \
    --batch-steps "${STEPS}" \
    --snapshots "${SNAPSHOTS}" \
    --output-dir "${OUT_DIR}"
else
  exec "${ROOT_DIR}/build/Galaxy_simulation" \
    --batch-steps "${STEPS}" \
    --snapshots "${SNAPSHOTS}" \
    --output-dir "${OUT_DIR}"
fi
