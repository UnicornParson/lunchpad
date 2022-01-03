#include "keyinjector.h"
#include <QCoreApplication>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QWidget>
#include <QThread>
#include "windows.h"
#include "winconstants.h"
#include "winsendwrapper.h"

namespace
{
[[maybe_unused]] constexpr NativeKeyEvent_t defaultEvent{WinConstants::eVK::KEY_RETURN, 0};
[[maybe_unused]] constexpr NativeKeyEvent_t invalidEvent{WinConstants::eVK::KEY_INVALID, 0};
[[maybe_unused]] constexpr UINT InvalidNativeMsg(0);


const KeyMapping_t DefaultKeyMapping =
{
    {0,  KeySeq_t{WinConstants::eVK::KEY_RETURN}},
    {1,  KeySeq_t{WinConstants::eVK::KEY_CONTROL, WinConstants::eVK::KEY_S}},
    {2,  KeySeq_t{WinConstants::eVK::KEY_CONTROL, WinConstants::eVK::KEY_C}},
    {3,  KeySeq_t{WinConstants::eVK::KEY_CONTROL, WinConstants::eVK::KEY_V}},
    {4,  KeySeq_t{WinConstants::eVK::KEY_B}},
    {5,  KeySeq_t{WinConstants::eVK::KEY_1}},
    {6,  KeySeq_t{WinConstants::eVK::KEY_2}},
    {7,  KeySeq_t{WinConstants::eVK::KEY_3}},
    {8,  KeySeq_t{WinConstants::eVK::KEY_4}},
    {9,  KeySeq_t{WinConstants::eVK::KEY_5}},
    {10,  KeySeq_t{WinConstants::eVK::KEY_6}},
    {11,  KeySeq_t{WinConstants::eVK::KEY_7}},
    {12,  KeySeq_t{WinConstants::eVK::KEY_8}},
    {13,  KeySeq_t{WinConstants::eVK::KEY_9}},
    {14,  KeySeq_t{WinConstants::eVK::KEY_0}}
}; // DefaultKeyMapping
}; // namespace


KeyInjector::KeyInjector(QObject *parent) :
    QObject(parent)
{
    m_keyMapping = DefaultKeyMapping;
}

void KeyInjector::execButtonEvent(ButtonEventType e, int key)
{
    qDebug() << "exec virtual key" << key;
    HWND hWindowHandle = GetActiveWindow();

    if(hWindowHandle == nullptr)
    {
        hWindowHandle = GetForegroundWindow();
        if(hWindowHandle == nullptr)
        {
            qWarning() << "no active window";
            return;
        }
    }

    bool ok = false;
    KeySeq_t seq = getKeyEvent(key, ok);
    if(seq.isEmpty())
    {
        qWarning() << "no events";
        return;
    }
    bool sendrc = false;
    switch(e)
    {
    case ButtonEventType::Press:
    {
        sendrc = WinSendWrapper::sendPressSeq(hWindowHandle, seq);
        break;
    }
    case ButtonEventType::Release:
    {
        sendrc = WinSendWrapper::sendReleaseSeq(hWindowHandle, seq);
        break;
    }
    default:
    {
        qDebug() << "ignore event" << static_cast<int>(e);
        sendrc = true;
    }
    }

    if(!sendrc)
    {
        qWarning() << "cannot process event"  << static_cast<int>(e) << "[" << seq << "]";
    }
}

const KeySeq_t KeyInjector::getKeyEvent(int key, bool& ok)
{
    if(m_keyMapping.contains(key))
    {
        ok = true;
        return m_keyMapping.value(key);
    }
    ok = false;
    return KeySeq_t();
}

