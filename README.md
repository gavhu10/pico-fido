# FIDO Cardputer
This project transforms your M5Stack Cardputer into an integrated FIDO Passkey,
functioning like a standard USB Passkey for authentication.
It builds on the amazing [Pico FIDO](https://github.com/polhenarejos/pico-fido) project.
FIDO Cardputer uses the `HID` driver, which is present in all operating systems.
It should be detected by all OS and browser applications just like normal USB FIDO keys.


# Building

To build the project, you must have docker and [esptool](https://github.com/espressif/esptool/releases) installed.

First, clone the project.


```sh
git clone https://github.com/gavhu10/FIDO-Cardputer
cd FIDO-Cardputer
git submodule update --init --recursive
```

Then build and flash with these commands:

>[!NOTE]
>You may have to run docker as root.

```sh
docker run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp espressif/idf:release-v5.5 \
  idf.py set-target esp32-s3
docker run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp espressif/idf:release-v5.5 \
  idf.py build

esptool --flash-size 4MB --flash-freq 80m 0x0 build/bootloader/bootloader.bin 0x8000 \
  build/partition_table/partition-table.bin 0x20000 build/FIDO-Cardputer.bin
```

I have not managed to get it to work with M5 Launcher yet. However, YMMV.

## Credits
FIDO Cardputer is built heavily on [Pico FIDO](https://github.com/polhenarejos/pico-fido) 
and started of as a fork of it. 
Pico FIDO is made by [Pol Henarejos](https://github.com/polhenarejos)
and uses the following libraries or portions of code:
- MbedTLS for cryptographic operations.
- TinyUSB for low level USB procedures.
- TinyCBOR for CBOR parsing and formatting.
- M5Unified and a ported version of M5Cardputer 1.1.1 for IO
