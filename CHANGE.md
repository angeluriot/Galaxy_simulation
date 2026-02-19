# CHANGELOG

## 2026-02-18

### Added

* Matter distribution selector for Janus initialization:
  * `Core + halo`
  * `Random mix`
  * `Split on X`
* `Positive Ratio` parameter for random matter assignment.
* `Core + halo` extra-density slider:
  * `Extra negative density inside core` in `[0, 1]`
* Batch simulation mode in executable:
  * `--batch-steps N`
  * `--snapshots K`
  * `--output-dir DIR`
  * `--config FILE` (load one config line)
  * `--batch-config FILE` (run one simulation per line)
* Final snapshot export from multiple camera angles in batch mode.
* Run helper scripts:
  * `run_sim.sh`
  * `run_batch.sh`
  * `run_batch.sh --batch-config batch_configs/example.batchcfg`
  * `run_batch.sh` automatically uses root `batch_jobs.cfg` when present
* In-app batch export UI:
  * set config output path
  * append current `SIMCFG` line directly from the menu
* Root-level batch job template file: `batch_jobs.cfg`
* Camera preset in config lines:
  * `camera_view=isometric|top`
* Root-level interactive startup config file: `simulation.cfg`

### Changed

* Rendering color convention aligned with Janus interpretation:
  * positive/regular mass rendered in blue
  * negative mass rendered in red
* Janus post-process shader simplified to preserve star channel data.
* Core+halo star assignment logic updated to match model:
  * positive stars initialized in core sphere (`Type Diameter`)
  * halo stars initialized as negative (outside core)
  * `Extra negative density inside core` controls core negative injection in `[0, 1]`
* Startup logs now print assigned counts (`stars+`, `stars-`, `core`, `halo`).
* Restart logs now print full one-line configs (`SIMCFG key=value ...`) for copy/paste into batch files.

### Performance

* OpenCL command queue is initialized once and reused.
* Per-frame scalar parameters are now updated in existing OpenCL buffers.
* Removed unnecessary per-frame acceleration readback from GPU to CPU.
* OpenGL VBO is no longer reallocated every frame.
* Star type data is uploaded once at initialization/restart.
* Integer star type vertex attribute now uses `glVertexAttribIPointer`.

### Usage

Interactive run:

```bash
./build/Galaxy_simulation
bash run_sim.sh
```

Batch run:

```bash
./build/Galaxy_simulation --batch-steps 5000 --snapshots 4 --output-dir outputs/run_001
bash run_batch.sh 5000 4 outputs/run_001
bash run_batch.sh --batch-config batch_configs/example.batchcfg
```

### Validation checklist

* Build succeeds: `bash unix_run.sh`.
* Positive stars appear blue, negative stars appear red.
* Batch run generates `snapshot_*.png` in output directory.
* Runtime improves versus previous version for same star count and parameters.

### Known limitation

* Batch mode still requires an OpenGL/X11 context (not true headless yet).
