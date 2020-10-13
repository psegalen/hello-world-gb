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

./img2gb.exe tileset \
    --output-c-file=../src/logo_rgb.tileset.c \
    --output-header-file=../src/logo_rgb.tileset.h \
    --output-image=../src/logo_rgb.tileset.png \
    --deduplicate \
    --name=LOGO_RGB_TS \
    ./logo/rgb_gb.v2.png

./img2gb.exe tilemap \
    --output-c-file=../src/logo_rgb.tilemap.c \
    --output-header-file=../src/logo_rgb.tilemap.h \
    ../src/logo_rgb.tileset.png \
    --name=LOGO_RGB_TM \
    ./logo/rgb_gb.v2.png

./img2gb.exe tileset \
    --output-c-file=../src/font.tileset.c \
    --output-header-file=../src/font.tileset.h \
    --name=FONT_TS \
    ./font.png
