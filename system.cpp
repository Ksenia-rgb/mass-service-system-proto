#include "system.h"

mss::System::System(size_t produce_cnt, size_t device_cnt, size_t buffer_cap):
  calendar(produce_cnt + device_cnt + 1, {{}, false}),
  prods(produce_cnt),
  devices(device_cnt),
  buffer(buffer_cap)
{}

size_t mss::System::determineNextEvent()
{
  size_t index = 0;
  for (size_t i = 1; i < calendar.size(); i++)
  {
    if (calendar[i].type && calendar[i].time < calendar[index].time)
    {
      index = i;
    }
  }
  calendar[index].type = false;
  return index;
}

mss::System::EventType mss::System::analyseEvent(size_t index)
{
  if (index < prods.size())
  {
    return mss::System::EventType::IncomeBid;
  }
  if (index < devices.size())
  {
    return mss::System::EventType::DeviceFree;
  }
  return mss::System::EventType::End;
}


