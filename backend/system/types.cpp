#include "types.h"

mss::ProducerConfig::ProducerConfig():
  cnt_min(1),
  cnt_max(100),
  cnt(10),
  time_min(5.0),
  time_max(120.0),
  rate_per_hour(120.0),
  dist_law(DistLaw::Uniform)
{}

mss::DeviceConfig::DeviceConfig():
  cnt_min(1),
  cnt_max(100),
  cnt(10),
  time_min(5.0),
  time_max(120.0),
  rate_per_hour(120.0),
  dist_law(DistLaw::Exp)
{}

mss::BufferConfig::BufferConfig():
  cap_min(1),
  cap_max(100),
  cap(20)
{}

