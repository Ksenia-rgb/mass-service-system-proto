#ifndef DEVICE_H
#define DEVICE_H

#include <deque>

#include "calendarentry.h"
#include "msstime.h"

namespace mss
{
  namespace base
  {
    struct Device: CalendarEntry
    {
      CalendarEntry bid;

      Device();
      std::ostream& print(std::ostream& out) override;

      bool isFree(MssTime system_time);
    };

    class DeviceGang
    {
    public:
      DeviceGang(size_t size, size_t prod_rate_per_hour);

      size_t size();
      const Device& get(size_t index) const;
      Device& get(size_t index);

      bool setBid(CalendarEntry bid, MssTime system_time);
    private:
      std::deque< Device > gang_;
      size_t index_ptr_;
      size_t prod_rate_per_hour_;

      size_t selectDevice(MssTime system_time);
      MssTime getTimeFree(MssTime system_time);
    };
  }
}

#endif
