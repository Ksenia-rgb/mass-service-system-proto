#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstddef>

#include "buffer.h"
#include "calendar.h"
#include "device.h"
#include "producer.h"
#include "types.h"

namespace mss
{
  class System
  {
  public:
    System(const SystemConfig& config);

    void step();
    void finish();

    double getAvgRejectProb();
    double getAvgTimeInSystem();
    double getAvgWorkload();
  private:
    base::MssTime system_time_;
    bool is_end_;

    base::ProducerGang prods_;
    base::DeviceGang devices_;
    base::Buffer buffer_;
    base::Calendar calendar_;

    std::pair< size_t, base::CalendarEntry > determineNextEvent();
    void analyseEvent(size_t index, base::CalendarEntry entry);
    void eventModIncomeBid(base::CalendarEntry entry);
    void eventModFreeDevice();
    void eventModEnd();

    std::ostream& print(std::ostream& out);
  };
}

#endif
