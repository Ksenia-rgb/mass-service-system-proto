#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstddef>

#include "buffer.h"
#include "calendar.h"
#include "device.h"
#include "producer.h"

namespace mss
{
  struct SystemConfig
  {
    size_t produce_cnt;
    size_t device_cnt;
    size_t buffer_cap;
    size_t gen_start_time, gen_finish_time;
    size_t prod_rate_per_hour;
  };
  class System
  {
  public:
    System(const SystemConfig& config);

    void step();
    void end();

    std::pair< size_t, base::CalendarEntry > determineNextEvent();
    void analyseEvent(size_t index, base::CalendarEntry entry);
    void eventModIncomeBid(size_t index, base::CalendarEntry entry);
    void eventModFreeDevice();
    void eventModEnd();
  private:
    base::MssTime system_time_;
    bool is_end_;

    base::ProducerGang prods_;
    base::DeviceGang devices_;
    base::Buffer buffer_;

    base::Calendar calendar_;

    std::ostream& print(std::ostream& out);
  };
}

#endif
