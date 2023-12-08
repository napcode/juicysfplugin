#!/bin/bash

# sudo pacman -S juce libvorbis flac libogg fluidsynth cmake pkg-config

cmake -S . \
    -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
#    -DCMAKE_C_COMPILER=clang \
#    -DCMAKE_CXX_COMPILER=clang++ \
#    -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=mold" \
#    -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=mold" \
ninja -C build \
#    --verbose