#include "system-controller.h"

mss::gui::SystemController::SystemController(QObject* parent)
{}

mss::gui::PDConfigController* mss::gui::SystemController::getProducerConfig()
{
  return &producer_config_;
}

mss::gui::PDConfigController* mss::gui::SystemController::getDeviceConfig()
{
  return &device_config_;
}

mss::gui::BufferConfigController* mss::gui::SystemController::getBufferConfig()
{
  return &buffer_config_;
}

mss::gui::SystemStepController* mss::gui::SystemController::getSystemStepController()
{
  return &system_step_controller_;
}

mss::gui::SystemAutoController* mss::gui::SystemController::getSystemAutoController()
{
  return &system_auto_controller_;
}

void mss::gui::SystemController::prepareSystemStepController()
{
  SystemConfig config{producer_config_.getConfig(), device_config_.getConfig(), buffer_config_.getConfig()};
  system_step_controller_.setSystemConfig(std::move(config));
}

void mss::gui::SystemController::prepareSystemAutoController()
{
  SystemConfig config{producer_config_.getConfig(), device_config_.getConfig(), buffer_config_.getConfig()};
  system_auto_controller_.setSystemConfig(std::move(config));
}
