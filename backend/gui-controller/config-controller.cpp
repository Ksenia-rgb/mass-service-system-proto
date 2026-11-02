#include "config-controller.h"

#include <sstream>

mss::control::ConfigController::ConfigController(QObject* parent)
{}

void mss::control::ConfigController::enterProducerCnt(std::string cnt)
{
  config_.produce_cnt = std::stoull(cnt);
}

void mss::control::ConfigController::enterDeviceCnt(std::string cnt)
{
  config_.device_cnt = std::stoull(cnt);
}

void mss::control::ConfigController::enterBufferCap(std::string cnt)
{
  config_.buffer_cap = std::stoull(cnt);
}

std::string mss::control::ConfigController::strConfig()
{
  std::stringstream str;
  config_.print(str);
  str << std::endl;

  return str.str();
}
