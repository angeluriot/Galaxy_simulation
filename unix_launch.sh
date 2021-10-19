#!/usr/bin/env bash

cmake -S . -B build -G Ninja "$*"

ninja -C build
