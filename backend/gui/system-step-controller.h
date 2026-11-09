#ifndef SYSTEM_STEP_CONTROLLER_H
#define SYSTEM_STEP_CONTROLLER_H

#include <QObject>
#include <QAbstractTableModel>

#include "backend/system/system.h"
#include "calendar-table-model.h"
#include "buffer-table-model.h"

namespace mss
{
  namespace gui
  {
    class SystemStepController: public QObject
    {
      Q_OBJECT
      Q_PROPERTY(QAbstractTableModel* calendarModel READ getCalendarModel CONSTANT)
      Q_PROPERTY(QAbstractTableModel* bufferModel READ getBufferModel CONSTANT)
      Q_PROPERTY(QString systemTime READ getSystemTime NOTIFY systemTimeChanged)
    public:
      SystemStepController(QObject* parent = nullptr);

      QAbstractTableModel* getCalendarModel();
      QAbstractTableModel* getBufferModel();
      QString getSystemTime() const;

      void setSystemConfig(const SystemConfig& config);

      Q_INVOKABLE void start();
      Q_INVOKABLE void step();
      Q_INVOKABLE void finish();
    signals:
      void systemTimeChanged(QString);
    private:
      System system_;
      SystemConfig config_;

      CalendarTableModel calendar_model_;
      BufferTableModel buffer_model_;
      QString system_time_;

      void setRows(const SystemResultsStr& res);
    };
  }
}

#endif
