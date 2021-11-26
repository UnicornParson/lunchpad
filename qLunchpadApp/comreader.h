#ifndef COMREADER_H
#define COMREADER_H

#include <QObject>
#include "constants.h"
#include <QtSerialPort/QSerialPort>

class ComReader : public QObject
{
    Q_OBJECT
public:
    explicit ComReader(QObject *parent = nullptr);
    QStringList comList();
    bool open(const QString& port);
    void close();
    bool isOpened() const;
    bool read()ж
signals:
    void onButtonEvent(ButtonEvent e);

public slots:
private:
    QSerialPort m_port;
};

#endif // COMREADER_H
