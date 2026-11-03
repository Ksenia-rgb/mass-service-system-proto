#ifndef TYPES_H
#define TYPES_H

#include <cstddef>

namespace mss
{
  enum DistLaw {Exp, Uniform};

  struct ProducerConfig
  {
    size_t cnt_min;
    size_t cnt_max;

    size_t cnt;

    double time_min; // время генерации заявок на источниках
    double time_max;

    double rate_per_hour; // интенсивность генерации (кол-во заявок в единицу времени)
    DistLaw dist_law; // закон распределения времени генерации

    ProducerConfig();
  };

  struct DeviceConfig
  {
    size_t cnt_min;
    size_t cnt_max;

    size_t cnt;

    double time_min; // время обслуживания заявок на приборах
    double time_max;

    double rate_per_hour; // интенсивность обслуживания (кол-во заявок в единицу времени)
    DistLaw dist_law; // закон распределения времени обслуживания

    DeviceConfig();
  };

  struct BufferConfig
  {
    size_t cap_min;
    size_t cap_max;

    size_t cap;

    BufferConfig();
  };

  struct SystemConfig
  {
    ProducerConfig producer_config;
    DeviceConfig device_config;
    BufferConfig buffer_config;
  };
}

#endif
