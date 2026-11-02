#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>


#include "backend/system/system.h"
#include "backend/gui-controller/config-controller.h"


int main(int argc, char* argv[])
{
  mss::ProducerConfig producer_config{1, 100, 3, 5, 20, mss::DistribLaw::Uniform, 100};
  mss::DeviceConfig device_config{1, 100, 2, 5, 20, mss::DistribLaw::Exp, 100};
  mss::BufferConfig buffer_config{1, 100, 5};

  mss::System system({producer_config, device_config, buffer_config});
  std::string command;
  while (!(std::cin >> command).eof())
  {
    system.step();
  }
  system.finish();

  std::cout << system.getAvgRejectProb() << '\n' << system.getAvgTimeInSystem() << '\n' << system.getAvgWorkload() << std::endl;
}
