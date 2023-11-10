#include <winuser.h>

#pragma once

void ctrl_c() {

keybd_event(VK_MENU,0xA2,0,0);                                                      // Appuie : CTRL GAUCHE
keybd_event(VK_RETURN,0x43,0,0);                                                    // Appuie : C KEY
keybd_event(VK_RETURN,0x43,KEYEVENTF_KEYUP,0);                                      // Relache : C KEY
keybd_event(VK_MENU,0xA2,KEYEVENTF_KEYUP,0);                                        // Relache : CTRL GAUCHE

}