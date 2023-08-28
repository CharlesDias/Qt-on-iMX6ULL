#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QFile>

// Get the default Qt message handler.
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(0);

void CustomMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt = qFormatLogMessage(type, context, msg);
    QFile outFile("logfile.log");

    // Write message
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << Qt::endl;
    outFile.close();

    // Call the default handler.
    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

int main(int argc, char *argv[])
{
    qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz} %{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] %{file}:%{line} - %{message}");
    qInstallMessageHandler(CustomMessageOutput);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
