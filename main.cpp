#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QIcon>

#include "mavlink/MavlinkStreamer.h"
#include "uav/UAV.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QIcon::setThemeName("light");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SGCS2_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;

    QScopedPointer<UAV> uavInstance(new UAV(new MavlinkStreamer()));
    qmlRegisterSingletonInstance("Finco", 1, 0, "UAV", uavInstance.get());
    qmlRegisterType<Connection>("Finco", 1, 0, "Connection");
    qmlRegisterType<Sensors>("Finco", 1, 0, "Sensors");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    engine.load(url);


    return app.exec();
}
