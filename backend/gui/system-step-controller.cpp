#include "system-step-controller.h"

mss::gui::SystemStepController::SystemStepController(QObject* parent):
  system_(SystemConfig{})
{}

QAbstractTableModel* mss::gui::SystemStepController::getCalendarModel()
{
  return &calendar_model_;
}

QAbstractTableModel* mss::gui::SystemStepController::getBufferModel()
{
  return &buffer_model_;
}

QString mss::gui::SystemStepController::getSystemTime() const
{
  return system_time_;
}

QString mss::gui::SystemStepController::getAvgRejectProb() const
{
  return avg_reject_prob_;
}

QString mss::gui::SystemStepController::getAvgTimeInSystem() const
{
  return avg_time_in_system_;
}

QString mss::gui::SystemStepController::getAvgWorkload() const
{
  return avg_workload_;
}

void mss::gui::SystemStepController::setSystemConfig(const SystemConfig& config)
{
  config_ = config;
}

void mss::gui::SystemStepController::start()
{
  system_ = System{config_};
  setRows(system_.start());
}

void mss::gui::SystemStepController::step()
{
  setRows(system_.step());
}

void mss::gui::SystemStepController::finish()
{
  setRows(system_.finish());
  avg_reject_prob_ = QString::number(system_.getAvgRejectProb());
  avg_time_in_system_ = QString::number(system_.getAvgTimeInSystem());
  avg_workload_ = QString::number(system_.getAvgWorkload());

  emit avgRejectProbChanged(avg_reject_prob_);
  emit avgTimeInSystemChanged(avg_time_in_system_);
  emit avgWorkloadChanged(avg_workload_);
}

void mss::gui::SystemStepController::setRows(const SystemResultsStr& res)
{
  calendar_model_.setRows(res.calendar_rows);
  buffer_model_.setRows(res.buffer_rows);
  system_time_ = res.system_time;
  emit systemTimeChanged(res.system_time);
}
