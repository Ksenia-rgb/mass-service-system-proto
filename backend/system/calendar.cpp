#include "calendar.h"

#include <cstddef>
#include <iostream>

mss::base::Calendar::Calendar(ProducerGang& prods, DeviceGang& devices, MssTime system_time):
  calendar_(prods.size() + devices.size() + 1, nullptr),
  end_entry_(std::make_unique< CalendarEntry >())
{
  size_t i = 0;
  for (; i < prods.size(); i++)
  {
    calendar_[i] = &prods.get(i);
    calendar_[i]->id = i + 1;
    calendar_[i]->time = system_time;
    calendar_[i]->type = false;
  }
  for (; i < prods.size() + devices.size(); i++)
  {
    calendar_[i] = &devices.get(i - prods.size());
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
  for (size_t i = 1; i < calendar_.size(); i++)
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

std::ostream& mss::base::Calendar::print(std::ostream& out)
{
  // Вывести текущее состояние календаря

  out << 0 << '\t';
  calendar_[0]->print(out);

  for (size_t i = 1; i < calendar_.size(); i++)
  {
    out << '\n' << i << '\t';
    calendar_[i]->print(out);
  }
  return out;
}
