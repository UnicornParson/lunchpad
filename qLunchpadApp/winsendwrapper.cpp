#include "winsendwrapper.h"

#include <QtGlobal>
#include <QDebug>

namespace
{
[[maybe_unused]] constexpr LRESULT LRESULT_OK(0);
}

LRESULT WinSendWrapper::sendWinEvent(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
    return PostMessage(hWnd, Msg, wParam, lParam);
    //    return SendMessage(hWnd, Msg, wParam, lParam);
}

bool WinSendWrapper::sendPressSeq(HWND hWnd, const KeySeq_t& seq)
{
    bool rc = true;
    uint lp = 0;
    for(uint keycode: seq)
    {
        lp = MapVirtualKey(keycode, 0) << 16;
        LRESULT lresult = sendWinEvent(hWnd, WM_KEYDOWN, keycode, lp);
        if(lresult != LRESULT_OK)
        {
            qWarning() << "send message keydown not ok. code:" << keycode << " result:" << lresult << "reason" << GetLastError();
            rc = false;
            break;
        }
    }
    return rc;
}

bool WinSendWrapper::sendReleaseSeq(HWND hWnd, const KeySeq_t& seq)
{
    bool rc = true;
    for(uint keycode: seq)
    {
        LRESULT lresult = sendWinEvent(hWnd, WM_KEYUP, keycode, 0);
        if(lresult != LRESULT_OK)
        {
            qWarning() << "send message keyup not ok. code:" << keycode << " result:" << lresult << "reason" << GetLastError();
            rc = false;
            break;
        }
    }
    return rc;
}
