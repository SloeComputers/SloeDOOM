#-------------------------------------------------------------------------------
# Copyright (c) 2026 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

add_subdirectory(id_DOOM)

add_executable(doom
               doom.cpp
               video.cpp
               event.cpp
               sound.cpp
               music.cpp
               net.cpp
               )

target_link_libraries(doom doom_lib PLT)
