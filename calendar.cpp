#include "calendar.h"

#include <cstddef>

mss::base::Calendar::Calendar(size_t produce_cnt, size_t device_cnt):
  calendar_(produce_cnt + device_cnt + 1)
{
  for (size_t i = 0; i < calendar_.size(); i++)
  {
    calendar_[i].id = i;
    calendar_[i].type = false;
  }
}

bool mss::base::Calendar::isIndexValid(size_t index)
{
  return index < calendar_.size();
}

size_t mss::base::Calendar::next()
{
  size_t index = 0;
  for (size_t i = 1; i < calendar_.size(); i++)
  {
    if (calendar_[i].type && calendar_[i].time < calendar_[index].time)
    {
      index = i;
    }
  }
  return index;
}

mss::base::CalendarEntry mss::base::Calendar::get(size_t index)
{
  CalendarEntry entry = calendar_[index];
  calendar_[index].type = false;
  return entry;
}

bool mss::base::Calendar::set(size_t index, QDateTime time)
{
  if (!isIndexValid(index))
  {
    return false;
  }
  calendar_[index].time = time;
  calendar_[index].type = true;
  return true;
}

