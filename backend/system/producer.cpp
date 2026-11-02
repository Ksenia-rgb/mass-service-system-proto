#include "producer.h"

#include "distribution.h"

mss::base::Producer::Producer():
  CalendarEntry(),
  bid_cnt(0),
  reject_cnt(0),
  time_on_device(0),
  time_in_buffer(0)
{}

double mss::base::Producer::getRejectProb()
{
  if (bid_cnt == 0)
  {
    throw std::logic_error("Count of generated bids is zero");
  }
  return reject_cnt * 1.0 / bid_cnt;
}

double mss::base::Producer::getAvgTimeInSystem()
{
  return (time_on_device.time_sec + time_in_buffer.time_sec) / bid_cnt;
}

std::ostream& mss::base::Producer::print(std::ostream& out)
{
  CalendarEntry::print(out);
  return out << '\t' << bid_cnt << '\t' << reject_cnt << '\t' << time_on_device << '\t' << time_in_buffer;
}

mss::base::ProducerGang::ProducerGang(const ProducerConfig& config):
  config_(config),
  gang_(config.cnt, Producer{})
{}

size_t mss::base::ProducerGang::size()
{
  return gang_.size();
}

mss::base::Producer& mss::base::ProducerGang::operator[](size_t index)
{
  return gang_[index];
}

void mss::base::ProducerGang::setOnDeviceTime(size_t index, MssTime time_service)
{
  gang_[index].time_on_device += time_service;
}

void mss::base::ProducerGang::setInBufferTime(size_t index, MssTime time_in_buffer)
{
  gang_[index].time_in_buffer += time_in_buffer;
}

void mss::base::ProducerGang::reject(size_t index)
{
  gang_[index].reject_cnt++;
}

mss::base::MssTime mss::base::ProducerGang::generateNextBid(size_t index, MssTime system_time)
{
  MssTime time = system_time + getGenerateBidTime();
  gang_[index].time = time;
  gang_[index].type = true;
  gang_[index].bid_cnt++;
  return time;
}

double mss::base::ProducerGang::getAvgRejectProb()
{
  double prob_sum = 0.0;
  for (size_t i = 0; i < gang_.size(); i++)
  {
    prob_sum += gang_[i].getRejectProb();
  }
  return prob_sum / gang_.size();
}

double mss::base::ProducerGang::getAvgTimeInSystem()
{
  double time_sum = 0.0;
  for (size_t i = 0; i < gang_.size(); i++)
  {
    time_sum += gang_[i].getAvgTimeInSystem();
  }
  return time_sum;
}

mss::base::MssTime mss::base::ProducerGang::getGenerateBidTime()
{
  // Закон распределения времени генерации заявок на источниках (равномерный)

  if (config_.distrib_law == DistribLaw::Exp)
  {
    return distribution::getExpTime(config_.rate_per_hour);
  }
  return distribution::getUniformTime({config_.time_min}, {config_.time_max});
}
