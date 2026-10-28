#include "device.h"

#include <random>
#include <iomanip>

#include "msstime.h"

mss::base::Device::Device():
  CalendarEntry(),
  bid()
{}

std::ostream& mss::base::Device::print(std::ostream& out)
{
  out << id << '\t' << std::fixed << std::setprecision(3) << time.time_sec << "\t\t" << type;
  return out << '\t' << bid.id << '\t' << std::fixed << std::setprecision(3) << bid.time.time_sec;
}

bool mss::base::Device::isFree(MssTime system_time)
{
  return time.isNull() || time < system_time;
}

mss::base::DeviceGang::DeviceGang(size_t size, size_t prod_rate_per_hour):
  gang_(size),
  index_ptr_(0),
  prod_rate_per_hour_(prod_rate_per_hour)
{}

size_t mss::base::DeviceGang::size()
{
  return gang_.size();
}

const mss::base::Device& mss::base::DeviceGang::get(size_t index) const
{
  return gang_[index];
}

mss::base::Device& mss::base::DeviceGang::get(size_t index)
{
  return gang_[index];
}

bool mss::base::DeviceGang::setBid(CalendarEntry bid, MssTime system_time)
{
  // Поставить заявку на обслуживание на один из приборов

  size_t index = selectDevice(system_time);
  if (index >= gang_.size())
  {
    return false;
  }

  Device& device = gang_[index];
  device.bid = bid;
  device.time = getTimeFree(system_time);
  device.type = true;
  return true;
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

mss::base::MssTime mss::base::DeviceGang::getTimeFree(MssTime system_time)
{
  // Экспоненциальный закон распределения времени обслуживания заявок на приборах

  const double mu_per_sec = prod_rate_per_hour_ / 3600.0;

  std::random_device rd;
  std::mt19937 rng(rd());
  std::exponential_distribution< double > distrib(mu_per_sec);
  double seconds = distrib(rng);

  return system_time + MssTime{seconds};
}
