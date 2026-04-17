#
# This file is part of the Pico FIDO distribution (https://github.com/polhenarejos/pico-fido).
# Copyright (c) 2022 Pol Henarejos.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED ENABLE_POWER_ON_RESET)
    set(ENABLE_POWER_ON_RESET 0)
endif()
if(NOT DEFINED ENABLE_PQC)
    set(ENABLE_PQC 0)
endif()
set(EXTRA_COMPONENT_DIRS
    src/fido
    pico-keys-sdk/config/esp32/components/pico-keys-sdk
    pico-keys-sdk/config/esp32/components/tinycbor
)
if(ENABLE_PQC)
    list(APPEND EXTRA_COMPONENT_DIRS
        pico-keys-sdk/config/esp32/components/mlkem512
        pico-keys-sdk/config/esp32/components/mlkem768
        pico-keys-sdk/config/esp32/components/mlkem1024
    )
endif()
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

include(pico-keys-sdk/cmake/options.cmake)

option(ENABLE_POWER_ON_RESET "Enable/disable power cycle on reset" ON)
configure_bool_option(
    ENABLE_POWER_ON_RESET
    ENABLE_POWER_ON_RESET
    "Power cycle on reset: \t enabled"
    "Power cycle on reset: \t disabled"
)

option(ENABLE_OATH_APP "Enable/disable OATH application" ON)
configure_bool_option(
    ENABLE_OATH_APP
    ENABLE_OATH_APP
    "OATH Application: \t\t enabled"
    "OATH Application: \t\t disabled"
)

option(ENABLE_OTP_APP "Enable/disable OTP application" ON)
configure_bool_option(
    ENABLE_OTP_APP
    ENABLE_OTP_APP
    "OTP Application: \t\t enabled"
    "OTP Application: \t\t disabled"
)

if(ENABLE_OTP_APP OR ENABLE_OATH_APP)
    set(USB_ITF_CCID 1)
    set(USB_ITF_WCID 1)
else()
    set(USB_ITF_CCID 0)
endif()

set(USB_ITF_HID 1)

add_compile_definitions(MANUFACTURER="gavhu10" PRODUCT="FIDO Cardputer")
add_compile_definitions(SERIAL_NUM="11223344" URL="github.com/gavhu10/FIDO-Cardputer")

include(pico-keys-sdk/pico_keys_sdk_import.cmake)


list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/fido.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/files.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cmd_register.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cmd_authenticate.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cmd_version.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_reset.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_get_info.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_make_credential.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/known_apps.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_client_pin.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/credential.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_get_assertion.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_selection.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_cred_mgmt.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_config.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_vendor.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/cbor_large_blobs.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/management.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fido/defs.c
)

if(ENABLE_OATH_APP)
    list(APPEND SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/src/fido/oath.c
    )
endif()

if(ENABLE_OTP_APP)
    list(APPEND SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/src/fido/otp.c
    )
endif()

SET_VERSION(ver_major ver_minor "${CMAKE_CURRENT_LIST_DIR}/src/fido/version.h")
project(FIDO-Cardputer)

set(INCLUDES ${INCLUDES}
    ${CMAKE_CURRENT_LIST_DIR}/src/fido
)

