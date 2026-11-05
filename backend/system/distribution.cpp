#include "distribution.h"

#include <random>

mss::base::MssTime mss::distribution::getExpTime(double rate_per_hour)
{
  static std::mt19937 rng(std::random_device{}());

  if (rate_per_hour <= 0)
  {
    throw std::logic_error("Incorrect rate per hour value");
  }

  const double rate_per_sec = rate_per_hour / 3600.0;
  std::exponential_distribution< double > dist(rate_per_sec);

  double time_sec = dist(rng);
  return {time_sec};
}

mss::base::MssTime mss::distribution::getUniformTime(base::MssTime start, base::MssTime finish)
{
  static std::mt19937 rng(std::random_device{}());

  if (start.isNull() || finish.isNull() || finish <= start)
  {
    throw std::logic_error("Incorrect start and finish time values");
  }

  std::uniform_real_distribution< double > dist(start.time_sec, finish.time_sec);

  double time_sec = dist(rng);
  return {time_sec};
}
