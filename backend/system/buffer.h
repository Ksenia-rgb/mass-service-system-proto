#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include "calendarentry.h"
#include "types.h"

namespace mss
{
  namespace base
  {
    class Buffer
    {
    public:
      Buffer(const BufferConfig& config);

      size_t size();
      CalendarEntry get(size_t index);

      bool addBid(CalendarEntry entry);
      size_t getServiceBidIndex();
      CalendarEntry getRejectBid(const CalendarEntry& entry);

      std::ostream& print(std::ostream& out);
    private:
      BufferConfig config_;
      std::vector< std::pair< bool, CalendarEntry > > buffer_;
      size_t index_ptr_;

      size_t selectPlace();
      size_t selectServiceBid();
      size_t selectRejectBid();

      // В буфере хранятся копии календарных записей, там только id, time, type
      // В буфере надо зафиксировать заявку именно в тот момент, как она туда попала
    };
  }
}

#endif
