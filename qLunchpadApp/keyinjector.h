#ifndef KEYINJECTOR_H
#define KEYINJECTOR_H

#include <QObject>
#include "keytypes.h"

class KeyInjector : public QObject
{
    Q_OBJECT
public:
    explicit KeyInjector(QObject *parent = nullptr);
    void execButtonEvent(ButtonEventType e, int key);
signals:

public slots:
private:
    const KeySeq_t getKeyEvent(int key, bool& ok);
    bool sendEvent(KeyEvent_t ke);

    KeyMapping_t m_keyMapping;
};

#endif // KEYINJECTOR_H
