//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: GPL-2.0-only
//-------------------------------------------------------------------------------

#include "doom_interface.h"

static doomcom_t doomcom_instance{};

void I_InitNetwork()
{
   doomcom = &doomcom_instance;
   netgame = 0;
}

void I_NetCmd()
{
}

