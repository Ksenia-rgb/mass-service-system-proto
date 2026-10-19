#ifndef PRODUCER_H
#define PRODUCER_H

#include "calendar.h"

namespace mss
{
  namespace base
  {
    class Producer
    {
    public:
      Producer(size_t id = 0);
      CalendarEntry generate();
    private:
      size_t id_;
    };
  }
}

#endif
