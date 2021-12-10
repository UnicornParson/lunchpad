#ifndef WINCONSTANTS_H
#define WINCONSTANTS_H

#include <QObject>
#include <windows.h>
#include <winuser.h>
class WinConstants : public QObject
{
    Q_OBJECT
public:
    explicit WinConstants(QObject *parent = nullptr);
    enum eVK: uint
    {
        KEY_INVALID = 0,
        KEY_LBUTTON = VK_LBUTTON, // 0x01
        KEY_RBUTTON = VK_RBUTTON, // 0x02
        KEY_CANCEL = VK_CANCEL, // 0x03
        KEY_MBUTTON = VK_MBUTTON, // 0x04
        KEY_XBUTTON1 = VK_XBUTTON1, // 0x05
        KEY_XBUTTON2 = VK_XBUTTON2, // 0x06
        KEY_BACK = VK_BACK, // 0x08
        KEY_TAB = VK_TAB, // 0x09
        KEY_CLEAR = VK_CLEAR, // 0x0C
        KEY_RETURN = VK_RETURN, // 0x0D
        KEY_SHIFT = VK_SHIFT, // 0x10
        KEY_CONTROL = VK_CONTROL, // 0x11
        KEY_MENU = VK_MENU, // 0x12
        KEY_PAUSE = VK_PAUSE, // 0x13
        KEY_CAPITAL = VK_CAPITAL, // 0x14
        KEY_KANA = VK_KANA, // 0x15
        KEY_HANGEUL = VK_HANGEUL, // 0x15
        KEY_HANGUL = VK_HANGUL, // 0x15
        KEY_JUNJA = VK_JUNJA, // 0x17
        KEY_FINAL = VK_FINAL, // 0x18
        KEY_HANJA = VK_HANJA, // 0x19
        KEY_KANJI = VK_KANJI, // 0x19
        KEY_ESCAPE = VK_ESCAPE, // 0x1B
        KEY_CONVERT = VK_CONVERT, // 0x1C
        KEY_NONCONVERT = VK_NONCONVERT, // 0x1D
        KEY_ACCEPT = VK_ACCEPT, // 0x1E
        KEY_MODECHANGE = VK_MODECHANGE, // 0x1F
        KEY_SPACE = VK_SPACE, // 0x20
        KEY_PRIOR = VK_PRIOR, // 0x21
        KEY_NEXT = VK_NEXT, // 0x22
        KEY_END = VK_END, // 0x23
        KEY_HOME = VK_HOME, // 0x24
        KEY_LEFT = VK_LEFT, // 0x25
        KEY_UP = VK_UP, // 0x26
        KEY_RIGHT = VK_RIGHT, // 0x27
        KEY_DOWN = VK_DOWN, // 0x28
        KEY_SELECT = VK_SELECT, // 0x29
        KEY_PRINT = VK_PRINT, // 0x2A
        KEY_SNAPSHOT = VK_SNAPSHOT, // 0x2C
        KEY_INSERT = VK_INSERT, // 0x2D
        KEY_DELETE = VK_DELETE, // 0x2E
        KEY_HELP = VK_HELP, // 0x2F
        KEY_LWIN = VK_LWIN, // 0x5B
        KEY_RWIN = VK_RWIN, // 0x5C
        KEY_APPS = VK_APPS, // 0x5D
        KEY_SLEEP = VK_SLEEP, // 0x5F
        KEY_NUMPAD0 = VK_NUMPAD0, // 0x60
        KEY_NUMPAD1 = VK_NUMPAD1, // 0x61
        KEY_NUMPAD2 = VK_NUMPAD2, // 0x62
        KEY_NUMPAD3 = VK_NUMPAD3, // 0x63
        KEY_NUMPAD4 = VK_NUMPAD4, // 0x64
        KEY_NUMPAD5 = VK_NUMPAD5, // 0x65
        KEY_NUMPAD6 = VK_NUMPAD6, // 0x66
        KEY_NUMPAD7 = VK_NUMPAD7, // 0x67
        KEY_NUMPAD8 = VK_NUMPAD8, // 0x68
        KEY_NUMPAD9 = VK_NUMPAD9, // 0x69
        KEY_MULTIPLY = VK_MULTIPLY, // 0x6A
        KEY_ADD = VK_ADD, // 0x6B
        KEY_SEPARATOR = VK_SEPARATOR, // 0x6C
        KEY_SUBTRACT = VK_SUBTRACT, // 0x6D
        KEY_DECIMAL = VK_DECIMAL, // 0x6E
        KEY_DIVIDE = VK_DIVIDE, // 0x6F
        KEY_F1 = VK_F1, // 0x70
        KEY_F2 = VK_F2, // 0x71
        KEY_F3 = VK_F3, // 0x72
        KEY_F4 = VK_F4, // 0x73
        KEY_F5 = VK_F5, // 0x74
        KEY_F6 = VK_F6, // 0x75
        KEY_F7 = VK_F7, // 0x76
        KEY_F8 = VK_F8, // 0x77
        KEY_F9 = VK_F9, // 0x78
        KEY_F10 = VK_F10, // 0x79
        KEY_F11 = VK_F11, // 0x7A
        KEY_F12 = VK_F12, // 0x7B
        KEY_F13 = VK_F13, // 0x7C
        KEY_F14 = VK_F14, // 0x7D
        KEY_F15 = VK_F15, // 0x7E
        KEY_F16 = VK_F16, // 0x7F
        KEY_F17 = VK_F17, // 0x80
        KEY_F18 = VK_F18, // 0x81
        KEY_F19 = VK_F19, // 0x82
        KEY_F20 = VK_F20, // 0x83
        KEY_F21 = VK_F21, // 0x84
        KEY_F22 = VK_F22, // 0x85
        KEY_F23 = VK_F23, // 0x86
        KEY_F24 = VK_F24, // 0x87
        KEY_NUMLOCK = VK_NUMLOCK, // 0x90
        KEY_SCROLL = VK_SCROLL, // 0x91
        KEY_OEM_NEC_EQUAL = VK_OEM_NEC_EQUAL, // 0x92
        KEY_OEM_FJ_JISHO = VK_OEM_FJ_JISHO, // 0x92
        KEY_OEM_FJ_MASSHOU = VK_OEM_FJ_MASSHOU, // 0x93
        KEY_OEM_FJ_TOUROKU = VK_OEM_FJ_TOUROKU, // 0x94
        KEY_OEM_FJ_LOYA = VK_OEM_FJ_LOYA, // 0x95
        KEY_OEM_FJ_ROYA = VK_OEM_FJ_ROYA, // 0x96
        KEY_LSHIFT = VK_LSHIFT, // 0xA0
        KEY_RSHIFT = VK_RSHIFT, // 0xA1
        KEY_LCONTROL = VK_LCONTROL, // 0xA2
        KEY_RCONTROL = VK_RCONTROL, // 0xA3
        KEY_LMENU = VK_LMENU, // 0xA4
        KEY_RMENU = VK_RMENU, // 0xA5
        KEY_BROWSER_BACK = VK_BROWSER_BACK, // 0xA6
        KEY_BROWSER_FORWARD = VK_BROWSER_FORWARD, // 0xA7
        KEY_BROWSER_REFRESH = VK_BROWSER_REFRESH, // 0xA8
        KEY_BROWSER_STOP = VK_BROWSER_STOP, // 0xA9
        KEY_BROWSER_SEARCH = VK_BROWSER_SEARCH, // 0xAA
        KEY_BROWSER_FAVORITES = VK_BROWSER_FAVORITES, // 0xAB
        KEY_BROWSER_HOME = VK_BROWSER_HOME, // 0xAC
        KEY_VOLUME_MUTE = VK_VOLUME_MUTE, // 0xAD
        KEY_VOLUME_DOWN = VK_VOLUME_DOWN, // 0xAE
        KEY_VOLUME_UP = VK_VOLUME_UP, // 0xAF
        KEY_MEDIA_NEXT_TRACK = VK_MEDIA_NEXT_TRACK, // 0xB0
        KEY_MEDIA_PREV_TRACK = VK_MEDIA_PREV_TRACK, // 0xB1
        KEY_MEDIA_STOP = VK_MEDIA_STOP, // 0xB2
        KEY_MEDIA_PLAY_PAUSE = VK_MEDIA_PLAY_PAUSE, // 0xB3
        KEY_LAUNCH_MAIL = VK_LAUNCH_MAIL, // 0xB4
        KEY_LAUNCH_MEDIA_SELECT = VK_LAUNCH_MEDIA_SELECT, // 0xB5
        KEY_LAUNCH_APP1 = VK_LAUNCH_APP1, // 0xB6
        KEY_LAUNCH_APP2 = VK_LAUNCH_APP2, // 0xB7
        KEY_OEM_1 = VK_OEM_1, // 0xBA
        KEY_OEM_PLUS = VK_OEM_PLUS, // 0xBB
        KEY_OEM_COMMA = VK_OEM_COMMA, // 0xBC
        KEY_OEM_MINUS = VK_OEM_MINUS, // 0xBD
        KEY_OEM_PERIOD = VK_OEM_PERIOD, // 0xBE
        KEY_OEM_2 = VK_OEM_2, // 0xBF
        KEY_OEM_3 = VK_OEM_3, // 0xC0
        KEY_OEM_4 = VK_OEM_4, // 0xDB
        KEY_OEM_5 = VK_OEM_5, // 0xDC
        KEY_OEM_6 = VK_OEM_6, // 0xDD
        KEY_OEM_7 = VK_OEM_7, // 0xDE
        KEY_OEM_8 = VK_OEM_8, // 0xDF
        KEY_OEM_AX = VK_OEM_AX, // 0xE1
        KEY_OEM_102 = VK_OEM_102, // 0xE2
        KEY_ICO_HELP = VK_ICO_HELP, // 0xE3
        KEY_ICO_00 = VK_ICO_00, // 0xE4
        KEY_PROCESSKEY = VK_PROCESSKEY, // 0xE5
        KEY_ICO_CLEAR = VK_ICO_CLEAR, // 0xE6
        KEY_PACKET = VK_PACKET, // 0xE7
        KEY_OEM_RESET = VK_OEM_RESET, // 0xE9
        KEY_OEM_JUMP = VK_OEM_JUMP, // 0xEA
        KEY_OEM_PA1 = VK_OEM_PA1, // 0xEB
        KEY_OEM_PA2 = VK_OEM_PA2, // 0xEC
        KEY_OEM_PA3 = VK_OEM_PA3, // 0xED
        KEY_OEM_WSCTRL = VK_OEM_WSCTRL, // 0xEE
        KEY_OEM_CUSEL = VK_OEM_CUSEL, // 0xEF
        KEY_OEM_ATTN = VK_OEM_ATTN, // 0xF0
        KEY_OEM_FINISH = VK_OEM_FINISH, // 0xF1
        KEY_OEM_COPY = VK_OEM_COPY, // 0xF2
        KEY_OEM_AUTO = VK_OEM_AUTO, // 0xF3
        KEY_OEM_ENLW = VK_OEM_ENLW, // 0xF4
        KEY_OEM_BACKTAB = VK_OEM_BACKTAB, // 0xF5
        KEY_ATTN = VK_ATTN, // 0xF6
        KEY_CRSEL = VK_CRSEL, // 0xF7
        KEY_EXSEL = VK_EXSEL, // 0xF8
        KEY_EREOF = VK_EREOF, // 0xF9
        KEY_PLAY = VK_PLAY, // 0xFA
        KEY_ZOOM = VK_ZOOM, // 0xFB
        KEY_NONAME = VK_NONAME, // 0xFC
        KEY_PA1 = VK_PA1, // 0xFD
        KEY_OEM_CLEAR = VK_OEM_CLEAR // 0xFE
    };
    Q_ENUM(eVK)
signals:

public slots:
};

#endif // WINCONSTANTS_H
