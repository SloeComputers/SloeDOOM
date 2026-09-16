//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: GPL-2.0-only
//-------------------------------------------------------------------------------

#include <cstdio>

#include "STB/ConsoleApp.h"

#define  PROGRAM         "SloeDOOM"
#define  DESCRIPTION     "Sloe Computers port of the classic game from id"
#define  LINK            "https://github.com/SloeComputers"
#define  AUTHOR          "id SOFTWARE"
#define  COPYRIGHT_YEAR  "1993"

extern "C" void D_DoomMain();

class DOOMApp : public STB::ConsoleApp
{
public:
   DOOMApp()
      : ConsoleApp(PROGRAM, DESCRIPTION, LINK, AUTHOR, COPYRIGHT_YEAR)
   {
      licGPL2();
   }

private:
   virtual int startConsoleApp() override
   {
      D_DoomMain();
      return 0;
   }
};


int main(int argc, const char* argv[])
{
   return DOOMApp().parseArgsAndStart(argc, argv);
}
