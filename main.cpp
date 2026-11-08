#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QIcon>

#include "backend/gui/system-controller.h"
#include "backend/gui/custom-plot-item.h"

int main(int argc, char* argv[])
{
  mss::gui::SystemController system_controller;

  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/images/comp-icon.jpg"));

  QQmlApplicationEngine engine;

  qmlRegisterType< mss::gui::PDConfigController >("mss", 1, 0, "PDConfigControllerType");
  qmlRegisterType< mss::gui::CustomPlotItem >("charts", 1, 0, "CustomPlotItemType");

  qmlRegisterSingletonInstance("mss", 1, 0, "ProducerConfigController", system_controller.getProducerConfig());
  qmlRegisterSingletonInstance("mss", 1, 0, "DeviceConfigController", system_controller.getDeviceConfig());
  qmlRegisterSingletonInstance("mss", 1, 0, "BufferConfigController", system_controller.getBufferConfig());
  qmlRegisterSingletonInstance("mss", 1, 0, "SystemStepController", system_controller.getSystemStepController());
  qmlRegisterSingletonInstance("mss", 1, 0, "SystemAutoController", system_controller.getSystemAutoController());
  qmlRegisterSingletonInstance("mss", 1, 0, "SystemController", &system_controller);

  engine.addImportPath(":/qml");
  engine.load("qrc:/qml/main.qml");

  QThreadPool::globalInstance()->setMaxThreadCount(1);
  return app.exec();
}
