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
      void finish(MssTime system_time);
      bool isFinished();
      bool hasEntries();

      std::ostream& print(std::ostream& out);
    private:
      std::vector< CalendarEntry* > calendar_;
      std::unique_ptr< CalendarEntry > end_entry_;

      bool is_finished;

      // В календаре хранятся сами (ссылки) календарные записи, там полная информация
      // Календарь синхронизирован со всем состоянием системы

      // Только событие финиша хранится здесь уникально, для него нужны свои методы
    };
  }
}

#endif
