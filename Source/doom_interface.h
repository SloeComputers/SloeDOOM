//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: GPL-2.0-only
//-------------------------------------------------------------------------------

#include <cstdint>


//--- EVENTS --------------------------------------------------------------------

enum DoomKey : int32_t
{
   KEY_ESCAPE      = 27,
   KEY_ENTER       = 13,
   KEY_TAB         = 9,
   KEY_BACKSPACE   = 127,
   KEY_RCTRL       = 0x9D,
   KEY_RIGHTARROW  = 0xAE,
   KEY_LEFTARROW   = 0xAC,
   KEY_UPARROW     = 0xAD,
   KEY_DOWNARROW   = 0xAF,
   KEY_RSHIFT      = 0xB6,
   KEY_RALT        = 0xB8,
   KEY_F1          = 0xBB,
   KEY_F2          = 0xBC,
   KEY_F3          = 0xBD,
   KEY_F4          = 0xBE,
   KEY_F5          = 0xBF,
   KEY_F6          = 0xC0,
   KEY_F7          = 0xC1,
   KEY_F8          = 0xC2,
   KEY_F9          = 0xC3,
   KEY_F10         = 0xC4,
   KEY_F11         = 0xD7,
   KEY_F12         = 0xD8,
   KEY_PAUSE       = 0xFF
};

enum DoomButton : int32_t
{
   BTN_LEFT   = 1 << 0,
   BTN_MIDDLE = 1 << 1,
   BTN_RIGHT  = 1 << 2
};

enum evtype_t
{
   ev_keydown  = 0,
   ev_keyup    = 1,
   ev_mouse    = 2,
   ev_joystick = 3
};

struct event_t
{
   evtype_t type;
   int32_t  data1; //< keys / mouse/joystick buttons
   int32_t  data2; //< mouse/joystick x move
   int32_t  data3; //< mouse/joystick y move
};

extern "C"
{
   void D_PostEvent(event_t*);
   void I_Quit();

   void I_StartTic();
}


//--- MUSIC ---------------------------------------------------------------------

extern "C"
{
   void I_InitMusic();
   void I_ShutdownMusic();
   void I_SetMusicVolume(int volume);
   void I_PlaySong(int handle, int looping);
   void I_PauseSong(int handle);
   void I_ResumeSong(int handle);
   void I_StopSong(int handle);
   void I_RegisterSong(void* data);
   void I_UnRegisterSong(int handle);
}


//--- NETWORK -------------------------------------------------------------------

struct ticcmd_t
{
   char    forwardmove{};
   char    sidemove{};
   short   angleturn{};
   short   consistancy{};
   uint8_t chatchar{};
   uint8_t buttons{};
};

struct doomdata_t
{   
   static const unsigned BACKUPTICS = 12;

   uint32_t checksum{};       
   uint8_t  retransmitfrom{};
   uint8_t  starttic{};
   uint8_t  player{};
   uint8_t  numtics{};
   ticcmd_t cmds[BACKUPTICS];
};

struct doomcom_t
{
   static const uint32_t DOOMCOM_ID = 0x12345678;

   uint32_t   id{DOOMCOM_ID};
   uint16_t   intnum{};
   uint16_t   command{};
   uint16_t   remotenode{};
   uint16_t   datalength{};
   uint16_t   numnodes{1};
   uint16_t   ticdup{1};
   uint16_t   extratics{};
   uint16_t   deathmatch{0};
   uint16_t   savegame{};
   uint16_t   episode{};
   uint16_t   map{};
   uint16_t   skill{};
   uint16_t   consoleplayer{0};
   uint16_t   numplayers{1};
   uint16_t   angleoffset{};
   uint16_t   drone{};
   doomdata_t data{};
};

extern "C"
{
   void I_InitNetwork();
   void I_NetCmd();
}

extern doomcom_t* doomcom;
extern int        netgame;


//--- SOUND ---------------------------------------------------------------------

struct sfxinfo_t
{
   char*      name;
   int        singularity;
   int        priority;
   sfxinfo_t* link;
   int        pitch;
   int        volume;
   void*      data;
   int        usefulness;
   int        lumpnum;
};

extern const char* sndserver_filename;

extern "C"
{
   void I_InitSound();
   void I_UpdateSound();
   void I_SubmitSound();
   void I_ShutdownSound();
   void I_SetChannels();
   int  I_GetSfxLumpNum(sfxinfo_t* sfxinfo);
   int  I_StartSound(int id, int vold, int sep, int pitch, int priority);
   void I_StopSound(int handle);
   int  I_SoundIsPlaying(int handle);
   void I_UpdateSoundParams(int handle, int vol, int sep, int pitch);
}


//--- VIDEO ---------------------------------------------------------------------

extern uint8_t* screens[5];

extern "C"
{
   void I_InitGraphics();
   void I_ShutdownGraphics();
   void I_SetPalette(uint8_t* data_);
   void I_FinishUpdate();
   void I_ReadScreen(uint8_t* out_);
   void I_UpdateNoBlit();
   void I_StartFrame();
}
