#include <QCoreApplication>
#include <QFile>
#include <iostream>
#include <QDebug>
#include "constants.h"
#include "comreader.h"
namespace
{
static const QString HelpFile("://readme.md");

}

void errMsg(const QString& s)
{
    std::cerr << s.toStdString() << std::endl << std::flush;
}

void logMsg(const QString& s)
{
    std::cout << s.toStdString() << std::endl << std::flush;
}

void printHelp()
{
    QFile f(HelpFile);
    if(f.open(QIODevice::ReadOnly))
    {
        logMsg(QString(f.readAll()));
    }
    else
    {
        qWarning("cannot open help file");
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    ComReader reader;
    QString comName;
    QString presetName;
    for(const QString& arg: args)
    {
        if(arg == "-h" || arg == "--help")
        {
            printHelp();
            return validApplicationCode;
        }
        else if(arg == "-l" || arg == "--list")
        {
            QStringList comList = reader.comList();
            for(const QString& cname : comList)
            {
                logMsg(cname);
            }
        }
        else if (presetName.isEmpty())
        {
            presetName = arg.trimmed();
        }
        else if (comName.isEmpty())
        {
            comName = arg.toUpper().trimmed();
        }
        else
        {
            errMsg(QString("invalid argument %1").arg(arg));
            printHelp();
            return errorApplicationCode;
        }

        if(presetName.isEmpty() || comName.isEmpty())
        {
            errMsg("invalid argument list");
            printHelp();
            return errorApplicationCode;
        }
    }
    return a.exec();
}
