#include "Backend.h"
#include "PlaybackBackend.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>
#include <QDirIterator>

int main(int argc, char *argv[]) {
  // Enable High DPI Support
  QApplication::setHighDpiScaleFactorRoundingPolicy(
      Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

  QApplication app(argc, argv);
  app.setOrganizationName("TEM Systems");
  app.setApplicationName("TEM_Acquisition");

  QQmlApplicationEngine engine;

  // Print all QRC resources
  QDirIterator it(":", QDirIterator::Subdirectories);
  while (it.hasNext()) {
    qDebug() << it.next();
  }

  Backend backend;

  qmlRegisterType<PlaybackBackend>("TEM.System", 1, 0, "PlaybackBackend");

  // Inject backend into QML root context
  engine.rootContext()->setContextProperty("cppBackend", &backend);

  // Add QRC root to module import paths so it finds the "BS" module
  engine.addImportPath("qrc:/");

  // Load the main view
  const QUrl url(QStringLiteral("qrc:/BSContent/App.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  engine.load(url);

  return app.exec();
}
