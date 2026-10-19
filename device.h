#ifndef DEVICE_H
#define DEVICE_H

#include <QDateTime>

#include "calendar.h"

namespace mss
{
  namespace base
  {
    struct Device
    {
      CalendarEntry entry;
      QDateTime time_free;

      bool isFree(QDateTime system_time);
    };

    class DeviceGang
    {
    public:
      DeviceGang(size_t size);

      bool setBid(CalendarEntry entry, QDateTime system_time);
    private:
      std::vector< Device > gang_;
      size_t index_ptr_;

      size_t selectDevice(QDateTime system_time);
      QDateTime getTimeFree(QDateTime system_time);
    };
  }
}

#endif
