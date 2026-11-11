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
      Q_PROPERTY(QString avgRejectProb READ getAvgRejectProb NOTIFY avgRejectProbChanged)
      Q_PROPERTY(QString avgTimeInSystem READ getAvgTimeInSystem NOTIFY avgTimeInSystemChanged)
      Q_PROPERTY(QString avgWorkload READ getAvgWorkload NOTIFY avgWorkloadChanged)
    public:
      SystemStepController(QObject* parent = nullptr);

      QAbstractTableModel* getCalendarModel();
      QAbstractTableModel* getBufferModel();
      QString getSystemTime() const;
      QString getAvgRejectProb() const;
      QString getAvgTimeInSystem() const;
      QString getAvgWorkload() const;

      void setSystemConfig(const SystemConfig& config);

      Q_INVOKABLE void start();
      Q_INVOKABLE void step();
      Q_INVOKABLE void finish();
    signals:
      void systemTimeChanged(QString);
      void avgRejectProbChanged(QString);
      void avgTimeInSystemChanged(QString);
      void avgWorkloadChanged(QString);
    private:
      System system_;
      SystemConfig config_;

      CalendarTableModel calendar_model_;
      BufferTableModel buffer_model_;
      QString system_time_;
      QString avg_reject_prob_;
      QString avg_time_in_system_;
      QString avg_workload_;

      void setRows(const SystemResultsStr& res);
    };
  }
}

#endif
