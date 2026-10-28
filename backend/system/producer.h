#ifndef PRODUCER_H
#define PRODUCER_H

#include <deque>

#include "msstime.h"
#include "calendarentry.h"

namespace mss
{
  namespace base
  {
    struct Producer: CalendarEntry
    {
      size_t reject_cnt;

      Producer();
      std::ostream& print(std::ostream& out) override;
    };

    class ProducerGang
    {
    public:
      ProducerGang(size_t size, size_t gen_start_time, size_t gen_finish_time);

      size_t size();
      const Producer& get(size_t index) const;
      Producer& get(size_t index);

      MssTime generateNextBid(size_t index, MssTime system_time);
      void reject(size_t index);
    private:
      std::deque< Producer > gang_;
      size_t gen_start_time_;
      size_t gen_finish_time_;

      MssTime getTimeIncomeBid();
    };
  }
}

#endif
