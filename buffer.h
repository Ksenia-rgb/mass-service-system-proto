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
      Buffer(size_t capacity);

      bool isIndexValid(size_t index);
      size_t getServiceBidIndex();
      size_t getRejectBidIndex(CalendarEntry entry);
      bool addBid(CalendarEntry entry);
    private:
      std::vector< std::pair< bool, base::CalendarEntry > > buffer_;
      size_t index_ptr_;

      size_t selectPlace();
      size_t selectServiceBid();
      size_t selectRejectBid();
    };
  }
}

#endif
