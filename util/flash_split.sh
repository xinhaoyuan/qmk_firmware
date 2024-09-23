#!/bin/bash

set -euo pipefail

DIR="$(dirname $0)"
TARGET="$1"


# "${DIR}/docker_build.sh" "${TARGET}:build"

echo "Flashing the left side in 5s" >&2
sleep 5
while ! pmount sda1; do
    echo "Retry to mount sda1 for the left side in 1s" >&2
    sleep 1
done
if ! "${DIR}/docker_build.sh" "${TARGET}:uf2-split-left"; then
    echo "Failed to flash the left side. Right side untouched." >&2
    pumount sda1
    exit
fi
pumount sda1

echo "Flashing the right side in 5s" >&2
sleep 5
while ! pmount sda1; do
    echo "Retry to mount sda1 for the right side in 1s" >&2
    sleep 1
done
if ! "${DIR}/docker_build.sh" "${TARGET}:uf2-split-right"; then
    echo "Failed to flash the right side." >&2
    pumount sda1
    exit
fi
pumount sda1
