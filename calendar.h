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
      size_t id;
      QDateTime time;
      bool type;
    };

    class Calendar
    {
    public:
      Calendar(size_t produce_cnt, size_t device_cnt);

      bool isIndexValid(size_t index);
      size_t next();
      CalendarEntry get(size_t index);
      bool set(size_t index, QDateTime time);
    private:
      std::vector< CalendarEntry > calendar_;
    };
  }
}

#endif
