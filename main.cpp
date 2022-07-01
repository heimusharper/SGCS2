#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "version.h"

#include <QLocale>
#include <QTranslator>
#include <QIcon>
#include <QQuickStyle>

#include "mavlink/MavlinkStreamer.h"
#include "uav/UAV.h"
#include "Configuration.h"

// #include "VideoViewV4L2Item.h"

void installTranslator(const QString &f)
{
    auto cur = QDir::current();
    if (cur.cd("translations"))
    {
        for (const QString &x : cur.entryList({"*.qm"}))
        {
            if (!x.contains("Photobase"))
                continue;
            int i = x.indexOf("_");
            int k = x.indexOf(".qm");
            QString trs = x.mid(i+1, k - (i+1));
            if (trs.compare(f) == 0) {
                QTranslator *translator = new QTranslator;
                if (translator->load(cur.absoluteFilePath(x))) {
                    qApp->installTranslator(translator);
                } else
                    delete translator;
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QIcon::setThemeName("light");
    app.setWindowIcon(QIcon(":/icons/logo.png"));
    app.setApplicationName(QString("Photobase SGCS v%1.%2.%3-%4")
                           .arg(SGCS2_VERSION_MAJOR)
                           .arg(SGCS2_VERSION_MINOR)
                           .arg(SGCS2_VERSION_PATH)
                           .arg(SGCS2_VERSION_HASH));

    QQmlApplicationEngine engine;

    QScopedPointer<UAV> uavInstance(new UAV(new MavlinkStreamer()));
    QScopedPointer<Configuration> uavConfiguration(new Configuration(new QSettings("settings.ini", QSettings::IniFormat)));

    QObject::connect(uavConfiguration.get(), &Configuration::languageChanged, [](const QString &t){
        installTranslator(t);
    });
    installTranslator(uavConfiguration.get()->language());

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
