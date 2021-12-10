#include "executor.h"
#include "comreader.h"
#include "constants.h"
#include <QDebug>
Executor::Executor(QObject *parent):
    QThread(parent),
    m_reader(nullptr),
    m_injector(this)
{

}

void Executor::run()
{
    if(m_portName.isEmpty())
    {
        qWarning() << "no port name";
        return;
    }

    auto destroyReader = [this]()
    {
        if(m_reader != nullptr)
        {
            if(m_reader->isOpened())
            {
                m_reader->close();
            }
            m_reader->deleteLater();
            m_reader = nullptr;
        }
    };

    destroyReader();

    m_reader = new ComReader(this);
    connect(m_reader, &ComReader::onButtonEvent, [this](ButtonEventType e, int key)
    {
        qWarning() << "e:" << static_cast<int>(e)  << "key:" << key;
        m_injector.execButtonEvent(e, key);
    });
    connect(m_reader, &ComReader::onStatEvent, [](const QString& msg)
    {
        qWarning() << "stat:" << msg;
    });
    do
    {
        if(!m_reader->open(m_portName))
        {
            qWarning() << "cannot open" << m_portName;
            break;
        }

        while(!isInterruptionRequested())
        {
            m_reader->read(100);
        }
    }
    while(false);
    destroyReader();
}

void Executor::setComPort(const QString& portname)
{
    m_portName = portname;
}
