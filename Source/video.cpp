//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: GPL-2.0-only
//-------------------------------------------------------------------------------

#include <cstdint>
#include <cstring>

#include "GUI/Frame.h"
#include "GUI/Colour.h"

#include "doom_interface.h"

class DoomGUI
{
public:
   DoomGUI() = default;

   uint8_t* getFrameBuffer() { return buffer; }

   void setPalette(const uint8_t* rgb_)
   {
      for(unsigned i = 0; i < PALETTE_SIZE; ++i)
      {
         uint8_t red = rgb_[i * 3 + 0];
         uint8_t grn = rgb_[i * 3 + 1];
         uint8_t blu = rgb_[i * 3 + 2];

         palette[i] = STB::RGB(red, grn, blu);;
      }
   }

   void render()
   {
      for(unsigned y = 0; y < HEIGHT; ++y)
      {
         for(unsigned x = 0; x < WIDTH; ++x)
         {
            STB::Colour pixel = palette[buffer[x + y * WIDTH]];

            for(unsigned yy = 0; yy < SCALE; ++yy)
            {
               for(unsigned xx = 0; xx < SCALE; ++xx)
               {
                  frame.drawPoint(pixel, x * SCALE + xx, y * SCALE + yy);
               }
            }
         }
      }

      frame.refresh();
   }

   static const unsigned WIDTH  = 320;
   static const unsigned HEIGHT = 200;

private:
   static const unsigned PALETTE_SIZE = 1 << 8;
   static const unsigned SCALE        = 2;

   STB::Colour palette[PALETTE_SIZE];
   GUI::Frame  frame{"DOOM", WIDTH * SCALE, HEIGHT * SCALE};
   uint8_t     buffer[WIDTH * HEIGHT];
};

static DoomGUI* gui{nullptr};

void I_InitGraphics()
{
   if (gui != nullptr) return;

   gui = new DoomGUI();
   screens[0] = gui->getFrameBuffer();
}

void I_ShutdownGraphics()
{
   delete gui;
   gui = nullptr;
}

void I_SetPalette(uint8_t* data_)
{
   if (gui == nullptr) return;

   gui->setPalette(data_);
}

void I_FinishUpdate()
{
   if (gui == nullptr) return;

   gui->render();
}

void I_ReadScreen(uint8_t* out_)
{
   if (gui == nullptr) return;

   memcpy(out_, gui->getFrameBuffer(), DoomGUI::WIDTH * DoomGUI::HEIGHT);
}

void I_UpdateNoBlit()
{
}

void I_StartFrame()
{
}
