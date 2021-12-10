#ifndef KEYINJECTOR_H
#define KEYINJECTOR_H

#include <QObject>
#include "constants.h"
#include <QEvent>
#include <QHash>
#include <QPair>

//using KeyEvent_t = QPair<Qt::Key, int>;
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

using KeyMapping_t = QHash<int, NativeKeyEvent_t>;



class KeyInjector : public QObject
{
    Q_OBJECT
public:
    explicit KeyInjector(QObject *parent = nullptr);
    void execButtonEvent(ButtonEventType e, int key);
signals:

public slots:
private:
    NativeKeyEvent_t getKeyEvent(int key, bool& ok);
    bool sendEvent(KeyEvent_t ke);

    KeyMapping_t m_keyMapping;
};

#endif // KEYINJECTOR_H
