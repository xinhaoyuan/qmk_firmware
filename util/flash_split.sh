#!/bin/bash

set -euo pipefail

DIR="$(dirname $0)"
TARGET="$1"


# "${DIR}/docker_build.sh" "${TARGET}:build"

echo "Flashing the left side in 15s" >&2
sleep 15
pmount sda1
if ! "${DIR}/docker_build.sh" "${TARGET}:uf2-split-left"; then
    echo "Failed to flash the left side. Right side untouched." >&2
    pumount sda1
    exit
fi
pumount sda1

echo "Flashing the right side in 15s" >&2
sleep 15
pmount sda1
if ! "${DIR}/docker_build.sh" "${TARGET}:uf2-split-right"; then
    echo "Failed to flash the right side." >&2
    pumount sda1
    exit
fi
pumount sda1
