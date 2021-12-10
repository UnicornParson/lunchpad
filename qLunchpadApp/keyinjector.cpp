#include "keyinjector.h"
#include <QCoreApplication>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QWidget>
#include <QThread>
#include "windows.h"
#include "winconstants.h"
namespace
{
[[maybe_unused]] constexpr NativeKeyEvent_t defaultEvent{WinConstants::eVK::KEY_RETURN, 0};
[[maybe_unused]] constexpr NativeKeyEvent_t invalidEvent{WinConstants::eVK::KEY_INVALID, 0};
[[maybe_unused]] constexpr UINT InvalidNativeMsg(0);

const KeyMapping_t DefaultKeyMapping =
{
    {0,  NativeKeyEvent_t{WinConstants::eVK::KEY_RETURN,  0}},
    {1,  NativeKeyEvent_t{WinConstants::eVK::KEY_RETURN,  0}},
    {2,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD0, 0}},
    {3,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD1, 0}},
    {4,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD2, 0}},
    {5,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD3, 0}},
    {6,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD4, 0}},
    {7,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD5, 0}},
    {8,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD6, 0}},
    {9,  NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD7, 0}},
    {10, NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD8, 0}},
    {11, NativeKeyEvent_t{WinConstants::eVK::KEY_NUMPAD9, 0}}
};


[[maybe_unused]] inline bool sendWinEvent(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
    //(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
    //PostMessage(windowHandle, WM_KEYDOWN, VK_LEFT, 0x414B0001);
    [[maybe_unused]] LRESULT rc = SendMessage(hWnd, Msg, wParam, lParam);
    qDebug() << rc;
    return (rc == 0);
}


[[maybe_unused]] inline UINT ButtonEventTypeToMsg(ButtonEventType e)
{
    switch (e)
    {
    case ButtonEventType::Press:{return WM_KEYDOWN;}
    case ButtonEventType::Release:{return WM_KEYUP;}
    case ButtonEventType::Hold:{break;/*ignore hold*/}
    case ButtonEventType::Invalid:
    {
        qWarning() << "invalid event" << static_cast<int>(e);
    }
    }
    return InvalidNativeMsg;
};

};





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
        qWarning() << "no active window";
        hWindowHandle = GetForegroundWindow();
        if(hWindowHandle == nullptr)
        {
            qWarning() << "no fg window";
            return;
        }

    }
    if(e == ButtonEventType::Invalid)
    {
        qWarning() << "invalid event type";
        return;
    }

    bool ok = false;
    NativeKeyEvent_t ke = getKeyEvent(key, ok);


    if(ke.keycode == WinConstants::eVK::KEY_INVALID)
    {
        qWarning() << "invalid win key code";
        return;
    }
    UINT nativeEvent = ButtonEventTypeToMsg(e);
    if(nativeEvent == InvalidNativeMsg)
    {
        qWarning() << "invalid win native message";
        return;
    }
    sendWinEvent(hWindowHandle, nativeEvent, (WPARAM)ke.keycode, (LPARAM)ke.params);

    //SendMessage(hWindowHandle, WM_SETTEXT, NULL, (LPARAM)_T("hello"));
}

NativeKeyEvent_t KeyInjector::getKeyEvent(int key, bool& ok)
{
    if(m_keyMapping.contains(key))
    {
        ok = true;
        return m_keyMapping.value(key);
    }
    ok = false;
    return invalidEvent;
}

