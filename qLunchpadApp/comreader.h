#ifndef COMREADER_H
#define COMREADER_H

#include <QObject>
#include "constants.h"
#include <QtSerialPort/QSerialPort>
#include <QAtomicInteger>
#include <QTimer>

class ComReader : public QObject
{
    Q_OBJECT
public:
    explicit ComReader(QObject *parent = nullptr);
    QStringList comList();
    bool open(const QString& port);
    void close();
    bool isOpened() const;
    bool read(int timeout);

signals:
    void onButtonEvent(ButtonEventType e, int key);
    void onStatEvent(const QString& msg);
public slots:

    void onReportTimeout();
private:
    bool processEventString(const QString& e);
    QSerialPort m_port;
    QAtomicInteger<quint64> m_receivedEvents;
    QAtomicInteger<quint64> m_droppedEvents;
    QTimer* m_statTimer;
    //QAtomicInteger<quint64> m_receivedEvents;
};

#endif // COMREADER_H
