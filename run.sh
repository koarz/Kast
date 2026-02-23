#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/config.sh"

MODE="${COMPILE_TYPE:-release}"
OUTPUT_DIR="$SCRIPT_DIR/output"
BUILD_BIN="$SCRIPT_DIR/build/linux/x86_64/$MODE"
mkdir -p "$OUTPUT_DIR"

xmake config --mode="$MODE" -y || exit 1

for param in "$@"; do
if [ "${param}" = "help" ]; then
    echo "db      build and run Kast"
elif [ "${param}" = "db" ]; then
    xmake build Kast || exit 1
    cp "$BUILD_BIN/Kast" "$OUTPUT_DIR/Kast"
    "$OUTPUT_DIR/Kast"
fi
done
