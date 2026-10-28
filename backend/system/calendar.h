#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>

#include "msstime.h"
#include "calendarentry.h"
#include "device.h"
#include "producer.h"

namespace mss
{
  namespace base
  {
    class Calendar
    {
    public:
      Calendar(ProducerGang& prods, DeviceGang& devices, MssTime system_time);

      size_t next();

      CalendarEntry get(size_t index);

      std::ostream& print(std::ostream& out);
    private:
      std::vector< CalendarEntry* > calendar_;
      std::unique_ptr< CalendarEntry > end_entry_;
    };
  }
}

#endif
