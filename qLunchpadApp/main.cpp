#include <QCoreApplication>
#include <QFile>
#include <QTextCodec>
#include <iostream>
#include <QDebug>
#include "tools.h"
#include "constants.h"
#include "comreader.h"
#include "executor.h"

using namespace Tools;

namespace
{
CONST_LITERAL HelpFile("://readme.md");
CONST_LITERAL LOGS_BASE_DIR("logs/");
CONST_LITERAL CRASH_BASE_DIR("crash/");
CONST_LITERAL LOGS_CFG_FILENAME("log.cfg");
CONST_LITERAL LOG_FILENAME("console.log");
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
        LOG_WARNING("cannot open help file");
    }
}

int main(int argc, char *argv[])
{
    LogGlobalSetup::self().setConsoleLoggingEnabled(false);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    ComReader reader;
    QString comName;
    QString presetName;
    bool firstArg = true;
    LogGlobalSetup::self().setConsoleLoggingEnabled(true);
    QString path = QString(argv[0]);
    int lastSlash = path.lastIndexOf('\\');
    QString binDir = path.left(lastSlash + 1);
    QString logDir = CTools::pathNormalize(binDir + LOGS_BASE_DIR + QDateTime::currentDateTime().toString("dd.MM.yyyy_hh.mm.ss"));
    LogStarter::initLogging(logDir, LOG_FILENAME, CTools::pathNormalize(binDir + LOGS_BASE_DIR + LOGS_CFG_FILENAME));

    for(const QString& arg: args)
    {
        if(firstArg)
        {
            firstArg = false;
            continue;
        }
        if(arg == "-h" || arg == "--help")
        {
            printHelp();
            return validApplicationCode;
        }
        else if(arg == "-l" || arg == "--list" )
        {
            QStringList comList = reader.comList();
            for(const QString& cname : comList)
            {
                logMsg(cname);
            }
            return validApplicationCode;
        }
        else if (presetName.isEmpty())
        {
            presetName = arg.trimmed();
            continue;
        }
        else if (comName.isEmpty())
        {
            comName = arg.toUpper().trimmed();
            continue;
        }
        else
        {
            LOG_ERROR(QString("invalid argument %1").arg(arg));
            printHelp();
            return errorApplicationCode;
        }
    }
    if(presetName.isEmpty() || comName.isEmpty())
    {
        LOG_ERROR("invalid argument list");
        printHelp();
        return errorApplicationCode;
    }
    Executor* e = new Executor();
    e->setComPort(comName);
    e->start();
    getchar();
    e->requestInterruption();
    e->wait();

    return a.exec();
}
