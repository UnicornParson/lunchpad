#include "comreader.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QList>

ComReader::ComReader(QObject *parent) : QObject(parent)
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
    if(isOpened())
    {
        close();
    }
    m_port.setPortName(port);
    if(!m_port.open(QIODevice::ReadOnly))
    {
        qWarning() << "cannot open port" ;
        return false;
    }
    return true;
}

void ComReader::close()
{
    m_port.close();
}

bool ComReader::isOpened() const
{
    return m_port.isOpen();
}
