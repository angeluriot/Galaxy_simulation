#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if ! command -v sudo >/dev/null 2>&1; then
  echo "Error: sudo is required."
  exit 1
fi

echo "[1/3] Installing system dependencies..."
sudo apt-get update
sudo apt-get install -y \
  git \
  build-essential \
  cmake \
  libglew-dev \
  freeglut3-dev \
  ocl-icd-opencl-dev \
  pocl-opencl-icd \
  xvfb \
  x11vnc \
  fluxbox \
  tmux

echo "[2/3] Building Galaxy_simulation..."
bash "${ROOT_DIR}/unix_run.sh"

echo "[3/3] Done."
echo "Try:"
echo "  bash cloud/run_headless_batch.sh 4000 4 outputs/test_run"
echo "  VNC_PASSWORD=change_me bash cloud/start_live_vnc.sh"
