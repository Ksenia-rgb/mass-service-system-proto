#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QIcon>

#include "backend/gui/system-step-controller.h"

int main(int argc, char* argv[])
{
  mss::gui::SystemStepController system_step_controller;

  QGuiApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/images/comp-icon.jpg"));

  QQmlApplicationEngine engine;

  qmlRegisterType< mss::gui::PDConfigController >("mss", 1, 0, "PDConfigControllerType");

  qmlRegisterSingletonInstance("mss", 1, 0, "SystemStepController", &system_step_controller);
  qmlRegisterSingletonInstance("mss", 1, 0, "ProducerConfigController", system_step_controller.getProducerConfig());
  qmlRegisterSingletonInstance("mss", 1, 0, "DeviceConfigController", system_step_controller.getDeviceConfig());
  qmlRegisterSingletonInstance("mss", 1, 0, "BufferConfigController", system_step_controller.getBufferConfig());

  engine.addImportPath(":/qml");
  engine.load("qrc:/qml/main.qml");
  return app.exec();
}
