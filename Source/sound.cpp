//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "doom_interface.h"

const char* sndserver_filename = "";

void I_InitSound()
{
}

void I_UpdateSound()
{
}

void I_SubmitSound()
{
}

void I_ShutdownSound()
{
}

void I_SetChannels()
{
}

int I_GetSfxLumpNum(sfxinfo_t* sfxinfo)
{
   return -1;
}

int I_StartSound(int id, int vold, int sep, int pitch, int priority)
{
   return -1;
}

void I_StopSound(int handle)
{
}

int I_SoundIsPlaying(int handle)
{
   return 0;
}

void I_UpdateSoundParams(int handle, int vol, int sep, int pitch)
{
}
