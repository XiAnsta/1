#include "Backend.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  // Enable High DPI Support
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
      Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

  QGuiApplication app(argc, argv);
  app.setOrganizationName("TEM Systems");
  app.setApplicationName("TEM_Acquisition");

  QQmlApplicationEngine engine;

  // Instantiate our C++ backend
  Backend backend;

  // Inject backend into QML root context
  engine.rootContext()->setContextProperty("backend", &backend);

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
