#-------------------------------------------------------------------------------
# Copyright (c) 2026 John D. Haughton
# SPDX-License-Identifier: GPL-2.0-only
#-------------------------------------------------------------------------------

add_subdirectory(id_DOOM/linuxdoom-1.10)

add_executable(doom
               doom.cpp
               video.cpp
               event.cpp
               sound.cpp
               music.cpp
               net.cpp
               )

target_link_libraries(doom id_DOOM PLT)
