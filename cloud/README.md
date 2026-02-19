# Cloud VM workflow (live + batch)

This folder provides a practical way to run Galaxy_simulation on a Linux VM with limited local hardware.

## What this gives you

- Live mode on a VM using a virtual display and VNC.
- Batch mode on a VM using headless rendering via `xvfb`.
- A simple queue processor for many batch config files.

## 1) Provision a VM

Use Ubuntu 22.04/24.04 and at least 4 vCPUs if possible.

On the VM:

```bash
git clone --recurse-submodules <your-repo-url>
cd Galaxy_simulation
bash cloud/setup_ubuntu_vm.sh
```

## 2) Run interactive ("live") mode remotely

Start the app with a virtual X server and VNC:

```bash
cd Galaxy_simulation
VNC_PASSWORD='strong_password_here' bash cloud/start_live_vnc.sh
```

Default settings:

- virtual display `:1`
- VNC port `5901`
- bound to localhost (`VNC_BIND_LOCALHOST=1`) for safer access

Recommended SSH tunnel from your laptop:

```bash
ssh -N -L 5901:127.0.0.1:5901 ubuntu@<vm-public-ip>
```

Then connect your VNC client to `127.0.0.1:5901`.

## 3) Run one batch job headlessly

```bash
cd Galaxy_simulation
bash cloud/run_headless_batch.sh 10000 6 outputs/run_100k
```

Or run from a batch config file:

```bash
bash cloud/run_headless_batch.sh --batch-config batch_configs/example.batchcfg
```

## 4) Process a queue of batch files

Put one `.cfg` file per queued run in `batch_queue/pending/`, then:

```bash
bash cloud/process_batch_queue.sh
```

Files are moved to:

- `batch_queue/done/` on success
- `batch_queue/failed/` on failure

Outputs go to `outputs/queue/<job_name>/`.

## Notes for 100k+ stars

- This project still needs OpenGL context even in batch mode; `xvfb` solves this on headless VMs.
- `LIBGL_ALWAYS_SOFTWARE=1` forces Mesa software rendering; it works but is slower than real GPU.
- For highest star counts, batch mode is generally more stable than keeping interactive live mode running for long periods.
