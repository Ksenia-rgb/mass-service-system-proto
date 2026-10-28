#include "calendarentry.h"

#include <iomanip>

mss::base::CalendarEntry::CalendarEntry():
  id(0),
  time(0.0),
  type(false)
{}

std::ostream& mss::base::CalendarEntry::print(std::ostream& out)
{
  return out << id << '\t' << std::fixed << std::setprecision(3) << time.time_sec << "\t\t" << type;
}
