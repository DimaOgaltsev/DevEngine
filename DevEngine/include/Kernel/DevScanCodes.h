#ifndef DEV_SC_H
#define DEV_SC_H

#define SC_ESCAPE          0x01
#define SC_1               0x02
#define SC_2               0x03
#define SC_3               0x04
#define SC_4               0x05
#define SC_5               0x06
#define SC_6               0x07
#define SC_7               0x08
#define SC_8               0x09
#define SC_9               0x0A
#define SC_0               0x0B
#define SC_MINUS           0x0C    /* - on main keyboard */
#define SC_EQUALS          0x0D
#define SC_BACK            0x0E    /* backspace */
#define SC_TAB             0x0F
#define SC_Q               0x10
#define SC_W               0x11
#define SC_E               0x12
#define SC_R               0x13
#define SC_T               0x14
#define SC_Y               0x15
#define SC_U               0x16
#define SC_I               0x17
#define SC_O               0x18
#define SC_P               0x19
#define SC_LBRACKET        0x1A
#define SC_RBRACKET        0x1B
#define SC_RETURN          0x1C    /* Enter on main keyboard */
#define SC_LCONTROL        0x1D
#define SC_A               0x1E
#define SC_S               0x1F
#define SC_D               0x20
#define SC_F               0x21
#define SC_G               0x22
#define SC_H               0x23
#define SC_J               0x24
#define SC_K               0x25
#define SC_L               0x26
#define SC_SEMICOLON       0x27
#define SC_APOSTROPHE      0x28
#define SC_GRAVE           0x29    /* accent grave */
#define SC_LSHIFT          0x2A
#define SC_BACKSLASH       0x2B
#define SC_Z               0x2C
#define SC_X               0x2D
#define SC_C               0x2E
#define SC_V               0x2F
#define SC_B               0x30
#define SC_N               0x31
#define SC_M               0x32
#define SC_COMMA           0x33
#define SC_PERIOD          0x34    /* . on main keyboard */
#define SC_SLASH           0x35    /* / on main keyboard */
#define SC_RSHIFT          0x36
#define SC_MULTIPLY        0x37    /* * on numeric keypad */
#define SC_LMENU           0x38    /* left Alt */
#define SC_SPACE           0x39
#define SC_CAPITAL         0x3A
#define SC_F1              0x3B
#define SC_F2              0x3C
#define SC_F3              0x3D
#define SC_F4              0x3E
#define SC_F5              0x3F
#define SC_F6              0x40
#define SC_F7              0x41
#define SC_F8              0x42
#define SC_F9              0x43
#define SC_F10             0x44
#define SC_NUMLOCK         0x45
#define SC_SCROLL          0x46    /* Scroll Lock */
#define SC_NUMPAD7         0x47
#define SC_NUMPAD8         0x48
#define SC_NUMPAD9         0x49
#define SC_SUBTRACT        0x4A    /* - on numeric keypad */
#define SC_NUMPAD4         0x4B
#define SC_NUMPAD5         0x4C
#define SC_NUMPAD6         0x4D
#define SC_ADD             0x4E    /* + on numeric keypad */
#define SC_NUMPAD1         0x4F
#define SC_NUMPAD2         0x50
#define SC_NUMPAD3         0x51
#define SC_NUMPAD0         0x52
#define SC_DECIMAL         0x53    /* . on numeric keypad */
#define SC_OEM_102         0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
#define SC_F11             0x57
#define SC_F12             0x58
#define SC_F13             0x64    /*                     (NEC PC98) */
#define SC_F14             0x65    /*                     (NEC PC98) */
#define SC_F15             0x66    /*                     (NEC PC98) */
#define SC_KANA            0x70    /* (Japanese keyboard)            */
#define SC_ABNT_C1         0x73    /* /? on Brazilian keyboard */
#define SC_CONVERT         0x79    /* (Japanese keyboard)            */
#define SC_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define SC_YEN             0x7D    /* (Japanese keyboard)            */
#define SC_ABNT_C2         0x7E    /* Numpad . on Brazilian keyboard */
#define SC_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define SC_PREVTRACK       0x90    /* Previous Track (SC_CIRCUMFLEX on Japanese keyboard) */
#define SC_AT              0x91    /*                     (NEC PC98) */
#define SC_COLON           0x92    /*                     (NEC PC98) */
#define SC_UNDERLINE       0x93    /*                     (NEC PC98) */
#define SC_KANJI           0x94    /* (Japanese keyboard)            */
#define SC_STOP            0x95    /*                     (NEC PC98) */
#define SC_AX              0x96    /*                     (Japan AX) */
#define SC_UNLABELED       0x97    /*                        (J3100) */
#define SC_NEXTTRACK       0x99    /* Next Track */
#define SC_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define SC_RCONTROL        0x9D
#define SC_MUTE            0xA0    /* Mute */
#define SC_CALCULATOR      0xA1    /* Calculator */
#define SC_PLAYPAUSE       0xA2    /* Play / Pause */
#define SC_MEDIASTOP       0xA4    /* Media Stop */
#define SC_VOLUMEDOWN      0xAE    /* Volume - */
#define SC_VOLUMEUP        0xB0    /* Volume + */
#define SC_WEBHOME         0xB2    /* Web home */
#define SC_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define SC_DIVIDE          0xB5    /* / on numeric keypad */
#define SC_SYSRQ           0xB7
#define SC_RMENU           0xB8    /* right Alt */
#define SC_PAUSE           0xC5    /* Pause */
#define SC_HOME            0xC7    /* Home on arrow keypad */
#define SC_UP              0xC8    /* UpArrow on arrow keypad */
#define SC_PRIOR           0xC9    /* PgUp on arrow keypad */
#define SC_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define SC_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define SC_END             0xCF    /* End on arrow keypad */
#define SC_DOWN            0xD0    /* DownArrow on arrow keypad */
#define SC_NEXT            0xD1    /* PgDn on arrow keypad */
#define SC_INSERT          0xD2    /* Insert on arrow keypad */
#define SC_DELETE          0xD3    /* Delete on arrow keypad */
#define SC_LWIN            0xDB    /* Left Windows key */
#define SC_RWIN            0xDC    /* Right Windows key */
#define SC_APPS            0xDD    /* AppMenu key */
#define SC_POWER           0xDE    /* System Power */
#define SC_SLEEP           0xDF    /* System Sleep */
#define SC_WAKE            0xE3    /* System Wake */
#define SC_WEBSEARCH       0xE5    /* Web Search */
#define SC_WEBFAVORITES    0xE6    /* Web Favorites */
#define SC_WEBREFRESH      0xE7    /* Web Refresh */
#define SC_WEBSTOP         0xE8    /* Web Stop */
#define SC_WEBFORWARD      0xE9    /* Web Forward */
#define SC_WEBBACK         0xEA    /* Web Back */
#define SC_MYCOMPUTER      0xEB    /* My Computer */
#define SC_MAIL            0xEC    /* Mail */
#define SC_MEDIASELECT     0xED    /* Media Select */

