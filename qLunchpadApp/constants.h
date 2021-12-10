#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QHash>
#include <QtGlobal>
#include <QEvent>
constexpr int validApplicationCode(0);
constexpr int errorApplicationCode(-1);

enum class DPin_t : quint32
{
    D2 = 2,
    D3 = 3,
    D4 = 4,
    D5 = 5,
    D6 = 6,
    D7 = 7,
    D8 = 8,
    D9 = 9,
    D10 = 10,
    D11 = 11,
    D12 = 12,
    D13 = 13
};

enum class BtnIndex_t: int
{
    Button0 = 0,
    Button1,
    Button2,
    Button3,
    Button4,
    Button5,
    Button6,
    Button7,
    Button8,
    Button9,
    Button10
};

enum class ButtonEventType: int
{
    Invalid,
    Press,
    Release,
    Hold
};
constexpr QEvent::Type InvalidType = QEvent::Type::None;
inline QEvent::Type btnEventToQtEvent(ButtonEventType e)
{
    switch(e)
    {
    case ButtonEventType::Press:{return QEvent::Type::KeyPress;}
    case ButtonEventType::Release:{return QEvent::Type::KeyRelease;}
    default:{return InvalidType;}
    }
};

namespace ApiConstants
{
constexpr quint32 SerialSpeed = 115200;
using CmdType = char;
constexpr CmdType EventPrefix = '@';
constexpr CmdType DebugPrefix = '#';
constexpr CmdType SysInfoPrefix = ':';
constexpr CmdType PressCmd = 'p';
constexpr CmdType ReleaseCmd = 'r';
constexpr CmdType HoldCmd = 'h';

const QHash<CmdType, ButtonEventType> ButtonEventMapping =
{
    {PressCmd, ButtonEventType::Press},
    {ReleaseCmd, ButtonEventType::Release},
    {HoldCmd, ButtonEventType::Hold}
};

}; //namespace ApiConstants

#endif // CONSTANTS_H
