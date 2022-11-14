//
// Created by aziz on 28.11.21.
//

#ifndef SOCKET_MOUSE_KEY_H
#define SOCKET_MOUSE_KEY_H

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <array>
#include <string>
#include <sstream>

const std::array<std::string, 249> Key_list = {
    "RESERVED", "ESC", "1"
    , "2", "3"
    , "4", "5"
    , "6", "7"
    , "8", "9"
    , "0", "MINUS"
    , "EQUAL", "BACKSPACE"
    , "TAB", "Q"
    , "W", "E", "R"
    , "T", "Y"
    , "U", "I"
    , "O", "P"
    , "LEFTBRACE", "RIGHTBRACE"
    , "ENTER", "LEFTCTRL"
    , "A", "S"
    , "D", "F"
    , "G", "H"
    , "J", "K"
    , "L", "SEMICOLON"
    , "APOSTROPHE", "GRAVE"
    , "LEFTSHIFT", "BACKSLASH"
    , "Z", "X"
    , "C", "V"
    , "B", "N"
    , "M", "COMMA"
    , "DOT", "SLASH"
    , "RIGHTSHIFT", "KPASTERISK"
    , "LEFTALT", "SPACE"
    , "CAPSLOCK", "F1"
    , "F2", "F3"
    , "F4", "F5"
    , "F6", "F7"
    , "F8", "F9"
    , "F10", "NUMLOCK"
    , "SCROLLLOCK", "KP7"
    , "KP8", "KP9"
    , "KPMINUS", "KP4"
    , "KP5", "KP6"
    , "KPPLUS", "KP1"
    , "KP2", "KP3"
    , "KP0", "KPDOT", "11"
    , "ZENKAKUHANKAKU", "102ND"
    , "F11", "F12"
    , "RO", "KATAKANA"
    , "HIRAGANA", "HENKAN"
    , "KATAKANAHIRAGANA", "MUHENKAN"
    , "KPJPCOMMA", "KPENTER"
    , "RIGHTCTRL", "KPSLASH"
    , "SYSRQ", "RIGHTALT"
    , "LINEFEED", "HOME"
    , "UP", "PAGEUP"
    , "LEFT", "RIGHT"
    , "END", "DOWN", "PAGEDOWN", "INSERT"
    , "DELETE", "MACRO"
    , "MUTE", "VOLUMEDOWN"
    , "VOLUMEUP", "POWER"
    , "KPEQUAL", "KPPLUSMINUS"
    , "PAUSE", "SCALE"
    , "KPCOMMA", "HANGEUL"
    , "HANGUEL", "HANJA"
    /*,"KEY_YEN"*/, "LEFTMETA"
    , "RIGHTMETA", "COMPOSE"
    , "STOP", "AGAIN"
    , "PROPS", "UNDO"
    , "FRONT", "COPY"
    , "OPEN", "PASTE"
    , "FIND", "CUT"
    , "HELP", "MENU"
    , "CALC", "SETUP"
    , "SLEEP", "WAKEUP"
    , "FILE", "SENDFILE"
    , "DELETEFILE", "XFER"
    , "PROG1", "PROG2"
    , "WWW", "MSDOS"
    , "COFFEE", "SCREENLOCK"
    , "ROTATE_DISPLAY", "DIRECTION", "ROTATE_DISPLAY"
    , "CYCLEWINDOWS", "MAIL"
    , "BOOKMARKS", "COMPUTER"
    , "BACK", "FORWARD"
    , "CLOSECD", "EJECTCD"
    , "EJECTCLOSECD", "NEXTSONG"
    , "PLAYPAUSE", "PREVIOUSSONG"
    , "STOPCD", "RECORD"
    , "REWIND", "PHONE"
    , "ISO", "CONFIG"
    , "HOMEPAGE", "REFRESH", "EXIT"
    , "MOVE", "EDIT"
    , "SCROLLUP", "SCROLLDOWN"
    , "KPLEFTPAREN", "KPRIGHTPAREN"
    , "NEW", "REDO"
    , "F13", "F14"
    , "F15", "F16"
    , "F17", "F18"
    , "F19", "F20"
    , "F21", "F22"
    , "F23", "F24"
    , "PLAYCD", "PAUSECD"
    , "PROG3", "PROG4"
    , "DASHBOARD", "SUSPEND"
    , "CLOSE", "PLAY"
    , "FASTFORWARD", "BASSBOOST"
    , "PRINT", "HP"
    , "CAMERA", "SOUND"
    , "QUESTION", "EMAIL"
    , "CHAT", "SEARCH"
    , "CONNECT", "FINANCE"
    , "SPORT", "SHOP"
    , "ALTERASE", "CANCEL"
    , "BRIGHTNESSDOWN", "BRIGHTNESSUP"
    , "MEDIA", "SWITCHVIDEOMODE"
    , "KBDILLUMTOGGLE", "KBDILLUMDOWN"
    , "KBDILLUMUP", "SEND"
    , "REPLY", "FORWARDMAIL", "SAVE"
    , "DOCUMENTS", "BATTERY", "BLUETOOTH"
    , "WLAN", "UWB", "UNKNOWN"
    , "VIDEO_NEXT", "VIDEO_PREV", "BRIGHTNESS_CYCLE"
    , "BRIGHTNESS_AUTO", "BRIGHTNESS_ZERO"
    , "DISPLAY_OFF", "WWAN", "WIMAX"
    , "RFKILL", "MICMUTE"
};


struct input_event;
class key
{
public:
    key();
    virtual ~key(){}
    void loop();
protected:
    int fd = 0;
    input_event ie{};
    int shift_state = 0;
    int alt_state = 0;
    int ctrl_state = 0;
};


#endif //SOCKET_MOUSE_KEY_H
