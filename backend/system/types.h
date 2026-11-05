#ifndef TYPES_H
#define TYPES_H

#include <cstddef>

namespace mss
{
  enum DistribLaw {Exp, Uniform};

  struct ProducerConfig
  {
    size_t cnt_min;
    size_t cnt_max;

    size_t cnt;

    double time_min; // время генерации заявок на источниках
    double time_max;

    DistribLaw distrib_law; // закон распределения времени генерации
    double rate_per_hour; // интенсивность генерации (кол-во заявок в единицу времени)
  };

  struct DeviceConfig
  {
    size_t cnt_min;
    size_t cnt_max;

    size_t cnt;

    double time_min; // время обслуживания заявок на приборах
    double time_max;

    DistribLaw distrib_law; // закон распределения времени обслуживания
    double rate_per_hour; // интенсивность обслуживания (кол-во заявок в единицу времени)
  };

  struct BufferConfig
  {
    size_t cap_min;
    size_t cap_max;

    size_t cap;
  };

  struct SystemConfig
  {
    ProducerConfig producer_config;
    DeviceConfig device_config;
    BufferConfig buffer_config;
  };
}

#endif
