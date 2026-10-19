#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include "calendar.h"

namespace mss
{
  namespace base
  {
    class Buffer
    {
    public:
      Buffer();
    private:
      std::vector< base::CalendarEntry > buffer;
    };
  }
}

#endif
