#ifndef PRODUCER_H
#define PRODUCER_H

#include <deque>

#include "msstime.h"
#include "calendarentry.h"
#include "types.h"

namespace mss
{
  namespace base
  {
    struct Producer: CalendarEntry
    {
      size_t bid_cnt;
      size_t reject_cnt;
      MssTime time_on_device;
      MssTime time_in_buffer;

      Producer();

      double getRejectProb();
      double getAvgTimeInSystem();

      std::ostream& print(std::ostream& out) override;
    };

    class ProducerGang
    {
    public:
      ProducerGang(const ProducerDeviceConfig& config);

      size_t size();
      Producer& operator[](size_t index);

      void setOnDeviceTime(size_t index, MssTime time_service);
      void setInBufferTime(size_t index, MssTime time_in_buffer);
      void reject(size_t index);
      MssTime generateNextBid(size_t index, MssTime system_time);

      double getAvgRejectProb();
      double getAvgTimeInSystem();
    private:
      ProducerDeviceConfig config_;
      std::deque< Producer > gang_;

      MssTime getGenerateBidTime();
    };
  }
}

#endif
