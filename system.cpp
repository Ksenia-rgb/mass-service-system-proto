#include "system.h"

#include <cmath>

mss::System::System(size_t produce_cnt, size_t device_cnt, size_t buffer_cap):
  produce_cnt_(produce_cnt),
  device_cnt_(device_cnt),
  buffer_cap_(buffer_cap),
  calendar_(produce_cnt, device_cnt),
  prods_(produce_cnt),
  devices_(device_cnt),
  buffer_(buffer_cap)
{}

size_t mss::System::determineNextEvent()
{
  size_t index = calendar_.next();
  if (calendar_.isIndexValid(index))
  {
    time_now_ = calendar_.get(index).time;
  }
  return index;
}

void mss::System::analyseEvent(size_t index)
{
  if (index < produce_cnt_)
  {
    return eventModIncomeBid(index);
  }
  if (index < produce_cnt_ + device_cnt_)
  {
    return eventModFreeDevice(index);
  }
  return eventModEnd(index);
}

void mss::System::eventModIncomeBid(size_t index)
{
  if (devices_.setBid(calendar_[index], time_now_))
  {
    // set time free in calendar for this device
    return;
  }

}

QDateTime mss::System::getTimeIncomeBid()
{
  qint64 time = 5000;
  return QDateTime(time_now_).addMSecs(time);
}


