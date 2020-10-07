#!/usr/bin/bash

./img2gb.exe tileset \
    --output-c-file=../src/splashscreen.tileset.c \
    --output-header-file=../src/splashscreen.tileset.h \
    --output-image=../src/splashscreen.tileset.png \
    --deduplicate \
    --name=SPLASH_TS \
    ./splash.png

./img2gb.exe tilemap \
    --output-c-file=../src/splashscreen.tilemap.c \
    --output-header-file=../src/splashscreen.tilemap.h \
    ../src/splashscreen.tileset.png \
    --name=SPLASH_TM \
    ./splash.png
