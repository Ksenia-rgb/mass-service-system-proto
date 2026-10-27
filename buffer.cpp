#include "buffer.h"

#include <iostream>

mss::base::Buffer::Buffer(size_t capacity):
  buffer_(capacity, {false, {}}),
  index_ptr_(0)
{}

size_t mss::base::Buffer::size()
{
  return buffer_.size();
}

const mss::base::CalendarEntry& mss::base::Buffer::get(size_t index) const
{
  return buffer_[index].second;
}

mss::base::CalendarEntry& mss::base::Buffer::get(size_t index)
{
  return buffer_[index].second;
}

size_t mss::base::Buffer::getServiceBidIndex()
{
  // Получить заявку на обслуживание из буфера
  // - Это место в буфере теперь свободно

  size_t index = selectServiceBid();
  if (index < size())
  {
    buffer_[index].first = false;
  }
  return index;
}

size_t mss::base::Buffer::getRejectBidId(CalendarEntry entry)
{
  // Получить заявку для отказа
  // - Это место в буфере теперь займет новая заявка

  size_t index = selectRejectBid();
  if (index < size())
  {
    size_t res = buffer_[index].second.id;
    buffer_[index].second = entry;
    return res;
  }

  return 0;
}

bool mss::base::Buffer::addBid(CalendarEntry entry)
{
  // Добавить заявку в буфер

  size_t index = selectPlace();
  if (!(index < size()))
  {
    return false;
  }
  buffer_[index].first = true;
  buffer_[index].second = entry;
  return true;
}

size_t mss::base::Buffer::selectPlace()
{
  // Дисциплина буферизации:
  // - Заполнение буффера по кольцу

  if (!buffer_[index_ptr_].first)
  {
    size_t index_res = index_ptr_;
    index_ptr_ = (index_ptr_ + 1) % buffer_.size();
    return index_res;
  }
  for (size_t i = (index_ptr_ + 1) % buffer_.size(); i != index_ptr_; i++)
  {
    if (!buffer_[i].first)
    {
      index_ptr_ = (i + 1) % buffer_.size();
      return i;
    }
  }
  return buffer_.size();
}

size_t mss::base::Buffer::selectServiceBid()
{
  // Дисциплина постановки на обслуживания - выбора заявки из буфера на обслуживание:
  // - Приоритет по номеру источника
  // - Приоритет по времени обслуживания (старые приориететнее)

  size_t i = 0;
  while (i < buffer_.size() && !buffer_[i].first)
  {
    i++;
  }

  if (i == buffer_.size())
  {
    return i;
  }

  size_t res = i;
  for (; i < buffer_.size(); i++)
  {
    if (buffer_[i].first && buffer_[i].second.id < buffer_[res].second.id)
    {
      res = i;
    }
    else if (buffer_[i].first && buffer_[i].second.id == buffer_[res].second.id)
    {
      if (buffer_[i].second.time < buffer_[res].second.time)
      {
        res = i;
      }
    }
  }
  return res;
}

size_t mss::base::Buffer::selectRejectBid()
{
  // Дисциплина отказа:
  // - Отказ последней поступившей в буфер заявке

  size_t i = 0;
  while (i < buffer_.size() && !buffer_[i].first)
  {
    i++;
  }

  if (i == buffer_.size())
  {
    return i;
  }

  size_t res = i++;
  MssTime max_time = buffer_[res].second.time;
  for (; i < buffer_.size(); i++)
  {
    if (buffer_[i].second.time > max_time)
    {
      res = i;
      max_time = buffer_[i].second.time;
    }
  }

  return res;
}

std::ostream& mss::base::Buffer::print(std::ostream& out)
{
  if (buffer_[0].first)
  {
    buffer_[0].second.print(out);
  }
  else
  {
    out << 0;
  }

  for (size_t i = 1; i < buffer_.size(); i++)
  {
    out << '\n';
    if (buffer_[i].first)
    {
      buffer_[i].second.print(out);
    }
    else
    {
      out << 0;
    }
  }
  return out;
}
