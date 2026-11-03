#include "producer-config-controller.h"

mss::control::ProducerConfigController::ProducerConfigController(QObject* parent)
{}

int mss::control::ProducerConfigController::getCntMin() const
{
  return config_.cnt_min;
}

int mss::control::ProducerConfigController::getCntMax() const
{
  return config_.cnt_max;
}

int mss::control::ProducerConfigController::getCnt() const
{
  return config_.cnt;
}

double mss::control::ProducerConfigController::getTimeMin() const
{
  return config_.time_min;
}

double mss::control::ProducerConfigController::getTimeMax() const
{
  return config_.time_max;
}

double mss::control::ProducerConfigController::getRate() const
{
  return config_.rate_per_hour;
}

bool mss::control::ProducerConfigController::getDistLaw() const
{
  return config_.dist_law == mss::DistLaw::Exp;
}

void mss::control::ProducerConfigController::setCntMin(int val)
{
  config_.cnt_min = val;
  emit cntMinChanged(val);
}

void mss::control::ProducerConfigController::setCntMax(int val)
{
  config_.cnt_max = val;
  emit cntMaxChanged(val);
}

void mss::control::ProducerConfigController::setCnt(int val)
{
  config_.cnt = val;
  emit cntChanged(val);
}

void mss::control::ProducerConfigController::setTimeMin(double val)
{
  config_.time_min = val;
  emit timeMinChanged(val);
}

void mss::control::ProducerConfigController::setTimeMax(double val)
{
  config_.time_max = val;
  emit timeMaxChanged(val);
}

void mss::control::ProducerConfigController::setRate(double val)
{
  config_.rate_per_hour = val;
  emit rateChanged(val);
}

void mss::control::ProducerConfigController::setDistLaw(bool is_exp)
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
