#include "device.h"

#include "msstime.h"
#include "distribution.h"

mss::base::Device::Device():
  CalendarEntry(),
  bid(),
  time_use()
{}

bool mss::base::Device::isFree(MssTime system_time)
{
  return time.isNull() || time <= system_time;
}

mss::base::DeviceGang::DeviceGang(const ProducerDeviceConfig& config):
  config_(config),
  gang_(config.cnt, Device{}),
  index_ptr_(0)
{}

size_t mss::base::DeviceGang::size()
{
  return gang_.size();
}

mss::base::Device& mss::base::DeviceGang::operator[](size_t index)
{
  return gang_[index];
}

mss::base::MssTime mss::base::DeviceGang::setBid(CalendarEntry bid, MssTime system_time)
{
  // Поставить заявку на обслуживание на один из приборов

  size_t index = selectDevice(system_time);
  if (index >= gang_.size())
  {
    return {};
  }

  MssTime time_service = getTimeService();

  Device& device = gang_[index];
  device.time = system_time + time_service;
  device.type = true;
  device.bid = bid;
  device.time_use += time_service;
  return time_service;
}

size_t mss::base::DeviceGang::selectDevice(MssTime system_time)
{
  // Дисциплина выбора прибора:
  // - Выбор прибора по кольцу

  if (gang_[index_ptr_].isFree(system_time))
  {
    size_t index_res = index_ptr_;
    index_ptr_ = (index_ptr_ + 1) % gang_.size();
    return index_res;
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

double mss::base::DeviceGang::getAvgWorkload(MssTime system_time)
{
  double time_sum = 0.0;
  for (size_t i = 0; i < gang_.size(); i++)
  {
    time_sum += gang_[i].time_use.time_sec;
  }
  return time_sum / gang_.size() / system_time.time_sec;
}

mss::base::MssTime mss::base::DeviceGang::getTimeService()
{
  // Закон распределения времени обслуживания заявок на приборах (экспоненциальный)

  if (config_.dist_law == DistLaw::Exp)
  {
    return distribution::getExpTime(config_.rate_per_hour);
  }
  return distribution::getUniformTime({config_.time_min}, {config_.time_max});
}
