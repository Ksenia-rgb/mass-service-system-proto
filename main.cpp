#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <iostream>

#include "system.h"


int main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url("qrc:/qml/main.qml");
  engine.load(url);
  return app.exec();

  /*mss::SystemConfig config;
  std::cin >>
    config.produce_cnt >>
    config.device_cnt >>
    config.buffer_cap >>
    config.gen_start_time >>
    config.gen_finish_time >>
    config.prod_rate_per_hour;

  if (!std::cin)
  {
    std::cerr << "Incorrect arguments: enter produse count, device count, buffer capacity ";
    std::cerr << "generate start time in sec, generate finish time in sec, produse rate per hour" << std::endl;
    return 1;
  }

  mss::System system(config);
  std::string command;
  while (!(std::cin >> command).eof())
  {
    system.step();
  }
  system.end();*/
}
