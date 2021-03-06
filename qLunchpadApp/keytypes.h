#ifndef KEYTYPES_H
#define KEYTYPES_H

#include "constants.h"
#include <QEvent>
#include <QHash>
#include <QPair>

struct KeyEvent_t
{
    Qt::Key qkey;
    int flags;
    unsigned short wVk;
    unsigned short wScan;
    quint32 dwFlags;


    KeyEvent_t() = default;
    KeyEvent_t(Qt::Key k):
        qkey(k),
        flags(0),
        wVk(0),
        wScan(0),
        dwFlags(0){}

    KeyEvent_t(const KeyEvent_t& o):
        qkey(o.qkey),
        flags(o.flags),
        wVk(o.wVk),
        wScan(o.wScan),
        dwFlags(o.dwFlags){}

    KeyEvent_t& operator=(const KeyEvent_t& o)
    {
        if(&o != this)
        {
            qkey=o.qkey;
            flags=o.flags;
            wVk=o.wVk;
            wScan=o.wScan;
            dwFlags=o.dwFlags;
        }
        return *this;
    }
};

struct NativeKeyEvent_t
{
    uint keycode;
    uint params;
};

using KeySeq_t = QList<uint>;
using KeyMapping_t_old = QHash<int, QList<NativeKeyEvent_t> >;
using KeyMapping_t = QHash<int, KeySeq_t>;


#endif // KEYTYPES_H
