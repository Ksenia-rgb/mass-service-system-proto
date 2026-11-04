#include "buffer-config-controller.h"

mss::gui::BufferConfigController::BufferConfigController(QObject* parent)
{}

int mss::gui::BufferConfigController::getCapMin() const
{
  return config_.cap_min;
}

int mss::gui::BufferConfigController::getCapMax() const
{
  return config_.cap_max;
}

int mss::gui::BufferConfigController::getCap() const
{
  return config_.cap;
}

void mss::gui::BufferConfigController::setCapMin(int val)
{
  config_.cap_min = val;
  emit capMinChanged(val);
}

void mss::gui::BufferConfigController::setCapMax(int val)
{
  config_.cap_max = val;
  emit capMaxChanged(val);
}

void mss::gui::BufferConfigController::setCap(int val)
{
  config_.cap = val;
  emit capChanged(val);
}
