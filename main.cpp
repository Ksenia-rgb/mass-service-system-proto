#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include "backend/gui-controller/producer-config-controller.h"


int main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  qmlRegisterType< mss::control::ProducerConfigController >("ProducerConfigController", 1, 0, "ProducerConfigController");

  const QUrl url("qrc:/qml/main.qml");
  engine.load(url);
  return app.exec();
}
