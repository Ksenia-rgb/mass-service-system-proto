#ifndef CALENDARENTRY_H
#define CALENDARENTRY_H

#include "msstime.h"

namespace mss
{
  namespace base
  {
    struct CalendarEntry
    {
      size_t id;
      MssTime time; // для источника: время генерации заявки, для прибора: время освобождения
      bool type;

      CalendarEntry();
    };
  }
}

#endif
