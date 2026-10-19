#include "device.h"

#include <QDateTime>

#include <random>

bool mss::base::Device::isFree(QDateTime system_time)
{
  return time_free.isNull() || time_free < system_time;
}

mss::base::DeviceGang::DeviceGang(size_t size):
  gang_(size),
  index_ptr_(0)
{}

bool mss::base::DeviceGang::setBid(CalendarEntry entry, QDateTime system_time)
{
  size_t index = selectDevice(system_time);
  if (index >= gang_.size())
  {
    return false;
  }

  Device& device = gang_[index];
  device.entry = entry;
  device.time_free = getTimeFree(system_time);
  return true;
}

size_t mss::base::DeviceGang::selectDevice(QDateTime system_time)
{
  if (gang_[index_ptr_].isFree(system_time))
  {
    return index_ptr_++;
  }
  for (size_t i = (index_ptr_ + 1) % gang_.size(); i != index_ptr_; i++)
  {
    if (gang_[i].isFree(system_time))
    {
      index_ptr_ = (i + 1) % gang_.size();
      return i;
    }
  }
  return gang_.size();
}

QDateTime mss::base::DeviceGang::getTimeFree(QDateTime system_time)
{
  const double mu_per_sec = gang_.size() / 3600.0;

  std::random_device rd;
  std::mt19937 rng(rd());
  std::exponential_distribution< double > distrib(mu_per_sec);
  double seconds = distrib(rng);

  qint64 ms = static_cast< qint64 >(std::llround(seconds * 1000.0));
  return system_time.addMSecs(ms);
}
