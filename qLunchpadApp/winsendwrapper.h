#ifndef WINSENDWRAPPER_H
#define WINSENDWRAPPER_H
#include "windows.h"
#include "keytypes.h"

class WinSendWrapper
{
public:
    // non creatable class
    WinSendWrapper() = delete;
    WinSendWrapper(WinSendWrapper&) = delete;
    WinSendWrapper(WinSendWrapper&&) = delete;

    static bool sendPressSeq(HWND hWnd, const KeySeq_t& seq);
    static bool sendReleaseSeq(HWND hWnd, const KeySeq_t& seq);

private:
    static LRESULT sendWinEvent(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
}; // class WinSendWrapper

#endif // WINSENDWRAPPER_H
