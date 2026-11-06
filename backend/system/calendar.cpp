#include "calendar.h"

#include <cstddef>

mss::base::Calendar::Calendar(ProducerGang& prods, DeviceGang& devices, MssTime system_time):
  calendar_(prods.size() + devices.size() + 1, nullptr),
  end_entry_(std::make_unique< CalendarEntry >()),
  is_finished(false)
{
  size_t i = 0;
  for (; i < prods.size(); i++)
  {
    calendar_[i] = &prods[i];
    calendar_[i]->id = i + 1;
    calendar_[i]->time = system_time;
    calendar_[i]->type = false;
  }
  for (; i < prods.size() + devices.size(); i++)
  {
    calendar_[i] = &devices[i - prods.size()];
    calendar_[i]->id = i - prods.size() + 1;
    calendar_[i]->time = system_time;
    calendar_[i]->type = false;
  }
  calendar_[i] = end_entry_.get();
  calendar_[i]->id = 0;
  calendar_[i]->time = system_time;
  calendar_[i]->type = false;
}

size_t mss::base::Calendar::next()
{
  // Получить индекс следующего события

  size_t index = 0;
  while (index < calendar_.size() && !calendar_[index]->type)
  {
    index++;
  }

  for (size_t i = index + 1; i < calendar_.size(); i++)
  {
    if (calendar_[i]->type && calendar_[i]->time < calendar_[index]->time)
    {
      index = i;
    }
  }

  return index;
}

mss::base::CalendarEntry mss::base::Calendar::get(size_t index)
{
  // Получить событие по индексу

  CalendarEntry entry = *calendar_[index];
  calendar_[index]->type = false;
  return entry;
}

void mss::base::Calendar::finish(MssTime system_time)
{
  end_entry_->time = system_time;
  end_entry_->type = true;
  is_finished = true;
}

bool mss::base::Calendar::isFinished()
{
  return is_finished;
}

bool mss::base::Calendar::hasEntries()
{
  for (size_t i = 0; i < calendar_.size(); i++)
  {
    if (calendar_[i]->type)
    {
      return true;
    }
  }
  return false;
}

mss::CalendarResultsStr mss::base::Calendar::resultsStr() const
{
  CalendarResultsStr res(calendar_.size());
  for (size_t i = 0; i < calendar_.size(); i++)
  {
    res[i] = CalendarRowResultStr{
      QString::number(calendar_[i]->id),
      QString::number(calendar_[i]->time.time_sec),
      QString::number(calendar_[i]->type)
    };
  }

  return res;
}
