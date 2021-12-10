#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QObject>
#include <QThread>
#include "comreader.h"
#include "keyinjector.h"

class Executor : public QThread
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = nullptr);
    void setComPort(const QString& portname);


protected:
    virtual void run() Q_DECL_OVERRIDE;

    QString m_portName;
    ComReader* m_reader;
    KeyInjector m_injector;
};

#endif // EXECUTOR_H
