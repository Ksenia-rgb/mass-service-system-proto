#ifndef MSSTIME_H
#define MSSTIME_H

#include <QDateTime>
#include <ios>

namespace mss
{
  namespace base
  {
    struct MssTime
    {
      double time_sec;

      MssTime();
      MssTime(double start_sec);

      bool isNull();

      void operator+=(const MssTime& a);
      void operator-=(const MssTime& a);
    };

    bool operator==(const MssTime& a, const MssTime& b);
    bool operator!=(const MssTime& a, const MssTime& b);
    bool operator>(const MssTime& a, const MssTime& b);
    bool operator>=(const MssTime& a, const MssTime& b);
    bool operator<(const MssTime& a, const MssTime& b);
    bool operator<=(const MssTime& a, const MssTime& b);

    MssTime operator+(const MssTime& a, const MssTime& b);
    MssTime operator-(const MssTime& a, const MssTime& b);

    std::ostream& operator<<(std::ostream& out, const MssTime& a);
  }
}

#endif
