#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "msstime.h"

namespace mss
{
  namespace distribution
  {
    base::MssTime getExpTime(double rate_per_hour);
    base::MssTime getUniformTime(base::MssTime start, base::MssTime finish);
  }
}

#endif
