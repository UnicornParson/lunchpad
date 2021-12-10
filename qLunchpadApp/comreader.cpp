#include "comreader.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QList>
namespace
{
constexpr int reportInterval(100);
}
ComReader::ComReader(QObject *parent) :
    QObject(parent),
    m_receivedEvents(0),
    m_droppedEvents(0),
    m_statTimer(nullptr)
{

}

QStringList ComReader::comList()
{
    QStringList l;
    for(const QSerialPortInfo& portInfo : QSerialPortInfo::availablePorts())
    {
        l.append(portInfo.portName());
    }
    return l;
}

bool ComReader::open(const QString& port)
{
    m_receivedEvents = 0;
    m_droppedEvents = 0;
    if(m_statTimer != nullptr)
    {
        m_statTimer->deleteLater();
        m_statTimer = nullptr;
    }
    m_statTimer = new QTimer(this);
    m_statTimer->setInterval(reportInterval);
    connect(m_statTimer, &QTimer::timeout, this, &ComReader::onReportTimeout);
    m_statTimer->start();
    if(isOpened())
    {
        close();
    }
    m_port.setPortName(port);
    m_port.setBaudRate(ApiConstants::SerialSpeed);
    if(!m_port.open(QIODevice::ReadOnly))
    {
        qWarning() << "cannot open port" ;
        return false;
    }
    return true;
}

void ComReader::onReportTimeout()
{
    QString msg = QString("ComReader[%1] received: %2, dropped: %3").arg(quintptr(this)).arg(m_receivedEvents).arg(m_droppedEvents);
    qWarning() << "onReportTimeout";
    emit onStatEvent(msg);
}

void ComReader::close()
{
    m_port.close();
    if(m_statTimer != nullptr)
    {
        m_statTimer->stop();
        m_statTimer->deleteLater();
        m_statTimer = nullptr;
    }
}

bool ComReader::isOpened() const
{
    return m_port.isOpen();
}

bool ComReader::read(int timeout)
{
    if(m_port.waitForReadyRead(timeout))
    {

        QByteArray msg = m_port.readAll();
        QStringList events;
        for (QString s: QString(msg).split(ApiConstants::EventPrefix, QString::SkipEmptyParts))
        {
            processEventString(s.trimmed());
        }
    }
    return true;
}

bool ComReader::processEventString(const QString& e)
{

    bool bRet = false;
    m_receivedEvents++;
    do
    {
        if(e.size() < 2)
        {
            qWarning() << "invalid event" << e;
        }
        QChar echar = e[0];
        if(ApiConstants::ButtonEventMapping.contains(echar.toLatin1()))
        {
            ButtonEventType event = ApiConstants::ButtonEventMapping.value(echar.toLatin1(), ButtonEventType::Invalid);
            if(event == ButtonEventType::Invalid)
            {
                qWarning() << "cannot parce event type" << echar;
                break;
            }
            QString keynumstr = e.right(e.length() - 1);
            qDebug() << "keycode" << keynumstr;
            int code = keynumstr.toInt(&bRet);
            if(!bRet)
            {
                qWarning() << "cannot parce button code" << keynumstr;
                break;
            }
            emit onButtonEvent(event, code);
        }
        else
        {
            qWarning() << "unknown parce event type" << echar;
            break;
        }
    }
    while(false);
    if(!bRet)
    {
        qWarning() << "event" << e << "dropped";
        m_droppedEvents++;
    }
    return bRet;
}
