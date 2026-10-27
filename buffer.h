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

      size_t size();
      const CalendarEntry& get(size_t index) const;
      CalendarEntry& get(size_t index);

      bool addBid(CalendarEntry entry);
      size_t getServiceBidIndex();
      size_t getRejectBidId(CalendarEntry entry);

      std::ostream& print(std::ostream& out);
    private:
      std::vector< std::pair< bool, CalendarEntry > > buffer_;
      size_t index_ptr_;

      size_t selectPlace();
      size_t selectServiceBid();
      size_t selectRejectBid();
    };
  }
}

#endif
