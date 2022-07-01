#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QIcon>
#include <QQuickStyle>

#include "mavlink/MavlinkStreamer.h"
#include "uav/UAV.h"
#include "Configuration.h"

// #include "VideoViewV4L2Item.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QIcon::setThemeName("light");
    app.setWindowIcon(QIcon(":/icons/logo.png"));

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
    QScopedPointer<Configuration> uavConfiguration(new Configuration(new QSettings("settings.ini", QSettings::IniFormat)));
    qmlRegisterSingletonInstance("Finco", 1, 0, "UAV", uavInstance.get());
    qmlRegisterSingletonInstance("Finco", 1, 0, "Configuration", uavConfiguration.get());
    qmlRegisterType<Connection>("Finco", 1, 0, "Connection");
    qmlRegisterType<Sensors>("Finco", 1, 0, "Sensors");
    qmlRegisterType<Positioning>("Finco", 1, 0, "Positioning");
    qmlRegisterType<Mission>("Finco", 1, 0, "Mission");
    qmlRegisterType<MissionItem>("Finco", 1, 0, "MissionItem");
    qmlRegisterType<PhotoPayload>("Finco", 1, 0, "PhotoPayload");
    // qmlRegisterType<VideoViewV4L2Item>("Finco", 1, 0, "VideoViewV4L2Item");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    engine.load(url);


    return app.exec();
}
