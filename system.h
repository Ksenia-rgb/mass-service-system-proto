#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstddef>
#include <vector>

#include "calendar.h"
#include "device.h"
#include "producer.h"

namespace mss
{
  class System
  {
  public:
    enum EventType {IncomeBid, DeviceFree, End};

    System(size_t produse_cnt, size_t device_cnt, size_t buffer_cap);

    size_t determineNextEvent();
    EventType analyseEvent(size_t index);
    void eventModIncomeBid(size_t index);
    void eventModFreeDevice(size_t index);
    void eventModEnd(size_t index);
  private:
    std::vector< base::CalendarEntry > calendar;
    std::vector< base::Producer > prods;
    std::vector< base::Device > devices;
    std::vector< base::CalendarEntry > buffer;

    void disciplineBuffering();
    void disciplineReject();
    void disciplineSelectBid();
    void disciplineSelectDevice();

    /*blocks::DeterminerNextEvent determiner;
    blocks::AnalyserEvent analyser;
    blocks::EventModIncomeBid mod_income_bid;
    blocks::EventModDeviceFree mod_device_free;
    blocks::EventModEnd mod_end;*/
  };
}

#endif
