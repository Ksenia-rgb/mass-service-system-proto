#ifndef DEVICE_H
#define DEVICE_H

#include <deque>

#include "calendarentry.h"
#include "msstime.h"
#include "types.h"

namespace mss
{
  namespace base
  {
    struct Device: CalendarEntry
    {
      CalendarEntry bid;
      MssTime time_use;

      Device();

      bool isFree(MssTime system_time);
      std::ostream& print(std::ostream& out) override;

      // В приборе хранится копия календарной записи, там только id, time, type
      // На приборе надо зафиксировать заявку именно в тот момент, как она туда попала
    };

    class DeviceGang
    {
    public:
      DeviceGang(const ProducerDeviceConfig& config);

      size_t size();
      Device& operator[](size_t index);

      MssTime setBid(CalendarEntry bid, MssTime system_time);

      double getAvgWorkload(MssTime system_time);
    private:
      ProducerDeviceConfig config_;
      std::deque< Device > gang_;
      size_t index_ptr_;

      size_t selectDevice(MssTime system_time);
      MssTime getTimeService();
    };
  }
}

#endif
