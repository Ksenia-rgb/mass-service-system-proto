#ifndef SYSTEM_H
#define SYSTEM_H

#include <QDateTime>

#include <cstddef>
#include <vector>

#include "buffer.h"
#include "calendar.h"
#include "device.h"
#include "producer.h"

namespace mss
{
  class System
  {
  public:
    System(size_t produce_cnt, size_t device_cnt, size_t buffer_cap);

    size_t determineNextEvent();
    void analyseEvent(size_t index);
    void eventModIncomeBid(size_t index);
    void eventModFreeDevice(size_t index);
    void eventModEnd(size_t index);
  private:
    QDateTime time_now_;
    size_t produce_cnt_, device_cnt_, buffer_cap_;

    base::Calendar calendar_;
    std::vector< base::Producer > prods_;
    base::DeviceGang devices_;
    base::Buffer buffer_;

    QDateTime getTimeIncomeBid();
  };
}

#endif
