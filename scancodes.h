#pragma once

#include <string>
void getAllScancodeLabels(std::string arr[]);
unsigned char getScancode(std::string label, std::string arr[]);

// taken from https://github.com/wgois/OIS/blob/master/includes/OISKeyboard.h
// assigns easy to remember labels to the PS2 scan codes set 1 (which the keyboard driver seems to use)

//Keyboard scan codes
//Put a space after every SC_X, and do NOT put a second SC_ into a line, not in the comments either
enum ScanCode {
    SC_NOP = 0x00,  //unassigned, unknown, NoOPeration
    SC_ESCAPE = 0x01,
    SC_1 = 0x02,
    SC_2 = 0x03,
    SC_3 = 0x04,
    SC_4 = 0x05,
    SC_5 = 0x06,
    SC_6 = 0x07,
    SC_7 = 0x08,
    SC_8 = 0x09,
    SC_9 = 0x0A,
    SC_0 = 0x0B,
    SC_MINUS = 0x0C, // - on main keyboard
    SC_EQUALS = 0x0D,
    SC_BACK = 0x0E, // backspace
    SC_TAB = 0x0F,
    SC_Q = 0x10,
    SC_W = 0x11,
    SC_E = 0x12,
    SC_R = 0x13,
    SC_T = 0x14,
    SC_Y = 0x15,
    SC_U = 0x16,
    SC_I = 0x17,
    SC_O = 0x18,
    SC_P = 0x19,
    SC_LBRACK = 0x1A, // left bracket [
    SC_RBRACK = 0x1B,
    SC_RETURN = 0x1C, // Enter on main keyboard
    SC_LCTRL = 0x1D,
    SC_A = 0x1E,
    SC_S = 0x1F,
    SC_D = 0x20,
    SC_F = 0x21,
    SC_G = 0x22,
    SC_H = 0x23,
    SC_J = 0x24,
    SC_K = 0x25,
    SC_L = 0x26,
    SC_SEMI = 0x27,  // semicolon ;
    SC_APOS = 0x28,  // apostrophe '
    SC_GRAVE = 0x29, // accent `
    SC_LSHIFT = 0x2A,
    SC_BSLASH = 0x2B,
    SC_Z = 0x2C,
    SC_X = 0x2D,
    SC_C = 0x2E,
    SC_V = 0x2F,
    SC_B = 0x30,
    SC_N = 0x31,
    SC_M = 0x32,
    SC_COMMA = 0x33,
    SC_DOT = 0x34, // . on main keyboard
    SC_SLASH = 0x35, // / on main keyboard
    SC_RSHIFT = 0x36,
    SC_NPMULT = 0x37, // * on numeric keypad
    SC_LALT = 0x38, // left Alt
    SC_SPACE = 0x39,
    SC_CAPS = 0x3A,
    SC_F1 = 0x3B,
    SC_F2 = 0x3C,
    SC_F3 = 0x3D,
    SC_F4 = 0x3E,
    SC_F5 = 0x3F,
    SC_F6 = 0x40,
    SC_F7 = 0x41,
    SC_F8 = 0x42,
    SC_F9 = 0x43,
    SC_F10 = 0x44,
    SC_NUMLOCK = 0x45, // also, 1dv 45v 1d^ 45^ is [Pause]
    SC_SCRLOCK = 0x46, // Scroll Lock
    SC_NP7 = 0x47,
    SC_NP8 = 0x48,
    SC_NP9 = 0x49,
    SC_NPSUB = 0x4A, // - on numeric keypad
    SC_NP4 = 0x4B,
    SC_NP5 = 0x4C,
    SC_NP6 = 0x4D,
    SC_NPADD = 0x4E, // + on numeric keypad
    SC_NP1 = 0x4F,
    SC_NP2 = 0x50,
    SC_NP3 = 0x51,
    SC_NP0 = 0x52,
    SC_NPDOT = 0x53, // . on numeric keypad
    SC_LBSLASH = 0x56, //  Left BackSlash \  or < > |  right of left shift on UK/Germany keyboards
    SC_F11 = 0x57,
    SC_F12 = 0x58,
    SC_NPEQUALS1 = 0x59,    //Numpad [=] on Apple 
    SC_F13 = 0x64, //                     (NEC PC98)
    SC_F14 = 0x65, //                     (NEC PC98)
    SC_F15 = 0x66, //                     (NEC PC98)
    SC_F16 = 0x67, //Apple KB
    SC_F17 = 0x68,
    SC_F18 = 0x69,
    SC_F19 = 0x6A,
    SC_KANA = 0x70, // (Japanese keyboard)
    SC_ABNT_C1 = 0x73, // / ? on Portugese (Brazilian) keyboards
    SC_CONVERT = 0x79, // (Japanese keyboard)
    SC_NOCONVERT = 0x7B, // (Japanese keyboard)
    SC_YEN = 0x7D, // (Japanese keyboard)
    SC_ABNT_C2 = 0x7E, // Numpad . on Portugese (Brazilian) keyboards
    SC_NPEQUALS2 = 0x8D, // = on numeric keypad (NEC PC98)
    SC_PREVTRACK = 0x90, // Previous Track (CIRCUMFLEX on Japanese keyboard)
    SC_AT = 0x91, //                     (NEC PC98)
    SC_COLON = 0x92, //                     (NEC PC98)
    SC_UNDERLINE = 0x93, //                     (NEC PC98)
    SC_KANJI = 0x94, // (Japanese keyboard)
    SC_STOP = 0x95, //                     (NEC PC98)
    SC_AX = 0x96, //                     (Japan AX)
    SC_UNLABELED = 0x97, //                        (J3100)
    SC_NEXTTRACK = 0x99, // Next Track
    SC_NPRET = 0x9C, // Enter on numeric keypad
    SC_RCTRL = 0x9D,
    SC_MUTE = 0xA0, // Mute
    SC_CALCULATOR = 0xA1, // Calculator
    SC_PLAYPAUSE = 0xA2, // Play / Pause
    SC_MEDIASTOP = 0xA4, // Media Stop
    SC_TWOSUPERIOR = 0xAA, // � on French AZERTY keyboard (same place as ~ ` on QWERTY)
    SC_VOLUMEDOWN = 0xAE, // Volume -
    SC_VOLUMEUP = 0xB0, // Volume +
    SC_WEBHOME = 0xB2, // Web home
    SC_NUMPADCOMMA = 0xB3, // , on numeric keypad (NEC PC98)
    SC_DIVIDE = 0xB5, // / on numeric keypad
    SC_SYSRQ = 0xB7,  // Print, sends Shift+Print 2A B7
    SC_RALT = 0xB8, // right Alt
    SC_PAUSE = 0xC5, // Pause
    SC_HOME = 0xC7, // Home on arrow keypad
    SC_UP = 0xC8, // UpArrow on arrow keypad
    SC_PGUP = 0xC9, // PgUp on arrow keypad
    SC_LEFT = 0xCB, // LeftArrow on arrow keypad
    SC_RIGHT = 0xCD, // RightArrow on arrow keypad
    SC_END = 0xCF, // End on arrow keypad
    SC_DOWN = 0xD0, // DownArrow on arrow keypad
    SC_PGDOWN = 0xD1, // PgDn on arrow keypad
    SC_INSERT = 0xD2, // Insert on arrow keypad
    SC_DELETE = 0xD3, // Delete on arrow keypad
    SC_LWIN = 0xDB, // Left Windows key
    SC_RWIN = 0xDC, // Right Windows key
    SC_APPS = 0xDD, // AppMenu key
    SC_POWER = 0xDE, // System Power
    SC_SLEEP = 0xDF, // System Sleep
    SC_WAKE = 0xE3, // System Wake
    SC_WEBSEARCH = 0xE5, // Web Search
    SC_WEBFAVORITES = 0xE6, // Web Favorites
    SC_WEBREFRESH = 0xE7, // Web Refresh
    SC_WEBSTOP = 0xE8, // Web Stop
    SC_WEBFORWARD = 0xE9, // Web Forward
    SC_WEBBACK = 0xEA, // Web Back
    SC_MYCOMPUTER = 0xEB, // My Computer
    SC_MAIL = 0xEC, // Mail
    SC_MEDIASELECT = 0xED, // Media Select
    //CAPSICAIN virtual modifier keys. Hope no keyboard ever sends this.
    SC_MOD9 = 0xF0,
    SC_MOD10 = 0xF1,
    SC_MOD11 = 0xF2,
    SC_MOD12 = 0xF3,
    SC_MOD13 = 0xF4,
    SC_MOD14 = 0xF5,
    SC_MOD15 = 0xF6,
    //special escape code for Capsicain key sequences. Do not use this in the .ini
    SC_CPS_ESC = 0xFF
};
