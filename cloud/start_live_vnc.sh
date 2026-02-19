#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

DISPLAY_NUM="${DISPLAY_NUM:-:1}"
SCREEN_GEOMETRY="${SCREEN_GEOMETRY:-1920x1080x24}"
VNC_PORT="${VNC_PORT:-5901}"
VNC_BIND_LOCALHOST="${VNC_BIND_LOCALHOST:-1}"
SIM_ARGS=("$@")

if ! command -v Xvfb >/dev/null 2>&1; then
  echo "Error: Xvfb not found. Install xvfb first."
  exit 1
fi

if ! command -v x11vnc >/dev/null 2>&1; then
  echo "Error: x11vnc not found. Install x11vnc first."
  exit 1
fi

VNC_AUTH_ARGS=()
if [[ -n "${VNC_PASSWORD:-}" ]]; then
  PASS_FILE="$(mktemp)"
  x11vnc -storepasswd "${VNC_PASSWORD}" "${PASS_FILE}" >/dev/null
  VNC_AUTH_ARGS=(-rfbauth "${PASS_FILE}")
else
  VNC_AUTH_ARGS=(-nopw)
fi

VNC_BIND_ARGS=()
if [[ "${VNC_BIND_LOCALHOST}" == "1" ]]; then
  VNC_BIND_ARGS=(-localhost)
fi

cleanup() {
  set +e
  [[ -n "${SIM_PID:-}" ]] && kill "${SIM_PID}" >/dev/null 2>&1
  [[ -n "${VNC_PID:-}" ]] && kill "${VNC_PID}" >/dev/null 2>&1
  [[ -n "${WM_PID:-}" ]] && kill "${WM_PID}" >/dev/null 2>&1
  [[ -n "${XVFB_PID:-}" ]] && kill "${XVFB_PID}" >/dev/null 2>&1
  [[ -n "${PASS_FILE:-}" ]] && rm -f "${PASS_FILE}"
}
trap cleanup EXIT INT TERM

echo "Starting virtual display ${DISPLAY_NUM} (${SCREEN_GEOMETRY})..."
Xvfb "${DISPLAY_NUM}" -screen 0 "${SCREEN_GEOMETRY}" >/tmp/galaxy_xvfb.log 2>&1 &
XVFB_PID=$!

echo "Starting lightweight window manager..."
DISPLAY="${DISPLAY_NUM}" fluxbox >/tmp/galaxy_fluxbox.log 2>&1 &
WM_PID=$!

echo "Starting VNC server on port ${VNC_PORT}..."
x11vnc \
  -display "${DISPLAY_NUM}" \
  -rfbport "${VNC_PORT}" \
  -forever \
  -shared \
  "${VNC_BIND_ARGS[@]}" \
  "${VNC_AUTH_ARGS[@]}" \
  >/tmp/galaxy_x11vnc.log 2>&1 &
VNC_PID=$!

echo "Launching simulation..."
echo "VNC logs: /tmp/galaxy_x11vnc.log"
echo "Display logs: /tmp/galaxy_xvfb.log"
echo "Window-manager logs: /tmp/galaxy_fluxbox.log"

export DISPLAY="${DISPLAY_NUM}"
export LIBGL_ALWAYS_SOFTWARE="${LIBGL_ALWAYS_SOFTWARE:-1}"
bash "${ROOT_DIR}/run_sim.sh" "${SIM_ARGS[@]}" &
SIM_PID=$!

wait "${SIM_PID}"
