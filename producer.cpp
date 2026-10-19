#include "producer.h"

mss::base::Producer::Producer(size_t id = 0):
  id_(id)
{}

mss::base::CalendarEntry mss::base::Producer::generate()
{
  return {QDateTime::currentDateTime(), true};
}