/*
 *  Alternate names for keys, to facilitate transition from DOS.
 */
#define SC_BACKSPACE       SC_BACK            /* backspace */
#define SC_NUMPADSTAR      SC_MULTIPLY        /* * on numeric keypad */
#define SC_LALT            SC_LMENU           /* left Alt */
#define SC_CAPSLOCK        SC_CAPITAL         /* CapsLock */
#define SC_NUMPADMINUS     SC_SUBTRACT        /* - on numeric keypad */
#define SC_NUMPADPLUS      SC_ADD             /* + on numeric keypad */
#define SC_NUMPADPERIOD    SC_DECIMAL         /* . on numeric keypad */
#define SC_NUMPADSLASH     SC_DIVIDE          /* / on numeric keypad */
#define SC_RALT            SC_RMENU           /* right Alt */
#define SC_UPARROW         SC_UP              /* UpArrow on arrow keypad */
#define SC_PGUP            SC_PRIOR           /* PgUp on arrow keypad */
#define SC_LEFTARROW       SC_LEFT            /* LeftArrow on arrow keypad */
#define SC_RIGHTARROW      SC_RIGHT           /* RightArrow on arrow keypad */
#define SC_DOWNARROW       SC_DOWN            /* DownArrow on arrow keypad */
#define SC_PGDN            SC_NEXT            /* PgDn on arrow keypad */

/*
 *  Alternate names for keys originally not used on US keyboards.
 */
#define SC_CIRCUMFLEX      SC_PREVTRACK       /* Japanese keyboard */

#endif