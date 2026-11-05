#include "full-system-controller.h"

mss::gui::FullSystemController::FullSystemController():
  system_step_({producer_config_.getConfig(), device_config_.getConfig(), buffer_config_.getConfig()})
{}

mss::gui::PDConfigController* mss::gui::FullSystemController::getProducerConfigPtr()
{
  return &producer_config_;
}

mss::gui::PDConfigController* mss::gui::FullSystemController::getDeviceConfigPtr()
{
  return &device_config_;
}

mss::gui::BufferConfigController* mss::gui::FullSystemController::getBufferConfigPtr()
{
  return &buffer_config_;
}

mss::gui::SystemStepController* mss::gui::FullSystemController::getSystemStepPtr()
{
  return &system_step_;
}

mss::gui::SystemAutoController* mss::gui::FullSystemController::getSystemAutoPtr()
{
  return &system_auto_;
}
