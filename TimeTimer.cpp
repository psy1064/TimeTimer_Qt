#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "TimeTimerMgr.h"
#include "SoundListModelItem.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<SoundListModelItem>("SoundListItem", 1,0, "SoundListModelItem");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/TimeTimer.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }
    , Qt::QueuedConnection);

    engine.load(url);

    TimeTimerMgr timerMgr;
    timerMgr.SetEngine(&engine);
    return app.exec();
}
