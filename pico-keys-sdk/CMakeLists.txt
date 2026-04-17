#
# This file is part of the Pico Keys SDK distribution (https://github.com/polhenarejos/pico-keys-sdk).
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

cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS src)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(USB_ITF_CCID 1)
set(USB_ITF_WCID 1)
include(cmake/version.cmake)
include(cmake/options.cmake OPTIONAL)
include(pico_keys_sdk_import.cmake)
list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/fs/files.c
    ${CMAKE_CURRENT_LIST_DIR}/src/version.c
)

SET_VERSION(ver_major ver_minor "${CMAKE_CURRENT_LIST_DIR}/src/pico_keys_version.h")

project(pico_rescue)