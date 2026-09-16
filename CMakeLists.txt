#-------------------------------------------------------------------------------
# Copyright (c) 2026 John D. Haughton
# SPDX-License-Identifier: GPL-2.0-only
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(SloeDOOM
        LANGUAGES CXX C
        VERSION 0.0)

if(NOT DEFINED BUILD_TESTING)
    set(BUILD_TESTING OFF CACHE BOOL "Build unit tests")
endif()
include(CTest)

add_subdirectory(PDK)
add_subdirectory(Source)
