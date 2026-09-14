//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include <cstdio>

#include "STB/ConsoleApp.h"

#define  PROGRAM         "DOOM"
#define  DESCRIPTION     "The classic game"
#define  LINK            "https://github.com/sloecomputer"
#define  AUTHOR          "John D. Haughton"
#define  COPYRIGHT_YEAR  "2026"

extern "C" void D_DoomMain();

class DOOMApp : public STB::ConsoleApp
{
public:
   DOOMApp()
      : ConsoleApp(PROGRAM, DESCRIPTION, LINK, AUTHOR, COPYRIGHT_YEAR)
   {
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
