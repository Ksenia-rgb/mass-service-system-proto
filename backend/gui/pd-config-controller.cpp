#include "pd-config-controller.h"

mss::gui::PDConfigController::PDConfigController(QObject* parent)
{}

int mss::gui::PDConfigController::getCntMin() const
{
  return config_.cnt_min;
}

int mss::gui::PDConfigController::getCntMax() const
{
  return config_.cnt_max;
}

int mss::gui::PDConfigController::getCnt() const
{
  return config_.cnt;
}

double mss::gui::PDConfigController::getTimeMin() const
{
  return config_.time_min;
}

double mss::gui::PDConfigController::getTimeMax() const
{
  return config_.time_max;
}

double mss::gui::PDConfigController::getRate() const
{
  return config_.rate_per_hour;
}

bool mss::gui::PDConfigController::getDistLaw() const
{
  return config_.dist_law == mss::DistLaw::Exp;
}

void mss::gui::PDConfigController::setCntMin(int val)
{
  config_.cnt_min = val;
  emit cntMinChanged(val);
}

void mss::gui::PDConfigController::setCntMax(int val)
{
  config_.cnt_max = val;
  emit cntMaxChanged(val);
}

void mss::gui::PDConfigController::setCnt(int val)
{
  config_.cnt = val;
  emit cntChanged(val);
}

void mss::gui::PDConfigController::setTimeMin(double val)
{
  config_.time_min = val;
  emit timeMinChanged(val);
}

void mss::gui::PDConfigController::setTimeMax(double val)
{
  config_.time_max = val;
  emit timeMaxChanged(val);
}

void mss::gui::PDConfigController::setRate(double val)
{
  config_.rate_per_hour = val;
  emit rateChanged(val);
}

void mss::gui::PDConfigController::setDistLaw(bool is_exp)
{
  if (is_exp)
  {
    config_.dist_law = mss::DistLaw::Exp;
  }
  else
  {
    config_.dist_law = mss::DistLaw::Uniform;
  }
  emit distLawChanged(is_exp);
}

mss::ProducerDeviceConfig mss::gui::PDConfigController::getConfig()
{
  return config_;
}
