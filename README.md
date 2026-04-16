# FIDO Cardputer
This project transforms your M5Stack Cardputer into an integrated FIDO Passkey, functioning like a standard USB Passkey for authentication. It builds on the amazing [Pico FIDO](https://github.com/polhenarejos/pico-fido) project. FIDO Cardputer uses the `HID` driver, which is present in all operating systems. It should be detected by all OS and browser applications just like normal USB FIDO keys.


# Building

To build the project, you must have docker and [esptool](https://github.com/espressif/esptool/releases) installed.

First, clone the project.


```
git clone https://github.com/gavhu10/pico-fido
git submodule update --init --recursive
cd pico-fido
```

Then build and flash with these commands:

```bash
docker run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp espressif/idf:release-v5.5 idf.py build

esptool  --before default-reset --after hard-reset write-flash --flash-mode dio \
  --flash-size 4MB --flash-freq 80m 0x0 build/bootloader/bootloader.bin 0x8000 \
  build/partition_table/partition-table.bin 0x20000 build/pico_fido.bin
```

## Credits
FIDO Cardputer is built heavily on [Pico FIDO](https://github.com/polhenarejos/pico-fido) which is made by 
[Pol Henarejos](https://github.com/polhenarejos). It uses the following libraries or portion of code:
- MbedTLS for cryptographic operations.
- TinyUSB for low level USB procedures.
- TinyCBOR for CBOR parsing and formatting.
