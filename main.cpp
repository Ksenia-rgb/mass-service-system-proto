#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QIcon>

#include "backend/gui/full-system-controller.h"


int main(int argc, char* argv[])
{
  mss::gui::FullSystemController controller;

  QGuiApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/images/comp-icon.jpg"));

  QQmlApplicationEngine engine;

  qmlRegisterType< mss::gui::PDConfigController >("Mss", 1, 0, "PDConfigControllerType");
  qmlRegisterType< mss::gui::BufferConfigController >("Mss", 1, 0, "BufferConfigControllerType");
  qmlRegisterType< mss::gui::SystemStepController >("Mss", 1, 0, "SystemStepControllerType");
  qmlRegisterType< mss::gui::SystemAutoController >("Mss", 1, 0, "SystemAutoControllerType");

  qmlRegisterSingletonInstance("Mss", 1, 0, "ProducerConfigController", controller.getProducerConfigPtr());
  qmlRegisterSingletonInstance("Mss", 1, 0, "DeviceConfigController", controller.getDeviceConfigPtr());
  qmlRegisterSingletonInstance("Mss", 1, 0, "BufferConfigController", controller.getBufferConfigPtr());
  qmlRegisterSingletonInstance("Mss", 1, 0, "SystemStepController", controller.getSystemStepPtr());
  qmlRegisterSingletonInstance("Mss", 1, 0, "SystemAutoController", controller.getSystemAutoPtr());

  const QUrl url("qrc:/qml/main.qml");
  engine.load(url);
  return app.exec();
}
