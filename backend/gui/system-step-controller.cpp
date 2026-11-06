#include "system-step-controller.h"

mss::gui::SystemStepController::SystemStepController(QObject* parent):
  system_(SystemConfig{})
{}

mss::gui::PDConfigController* mss::gui::SystemStepController::getProducerConfig()
{
  return &producer_config_;
}

mss::gui::PDConfigController* mss::gui::SystemStepController::getDeviceConfig()
{
  return &device_config_;
}

mss::gui::BufferConfigController* mss::gui::SystemStepController::getBufferConfig()
{
  return &buffer_config_;
}

QAbstractTableModel* mss::gui::SystemStepController::getCalendar()
{
  return &calendar_model_;
}

QAbstractTableModel* mss::gui::SystemStepController::getBuffer()
{
  return &buffer_model_;
}

QString mss::gui::SystemStepController::getSystemTime() const
{
  return system_time_;
}

void mss::gui::SystemStepController::start()
{
  system_ = System({producer_config_.getConfig(), device_config_.getConfig(), buffer_config_.getConfig()});
  setRows(system_.start());
}

void mss::gui::SystemStepController::step()
{
  setRows(system_.step());
}

void mss::gui::SystemStepController::finish()
{
  setRows(system_.finish());
}

void mss::gui::SystemStepController::setRows(const SystemResultsStr& res)
{
  calendar_model_.setRows(res.calendar_rows);
  buffer_model_.setRows(res.buffer_rows);
  system_time_ = res.system_time;
  emit systemTimeChanged(res.system_time);
}
