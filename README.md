# Galaxy simulation

![Release](https://img.shields.io/badge/Release-v4.0-blueviolet)
![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)
![Libraries](https://img.shields.io/badge/Libraries-Dimension3D_OpenCL-00cf2c)
![Size](https://img.shields.io/badge/Size-204Mo-f12222)
![Open Source](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)

<br/>

This repository contains the source code of an n-body type simulation using GPU acceleration. It is able to simulate galaxies, galaxy collisions and expanding universes. It has a menu to change the settings and an interactive camera.

<br/>

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_1.png" width="700">
</p>

<br/>

# Summary

* **[Summary](#summary)**
* **[Video](#video)**
* **[Features](#features)**
* **[Build](#build)**
	* [Linux](#linux)
* **[Install](#install)**
	* [Skeleton project install](#skeleton-project-install)
	* [Additionnal dependecies](#additionnal-dependecies)
* **[Releases](#releases)**
* **[Tests](#tests)**
	* [A unique galaxy](#a-unique-galaxy)
	* [Mixing 2 different types of stars](#mixing-2-different-types-of-stars)
	* [Two galaxies colliding](#two-galaxies-colliding)
	* [Universe simulations](#universe-simulations)
* **[Credits](#credits)**

<br/>

# Video

Here is a video explaining how the algorithm works : [<u>**Simuler 1 000 000 de Galaxies 🌌**</u>](https://www.youtube.com/watch?v=dFqjqRUWCus).

<br/>

# Features

* A menu to change the settings of the simulation

* A camera that you can control with your mouse and your wheel

* It can simulate a unique galaxy :

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_2.png" width="500">
</p>

* It can also simulate a collision between two galaxies :

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_3.png" width="500">
</p>

* And it can simulate an entire expanding universe :

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_4.png" width="500">
</p>

<br/>

# Build

## Linux
```sh
./unix_launch.sh -D CMAKE_BUILD_TYPE=Release
```

# Install


### Skeleton project install

This repository is based on my [**Graphics skeleton project**](https://github.com/angeluriot/Graphics_skeleton), so go see its [**install**](https://github.com/angeluriot/Graphics_skeleton#install) part first.

### Additionnal dependecies

Then, you will also need the [**OpenCL**](https://www.khronos.org/opencl/) library.

<br/>

# Releases

If you just want to test the program without editing the source code, go see the [**Releases**](https://github.com/angeluriot/Galaxy_simulation/releases).

<br/>

# Tests

### A unique galaxy

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_5.png" width="500">
</p>

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_6.png" width="500">
</p>

<br/>

### Mixing 2 different types of stars

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_7.png" width="500">
</p>

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_8.png" width="500">
</p>

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_9.png" width="500">
</p>

<br/>

### Two galaxies colliding

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_10.png" width="500">
</p>

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_11.png" width="500">
</p>

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_12.png" width="500">
</p>

<br/>

### Universe simulations

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_14.png" width="500">
</p>

<p align="center">
	<img src="https://www.angeluriot.com/storage/images/galaxy_13.png" width="500">
</p>

<br/>

# Credits

* [**Angel Uriot**](https://github.com/angeluriot) : Creator of the project.
