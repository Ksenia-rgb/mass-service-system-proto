#ifndef TYPES_H
#define TYPES_H

#include <QVector>
#include <QString>

#include <cstddef>

namespace mss
{
  enum DistLaw {Exp, Uniform};

  struct ProducerDeviceConfig
  {
    size_t cnt_min;
    size_t cnt_max;

    size_t cnt;

    double time_min; // время генерации заявок на источниках
    double time_max;

    double rate_per_hour; // интенсивность генерации (кол-во заявок в единицу времени)
    DistLaw dist_law; // закон распределения времени генерации

    ProducerDeviceConfig();
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
    ProducerDeviceConfig producer_config;
    ProducerDeviceConfig device_config;
    BufferConfig buffer_config;
  };

  struct CalendarRowResultStr
  {
    QString id;
    QString time;
    QString type;
  };
  using CalendarResultsStr = QVector< CalendarRowResultStr >;

  struct BufferRowResultStr
  {
    QString id;
    QString time;
  };
  using BufferResultsStr = QVector< BufferRowResultStr >;

  struct SystemResultsStr
  {
    QString system_time;
    CalendarResultsStr calendar_rows;
    BufferResultsStr buffer_rows;
  };
}

#endif
