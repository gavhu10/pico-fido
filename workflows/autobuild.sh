#!/bin/bash

git submodule update --init --recursive

idf.py set-target esp32s3
idf.py all
mkdir -p release
cd build
esptool.py --chip ESP32-S3 merge_bin -o ../release/pico_fido_esp32-s3.bin @flash_args

