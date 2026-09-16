//-------------------------------------------------------------------------------
// Copyright (c) 2026 John D. Haughton
// SPDX-License-Identifier: GPL-2.0-only
//-------------------------------------------------------------------------------

#include <cstdint>
#include <cstring>

#include "PLT/Event.h"

#include "doom_interface.h"


inline DoomKey xlateKey(PLT::KeyCode key_)
{
   switch(key_)
   {
   case PLT::KeyCode::TAB:    return KEY_TAB;
   case PLT::KeyCode::RETURN: return KEY_ENTER;
   case PLT::KeyCode::ESCAPE: return KEY_ESCAPE;
   case PLT::KeyCode::LEFT:   return KEY_LEFTARROW;
   case PLT::KeyCode::RIGHT:  return KEY_RIGHTARROW;
   case PLT::KeyCode::DOWN:   return KEY_DOWNARROW;
   case PLT::KeyCode::UP:     return KEY_UPARROW;
   case PLT::KeyCode::F1:     return KEY_F1;
   case PLT::KeyCode::F2:     return KEY_F2;
   case PLT::KeyCode::F3:     return KEY_F3;
   case PLT::KeyCode::F4:     return KEY_F4;
   case PLT::KeyCode::F5:     return KEY_F5;
   case PLT::KeyCode::F6:     return KEY_F6;
   case PLT::KeyCode::F7:     return KEY_F7;
   case PLT::KeyCode::F8:     return KEY_F8;
   case PLT::KeyCode::F9:     return KEY_F9;
   case PLT::KeyCode::F10:    return KEY_F10;
   case PLT::KeyCode::F11:    return KEY_F11;
   case PLT::KeyCode::F12:    return KEY_F12;

   case PLT::KeyCode::BACKSPACE:
   case PLT::KeyCode::DELETE:
      return KEY_BACKSPACE;

   case PLT::KeyCode::LSHIFT:
   case PLT::KeyCode::RSHIFT:
      return KEY_RSHIFT;

   case PLT::KeyCode::LCTRL:
   case PLT::KeyCode::RCTRL:
      return KEY_RCTRL;

   case PLT::KeyCode::LALT:
   case PLT::KeyCode::LCMD:
   case PLT::KeyCode::RALT:
   case PLT::KeyCode::RCMD:
      return KEY_RALT;

   default:
      break;
   }

   return DoomKey(key_);
}

void I_StartTic()
{
   PLT::Event::Message msg{};

   while(PLT::Event::poll(msg) != PLT::Event::NONE)
   {
      static uint8_t button_state = 0;
      static int32_t last_x{};
      static int32_t last_y{};

      event_t event{};

      switch(msg.type)
      {
      case PLT::Event::KEY_DOWN:
         event.type  = ev_keydown;
         event.data1 = xlateKey(PLT::KeyCode(msg.code));
         D_PostEvent(&event);
         break;

      case PLT::Event::KEY_UP:
         event.type  = ev_keyup;
         event.data1 = xlateKey(PLT::KeyCode(msg.code));
         D_PostEvent(&event);
         break;

      case PLT::Event::BUTTON_DOWN:
         event.type  = ev_mouse;
              if (msg.code == PLT::LEFT)  button_state |= BTN_LEFT;
         else if (msg.code == PLT::RIGHT) button_state |= BTN_RIGHT;
         event.data1 = button_state;
         D_PostEvent(&event);
         break;

      case PLT::Event::BUTTON_UP:
         event.type  = ev_mouse;
              if (msg.code == PLT::LEFT)  button_state &= ~BTN_LEFT;
         else if (msg.code == PLT::RIGHT) button_state &= ~BTN_RIGHT;
         event.data1 = button_state;
         D_PostEvent(&event);
         break;

      case PLT::Event::POINTER_MOVE:
         event.type  = ev_mouse;
         event.data1 = button_state;
         event.data2 = msg.x - last_x;
         event.data3 = last_y - msg.y;
         D_PostEvent(&event);
         last_x = msg.x;
         last_y = msg.y;
         break;

      case PLT::Event::QUIT:
         I_Quit();
         break;

      default:
         break;
      }
   }
}
