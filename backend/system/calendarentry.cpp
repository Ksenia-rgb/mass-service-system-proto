#include "calendarentry.h"

mss::base::CalendarEntry::CalendarEntry():
  id(0),
  time(),
  type(false)
{}

std::ostream& mss::base::CalendarEntry::print(std::ostream& out)
{
  return out << id << '\t' << time << "\t\t" << type;
}
