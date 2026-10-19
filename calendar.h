#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>

#include <QDateTime>

namespace mss
{
  namespace base
  {
    struct CalendarEntry
    {
      QDateTime time;
      bool type;
    };

    class Calendar
    {
    public:
      Calendar(size_t produce_cnt, size_t device_cnt);
      CalendarEntry next();
    private:
      std::vector< CalendarEntry > calendar;
    };
  }
}

#endif
