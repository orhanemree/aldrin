#!/usr/bin/env bash

# Usage: build.sh <PLATFORM> <EXTENSION_LESS_FILENAME>
#   PLATFORM: [c, wasm]. default = c
# Example: build.sh wasm main

PLATFORM_C="c"
PLATFORM_WASM="wasm"

if [[ "$#" -eq 0 ]]; then
    echo "Error: Input file not provided."
    echo "Usage: build.sh <PLATFORM> <EXTENSION_LESS_FILENAME>"
    echo "    PLATFORM: [c, wasm]. default = c"
    echo "Example: build.sh wasm main"

elif [[ "$#" -eq 1 ]]; then
    set -xe

    # act like normal C program
    clang -Wall -Wextra -ggdb -lm -DPLATFORM_C -o $1 $1.c

else
    if [ "$1" = "$PLATFORM_C" ]; then
        set -xe

        clang -Wall -Wextra -ggdb -lm -DPLATFORM_C -o $2 $2.c
        
    elif [ "$1" = "$PLATFORM_WASM" ]; then
        set -xe

        clang -Wall -Wextra -ggdb -DPLATFORM_WASM --target=wasm32 -o $2.o -c $2.c
        wasm-ld --no-entry --allow-undefined --export-all -o $2.wasm $2.o
        rm $2.o

    else
        echo "Error: Platform not provided."
        echo "Usage: build.sh <PLATFORM> <EXTENSION_LESS_FILENAME>"
        echo "    PLATFORM: [c, wasm]. default = c"
        echo "Example: build.sh wasm main"
    fi
fi