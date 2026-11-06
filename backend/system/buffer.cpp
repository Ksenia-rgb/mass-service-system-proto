#include "buffer.h"

mss::base::Buffer::Buffer(const BufferConfig& config):
  config_(config),
  buffer_(config.cap, {false, {}}),
  index_ptr_(0)
{}

size_t mss::base::Buffer::size()
{
  return buffer_.size();
}

mss::base::CalendarEntry mss::base::Buffer::get(size_t index)
{
  buffer_[index].first = false;
  return buffer_[index].second;
}

size_t mss::base::Buffer::getServiceBidIndex()
{
  // Получить заявку на обслуживание из буфера
  // - Это место в буфере теперь свободно

  return selectServiceBid();
}

mss::base::CalendarEntry mss::base::Buffer::getRejectBid(const CalendarEntry& entry)
{
  // Получить заявку для отказа
  // - Это место в буфере теперь займет новая заявка

  size_t index = selectRejectBid();
  if (index < size())
  {
    CalendarEntry res = buffer_[index].second;
    buffer_[index].second = entry;
    return res;
  }

  return {};
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

  size_t res = 0;
  while (res < buffer_.size() && !buffer_[res].first)
  {
    res++;
  }

  if (res == buffer_.size())
  {
    return res;
  }

  for (size_t i = res + 1; i < buffer_.size(); i++)
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

  size_t res = 0;
  while (res < buffer_.size() && !buffer_[res].first)
  {
    res++;
  }

  if (res == buffer_.size())
  {
    return res;
  }

  for (size_t i = res + 1; i < buffer_.size(); i++)
  {
    if (buffer_[i].second.time > buffer_[res].second.time)
    {
      res = i;
    }
  }

  return res;
}

mss::BufferResultsStr mss::base::Buffer::resultsStr() const
{
  BufferResultsStr res(buffer_.size());
  for (size_t i = 0; i < buffer_.size(); i++)
  {
    if (buffer_[i].first)
    {
      res[i] = BufferRowResultStr{
        QString::number(buffer_[i].second.id),
        QString::number(buffer_[i].second.time.time_sec)
      };
    }
    else
    {
      res[i] = BufferRowResultStr{"0", "0"};
    }
  }

  return res;
}
