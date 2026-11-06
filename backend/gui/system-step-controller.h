#ifndef SYSTEM_STEP_CONTROLLER_H
#define SYSTEM_STEP_CONTROLLER_H

#include <QObject>
#include <QAbstractTableModel>

#include "backend/system/system.h"
#include "pd-config-controller.h"
#include "buffer-config-controller.h"
#include "calendar-table-model.h"
#include "buffer-table-model.h"

namespace mss
{
  namespace gui
  {
    class SystemStepController: public QObject
    {
      Q_OBJECT
      Q_PROPERTY(PDConfigController* producerConfig READ getProducerConfig CONSTANT)
      Q_PROPERTY(PDConfigController* deviceConfig READ getDeviceConfig CONSTANT)
      Q_PROPERTY(BufferConfigController* bufferConfig READ getBufferConfig CONSTANT)
      Q_PROPERTY(QAbstractTableModel* calendar READ getCalendar CONSTANT)
      Q_PROPERTY(QAbstractTableModel* buffer READ getBuffer CONSTANT)
      Q_PROPERTY(QString systemTime READ getSystemTime NOTIFY systemTimeChanged)
    public:
      SystemStepController(QObject* parent = nullptr);

      PDConfigController* getProducerConfig();
      PDConfigController* getDeviceConfig();
      BufferConfigController* getBufferConfig();
      QAbstractTableModel* getCalendar();
      QAbstractTableModel* getBuffer();
      QString getSystemTime() const;

      Q_INVOKABLE void start();
      Q_INVOKABLE void step();
      Q_INVOKABLE void finish();
    signals:
      void systemTimeChanged(QString);
    private:
      System system_;

      PDConfigController producer_config_;
      PDConfigController device_config_;
      BufferConfigController buffer_config_;

      CalendarTableModel calendar_model_;
      BufferTableModel buffer_model_;
      QString system_time_;

      void setRows(const SystemResultsStr& res);
    };
  }
}

#endif
