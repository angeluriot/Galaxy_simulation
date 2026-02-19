#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
QUEUE_DIR="${1:-${ROOT_DIR}/batch_queue/pending}"
DONE_DIR="${2:-${ROOT_DIR}/batch_queue/done}"
FAILED_DIR="${3:-${ROOT_DIR}/batch_queue/failed}"
OUTPUT_ROOT="${4:-${ROOT_DIR}/outputs/queue}"

mkdir -p "${QUEUE_DIR}" "${DONE_DIR}" "${FAILED_DIR}" "${OUTPUT_ROOT}"

shopt -s nullglob
jobs=( "${QUEUE_DIR}"/*.cfg )
shopt -u nullglob

if [[ ${#jobs[@]} -eq 0 ]]; then
  echo "No queued batch files in ${QUEUE_DIR}"
  exit 0
fi

for cfg in "${jobs[@]}"; do
  name="$(basename "${cfg}" .cfg)"
  out_dir="${OUTPUT_ROOT}/${name}"
  echo "Processing ${cfg}"
  if bash "${ROOT_DIR}/cloud/run_headless_batch.sh" --batch-config "${cfg}" 2000 4 "${out_dir}"; then
    mv "${cfg}" "${DONE_DIR}/"
    echo "Done: ${name}"
  else
    mv "${cfg}" "${FAILED_DIR}/"
    echo "Failed: ${name}"
  fi
done
