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

enum
{
   sfx_None,
   sfx_pistol,
   sfx_shotgn,
   sfx_sgcock,
   sfx_dshtgn,
   sfx_dbopn,
   sfx_dbcls,
   sfx_dbload,
   sfx_plasma,
   sfx_bfg,
   sfx_sawup,
   sfx_sawidl,
   sfx_sawful,
   sfx_sawhit,
   sfx_rlaunc,
   sfx_rxplod,
   sfx_firsht,
   sfx_firxpl,
   sfx_pstart,
   sfx_pstop,
   sfx_doropn,
   sfx_dorcls,
   sfx_stnmov,
   sfx_swtchn,
   sfx_swtchx,
   sfx_plpain,
   sfx_dmpain,
   sfx_popain,
   sfx_vipain,
   sfx_mnpain,
   sfx_pepain,
   sfx_slop,
   sfx_itemup,
   sfx_wpnup,
   sfx_oof,
   sfx_telept,
   sfx_posit1,
   sfx_posit2,
   sfx_posit3,
   sfx_bgsit1,
   sfx_bgsit2,
   sfx_sgtsit,
   sfx_cacsit,
   sfx_brssit,
   sfx_cybsit,
   sfx_spisit,
   sfx_bspsit,
   sfx_kntsit,
   sfx_vilsit,
   sfx_mansit,
   sfx_pesit,
   sfx_sklatk,
   sfx_sgtatk,
   sfx_skepch,
   sfx_vilatk,
   sfx_claw,
   sfx_skeswg,
   sfx_pldeth,
   sfx_pdiehi,
   sfx_podth1,
   sfx_podth2,
   sfx_podth3,
   sfx_bgdth1,
   sfx_bgdth2,
   sfx_sgtdth,
   sfx_cacdth,
   sfx_skldth,
   sfx_brsdth,
   sfx_cybdth,
   sfx_spidth,
   sfx_bspdth,
   sfx_vildth,
   sfx_kntdth,
   sfx_pedth,
   sfx_skedth,
   sfx_posact,
   sfx_bgact,
   sfx_dmact,
   sfx_bspact,
   sfx_bspwlk,
   sfx_vilact,
   sfx_noway,
   sfx_barexp,
   sfx_punch,
   sfx_hoof,
   sfx_metal,
   sfx_chgun,
   sfx_tink,
   sfx_bdopn,
   sfx_bdcls,
   sfx_itmbk,
   sfx_flame,
   sfx_flamst,
   sfx_getpow,
   sfx_bospit,
   sfx_boscub,
   sfx_bossit,
   sfx_bospn,
   sfx_bosdth,
   sfx_manatk,
   sfx_mandth,
   sfx_sssit,
   sfx_ssdth,
   sfx_keenpn,
   sfx_keendt,
   sfx_skeact,
   sfx_skesit,
   sfx_skeatk,
   sfx_radio,
   NUMSFX
};

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

extern sfxinfo_t S_sfx[NUMSFX];

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

   int            W_CheckNumForName(const char*);
   int            W_LumpLength(int);
   const uint8_t* W_CacheLumpNum(int, int);
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
