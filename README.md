# 🌌 Galaxy simulation

![Release](https://img.shields.io/badge/Release-v4.0-blueviolet)
![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)
![Libraries](https://img.shields.io/badge/Libraries-Dimension3D_OpenCL-00cf2c)
![Size](https://img.shields.io/badge/Size-204Mo-f12222)
![Open Source](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)

<br/>

This repository contains the source code of an n-body type simulation using GPU acceleration. It is able to simulate galaxies, galaxy collisions and expanding universes. It has a menu to change the settings and an interactive camera.

<br/>

⚠️ This repository contains **submodules**, add `--recurse-submodules` when cloning ⚠️

<br/>

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_1.png" width="700">
</p>

<br/>

# 📋 Summary

* **[📋 Summary](#-summary)**
* **[🎥 Video](#-video)**
* **[✨ Features](#-features)**
* **[🐧 Build on Linux](#-build-on-linux)**
* **[🛠️ Install](#%EF%B8%8F-install)**
	* [📦 Dependencies](#-dependencies)
	* [▶️ Build](#%EF%B8%8F-build)
	* [🚀 Run](#-run)
	* [⚙️ Janus + Performance Update](#%EF%B8%8F-janus--performance-update)
	* [🧪 Batch Experiment Workflow](#-batch-experiment-workflow)
	* [✅ Validate Optimized Runs](#-validate-optimized-runs)
	* [☁️ Cloud VM](#%EF%B8%8F-cloud-vm)
	* [🧩 Troubleshooting](#-troubleshooting)
* **[📝 Changes](#-changes)**
* **[🧪 Simulation variants](#-simulation-variants)**
* **[🗓️ Releases](#%EF%B8%8F-releases)**
* **[🧪 Tests](#-tests)**
* **[🙏 Credits](#-credits)**

<br/>

# 🎥 Video

Here is a video explaining how the algorithm works : [<u>**Simuler 1 000 000 de Galaxies 🌌**</u>](https://www.youtube.com/watch?v=dFqjqRUWCus).

<br/>

# ✨ Features

* A menu to change the settings of the simulation

* A camera that you can control with your mouse and your wheel

* It can simulate a unique galaxy :

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_2.png" width="500">
</p>

* It can also simulate a collision between two galaxies :

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_3.png" width="500">
</p>

* And it can simulate an entire expanding universe :

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_4.png" width="500">
</p>

<br/>

# 🐧 Build on Linux

```bash
bash unix_run.sh
```

This script:

* initializes/upgrades git submodules (`--init --recursive`)
* configures CMake with `Unix Makefiles`
* uses the OpenCL include/library shipped in this repository
* builds the executable in `./build`

<br/>

# 🛠️ Install

## 📦 Dependencies

On Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install -y \
  build-essential \
  cmake \
  libglew-dev \
  freeglut3-dev \
  ocl-icd-opencl-dev
```

On Arch Linux:

```bash
sudo pacman -S --needed \
  base-devel \
  cmake \
  glew \
  freeglut \
  opencl-headers \
  ocl-icd \
  clinfo
```

Install at least one OpenCL implementation:

CPU fallback:

```bash
sudo pacman -S --needed pocl
```

NVIDIA GPU:

```bash
sudo pacman -S --needed opencl-nvidia
```

## ▶️ Build

If you clone for the first time:

```bash
git clone --recurse-submodules https://github.com/angeluriot/Galaxy_simulation.git
cd Galaxy_simulation
```

Then build:

```bash
bash unix_run.sh
```

## 🚀 Run

```bash
./build/Galaxy_simulation
```

Shortcut:

```bash
bash run_sim.sh
```

Default root config for normal (interactive) simulation:

* `simulation.cfg`
* when you run `bash run_sim.sh` with no extra arguments, this file is loaded automatically
* set `camera_view=top` in `simulation.cfg` for top-down startup

Batch run (compute N steps, then export final snapshots from multiple angles):

```bash
./build/Galaxy_simulation --batch-steps 2000 --snapshots 4 --output-dir outputs
```

Shortcut:

```bash
bash run_batch.sh 2000 4 outputs
```

Batch file (each line = one simulation job):

```bash
bash run_batch.sh --batch-config batch_configs/example.batchcfg
```

Default root config:

```bash
bash run_batch.sh
```

If `batch_jobs.cfg` exists at repository root, `run_batch.sh` uses it automatically.

## ⚙️ Janus + Performance Update

This branch includes:

* Janus star typing with explicit matter distributions:
  * `Core + halo` (positive center, negative outer region)
  * `Random mix` (positive ratio slider)
  * `Split on X` (two spatial halves)
* `Core + halo` negative density control:
  * `Extra negative density inside core` in `[0, 1]`
  * `0`: core fully positive
  * `1`: core fully negative
  * in `Core + halo` mode: halo stars are always negative
* Janus force multipliers:
  * `Negative Attraction Constant`
  * `Repulsion Constant`
* Color convention:
  * Positive/regular mass: **blue**
  * Negative mass: **red**
* Performance optimizations:
  * Reuse OpenCL command queue
  * Reuse scalar OpenCL buffers and update them in-place
  * Remove unnecessary per-frame acceleration readback
  * Avoid per-frame OpenGL VBO reallocation
  * Upload star type data only at initialization/restart

## 🧪 Batch Experiment Workflow

Use batch mode when you want to simulate many frames and only inspect final results:

```bash
./build/Galaxy_simulation --batch-steps 10000 --snapshots 6 --output-dir outputs/run_001
```

Run many jobs from one file (line-by-line):

```bash
./build/Galaxy_simulation --batch-config batch_configs/example.batchcfg
```

Root-level default batch file:

```bash
./build/Galaxy_simulation --batch-config batch_jobs.cfg
```

Batch file format:

* each non-comment line is one job
* each line is `key=value` tokens
* lines can start with `SIMCFG`
* recommended keys per line:
  * simulation: `simulation_type step smoothing_length interaction_rate nb_stars galaxy_diameter galaxy_thickness galaxies_distance stars_speed black_hole_mass negative_attraction_constant repulsion_constant matter_distribution type_diameter positive_ratio core_extra_negative_density camera_view`
  * batch: `batch_steps snapshots output_dir`
* `camera_view` values:
  * `isometric` (default)
  * `top` (top-down start view)

Recommended workflow:

1. Start interactive mode (`./build/Galaxy_simulation`) and tune settings until the setup is close to your target physics.
2. Click `Restart` after changing any setting under `Applies after restart`.
3. In the menu, use `Batch config export`:
   * set output file path (default: `batch_configs/user.batchcfg`)
   * click `Append current SIMCFG to file`
4. Repeat for each setup you want to queue.
5. Run the whole file with:
   ```bash
   bash run_batch.sh --batch-config batch_configs/user.batchcfg
   ```
6. Compare the exported snapshots across runs.

Choosing initial parameters:

* `Core + halo`:
  * `Type Diameter` defines the positive core sphere.
  * outside that sphere is halo and always negative.
  * `Extra negative density inside core` injects negative stars into the core (`0` to `1`).
  * start around `type_diameter = 0.4 * galaxy_diameter` and extra density `0.1`, then sweep.
* `Random mix`:
  * use `Positive Ratio` (for example `0.2`, `0.5`, `0.8`) to test segregation behavior.
* `Split on X`:
  * good for interface-instability tests.
* For reduced-particle experiments:
  * decrease `nb_stars`
  * compensate dynamics with `Negative Attraction Constant` and `Repulsion Constant`
  * keep `step` and `smoothing_length` stable while you tune force multipliers.

## ✅ Validate Optimized Runs

Before launching cloud runs, validate local behavior:

1. Build and run:
   ```bash
   bash unix_run.sh
   ./build/Galaxy_simulation
   ```
2. Confirm expected visuals:
   * positive stars are blue
   * negative stars are red
3. Confirm initialization counts in terminal logs:
   * `[Init] stars+=... stars-=... core=... halo=...`
   * this lets you verify the real positive/negative assignment for each restart
   * a copy/paste one-line config is printed as:
     `SIMCFG key=value ...`
4. Confirm batch export:
   ```bash
   ./build/Galaxy_simulation --batch-steps 2000 --snapshots 4 --output-dir outputs/check
   ```
5. Compare timing at same parameters before/after optimization.

Notes:

* Batch mode still needs an OpenGL/X11 context on Linux.
* For server VMs without display, use a virtual display (for example `xvfb`) or add a future true headless mode.

## ☁️ Cloud VM

For remote runs when your local machine is limited:

* setup VM dependencies + build: `bash cloud/setup_ubuntu_vm.sh`
* run interactive mode over VNC: `VNC_PASSWORD='change_me' bash cloud/start_live_vnc.sh`
* run headless batch: `bash cloud/run_headless_batch.sh --batch-config batch_configs/example.batchcfg`
* run queued batch files: `bash cloud/process_batch_queue.sh`

Full guide: [`cloud/README.md`](cloud/README.md)

## 📝 Changes

Detailed change log: see [`CHANGE.md`](CHANGE.md).

## 🧩 Troubleshooting

* `Could not find SFML`: make sure submodules are present (`git submodule update --init --recursive`).
* `Could NOT find OpenCL`: use `bash unix_run.sh` (it passes the required OpenCL paths).
* `No platforms found!`: OpenCL loader is present but no OpenCL driver ICD is installed.
  On Arch Linux:
  `sudo pacman -S --needed pocl` (CPU fallback) or install the NVIDIA-matching OpenCL package (for example `opencl-nvidia-580xx` for 580xx drivers).
  Verify with `clinfo`: `Number of platforms` must be at least `1`.
* `Failed to open X11 display`: run from a desktop session with a valid `DISPLAY` variable.

<br/>

# 🧪 Simulation variants

* Add different star types at random in proportion.
* Add different star types from a diameter threshold (current modification).
* Select matter distribution in-app:
  * `Core + halo`: positive core, negative halo
  * `Random mix`: random positive/negative based on ratio
  * `Split on X`: one half positive, one half negative

<br/>

# 🗓️ Releases

If you just want to test the program without editing the source code, go see the [**Releases**](https://github.com/angeluriot/Galaxy_simulation/releases).

<br/>

# 🧪 Tests

### A unique galaxy

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_5.png" width="500">
</p>

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_6.png" width="500">
</p>

<br/>

### Mixing 2 different types of stars

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_7.png" width="500">
</p>

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_8.png" width="500">
</p>

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_9.png" width="500">
</p>

<br/>

### Two galaxies colliding

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_10.png" width="500">
</p>

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_11.png" width="500">
</p>

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_12.png" width="500">
</p>

<br/>

### Universe simulations

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_14.png" width="500">
</p>

<p align="center">
	<img src="https://raw.githubusercontent.com/angeluriot/Galaxy_simulation/master/resources/misc/galaxy_13.png" width="500">
</p>

<br/>

# 🙏 Credits

* [**Angel Uriot**](https://github.com/angeluriot) : Creator of the project.
