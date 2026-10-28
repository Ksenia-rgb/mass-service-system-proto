#ifndef CALENDARENTRY_H
#define CALENDARENTRY_H

#include <iostream>

#include "msstime.h"

namespace mss
{
  namespace base
  {
    struct CalendarEntry
    {
      size_t id;
      MssTime time;
      bool type;

      CalendarEntry();
      virtual std::ostream& print(std::ostream& out);
    };
  }
}

#endif
