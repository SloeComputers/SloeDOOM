//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: GPL-2.0-only
//-------------------------------------------------------------------------------

#include <cstdio>

#include "PLT/Audio.h"

#include "doom_interface.h"

class DoomAudio : public PLT::Audio::Out
{
public:
   DoomAudio()
      : PLT::Audio::Out(SAMPLE_FREQUENCY, PLT::Audio::Format::SINT16, /* channels */ 1)
   {}

   void playSample(const int8_t* sample_, size_t length_)
   {
      unsigned oldest    = 0;
      unsigned max_index = 0;

      for(unsigned i = 0; i < NUM_CHANNELS; ++i)
      {
         Channel* chan = &channels[i];
         if (chan->on == false)
         {
            chan->start(sample_, length_);
            return;
         }

         if (chan->index_8 > max_index)
         {
            oldest = i;
            max_index = chan->index_8;
         }
      }

      channels[oldest].start(sample_, length_);
   }

private:
   static const unsigned SAMPLE_FREQUENCY = 11025;
   static const unsigned NUM_CHANNELS     = 8;

   struct Channel
   {
      bool          on{false};
      uint32_t      index_8{};
      uint32_t      rate_8{};
      const int8_t* sample{};
      uint32_t      length_8{};

      void start(const int8_t* sample_, unsigned length_)
      {
         on       = false;
         index_8  = 0;
         rate_8   = 0x100;
         sample   = sample_;
         length_8 = length_ << 8;
         on       = true;
      }

      int16_t getSample()
      {
         if (not on)
            return 0;

         int16_t value = sample[index_8 >> 8] - 128;
         index_8 += rate_8;
         if (index_8 >= length_8)
            on = false;
         return value;
      }
   };

   virtual void getSamples(int16_t* buffer, unsigned n) override
   {
      for(unsigned i = 0; i < n; ++i)
      {
         int16_t mix = 0;

         for(unsigned i = 0; i < NUM_CHANNELS; ++i)
         {
            Channel* chan = &channels[i];

            mix += chan->getSample();
         }

         buffer[i] = mix;
      }
   }

   Channel channels[NUM_CHANNELS];
};

struct Sample
{
   const int8_t* sample;
   unsigned      length;
};

const char* sndserver_filename = "";

static DoomAudio* audio{nullptr};

static Sample samples[NUMSFX];


void I_InitSound()
{
   if (audio != nullptr) return;

   audio = new DoomAudio();

   audio->setEnable(true);

   for(unsigned i = 0; i < NUMSFX; ++i)
   {
      char name[64];
      snprintf(name, sizeof(name), "ds%s", S_sfx[i].name);

      int lump = W_CheckNumForName(name);
      if (lump == -1)
         lump = W_CheckNumForName("dspistol");

      samples[i].length = W_LumpLength(lump);
      samples[i].sample = (const int8_t*) W_CacheLumpNum(lump, /* PU_STATIC */ 1);
   }
}

void I_ShutdownSound()
{
   if (audio == nullptr) return;

   audio->setEnable(false);

   delete audio;
}

void I_SetChannels()
{
   if (audio == nullptr) return;
}

void I_UpdateSound()
{
   if (audio == nullptr) return;
}

void I_SubmitSound()
{
   if (audio == nullptr) return;
}

int I_GetSfxLumpNum(sfxinfo_t* sfxinfo)
{
   if (audio == nullptr) return -1;
   return -1;
}

int I_StartSound(int id, int vold, int sep, int pitch, int priority)
{
   if (audio == nullptr) return -1;

   printf("StartSound(id=%d, vold=%d, sep=%d, pitch=%d, priority=%d)\n",
          id, vold, sep, pitch, priority);

   audio->playSample(samples[id].sample,
                     samples[id].length);

   return -1;
}

void I_StopSound(int handle)
{
   if (audio == nullptr) return;
}

int I_SoundIsPlaying(int handle)
{
   if (audio == nullptr) return 0;
   return 0;
}

void I_UpdateSoundParams(int handle, int vol, int sep, int pitch)
{
   if (audio == nullptr) return;
}
