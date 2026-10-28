#include "msstime.h"

mss::base::MssTime::MssTime():
  time_sec(0.0)
{}

mss::base::MssTime::MssTime(double start):
  time_sec(start)
{}

bool mss::base::MssTime::isNull()
{
  return time_sec == 0;
}

void mss::base::MssTime::operator+=(const MssTime& a)
{
  time_sec += a.time_sec;
}

bool mss::base::operator==(const MssTime& a, const MssTime& b)
{
  return a.time_sec == b.time_sec;
}

bool mss::base::operator!=(const MssTime& a, const MssTime& b)
{
  return a.time_sec != b.time_sec;
}

bool mss::base::operator>(const MssTime& a, const MssTime& b)
{
  return a.time_sec > b.time_sec;
}

bool mss::base::operator>=(const MssTime& a, const MssTime& b)
{
  return a.time_sec >= b.time_sec;
}

bool mss::base::operator<(const MssTime& a, const MssTime& b)
{
  return a.time_sec < b.time_sec;
}

bool mss::base::operator<=(const MssTime& a, const MssTime& b)
{
  return a.time_sec <= b.time_sec;
}

mss::base::MssTime mss::base::operator+(const MssTime& a, const MssTime& b)
{
  return {a.time_sec + b.time_sec};
}
