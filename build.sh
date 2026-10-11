#!/bin/bash
gcc batteryInfo.c -O2 -s -o prg_batteryInfo
gcc `pkg-config gtk+-3.0 --cflags` wallpaperSelect.c -O2 -s -o prg_wallpaperSelect `pkg-config gtk+-3.0 --libs`