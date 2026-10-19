#include "buffer.h"

mss::base::Buffer::Buffer(size_t capacity):
  buffer_(capacity, {false, {}}),
  index_ptr_(0)
{}

bool mss::base::Buffer::isIndexValid(size_t index)
{
  return index < buffer_.size();
}

size_t mss::base::Buffer::getServiceBidIndex()
{
  size_t index = selectServiceBid();
  if (isIndexValid(index))
  {
    buffer_[index].first = false;
  }
  return index;
}

size_t mss::base::Buffer::getRejectBidIndex(CalendarEntry entry)
{
  size_t index = selectRejectBid();
  if (isIndexValid(index))
  {
    buffer_[index].second = entry;
  }
  return index;
}

bool mss::base::Buffer::addBid(CalendarEntry entry)
{
  size_t index = selectPlace();
  if (!isIndexValid(index))
  {
    return false;
  }
  buffer_[index].first = true;
  buffer_[index].second = entry;
  return true;
}

size_t mss::base::Buffer::selectPlace()
{
  if (!buffer_[index_ptr_].first)
  {
    return index_ptr_++;
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
  if (index_ptr_ == 0)
  {
    return buffer_.size() - 1;
  }
  return index_ptr_ - 1;
}

