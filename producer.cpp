#include "producer.h"

#include <random>
#include <iomanip>

mss::base::Producer::Producer():
  CalendarEntry(),
  reject_cnt(0)
{}

mss::base::ProducerGang::ProducerGang(size_t size, size_t gen_start_time, size_t gen_finish_time):
  gang_(size, Producer{}),
  gen_start_time_(gen_start_time),
  gen_finish_time_(gen_finish_time)
{}

std::ostream& mss::base::Producer::print(std::ostream& out)
{
  out << id << '\t' << std::fixed << std::setprecision(3) << time.time_sec << "\t\t" << type;
  return out << '\t' << reject_cnt;
}

size_t mss::base::ProducerGang::size()
{
  return gang_.size();
}

const mss::base::Producer& mss::base::ProducerGang::get(size_t index) const
{
  return gang_[index];
}

mss::base::Producer& mss::base::ProducerGang::get(size_t index)
{
  return gang_[index];
}

mss::base::MssTime mss::base::ProducerGang::generateNextBid(size_t index, MssTime system_time)
{
  MssTime time = system_time + getTimeIncomeBid();
  gang_[index].time = time;
  gang_[index].type = true;
  return time;
}

void mss::base::ProducerGang::reject(size_t index)
{
  gang_[index].reject_cnt++;
}

mss::base::MssTime mss::base::ProducerGang::getTimeIncomeBid()
{
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution< double > dist(gen_start_time_, gen_finish_time_);

  double time_sec = dist(rng);
  return {time_sec};
}
