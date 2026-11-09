#include "auto-graphs-table-model.h"

mss::gui::AutoGraphsProducerCntTableModel::AutoGraphsProducerCntTableModel(QObject* parent)
{}

int mss::gui::AutoGraphsProducerCntTableModel::rowCount(const QModelIndex& index) const
{
  return rows_.size();
}

int mss::gui::AutoGraphsProducerCntTableModel::columnCount(const QModelIndex& index) const
{
  return Roles::AvgWorkloadRole - Qt::UserRole;
}

QVariant mss::gui::AutoGraphsProducerCntTableModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return {};
  }

  const auto& row = rows_.at(index.row());

  switch (role)
  {
  case Qt::DisplayRole:
  {
    switch (index.column())
    {
    case 0: return row.producer_cnt;
    case 1: return row.res_row.avg_reject_prob;
    case 2: return row.res_row.avg_time_in_system;
    case 3: return row.res_row.avg_workload;
    }
  };
  case Roles::ProducerCntRole: return row.producer_cnt;
  case Roles::AvgRejectProbRole: return row.res_row.avg_reject_prob;
  case Roles::AvgTimeInSystemRole: return row.res_row.avg_time_in_system;
  case Roles::AvgWorkloadRole: return row.res_row.avg_workload;
  default: return {};
  }
}

QVariant mss::gui::AutoGraphsProducerCntTableModel::headerData(int section, Qt::Orientation ori, int role) const
{
  if (role != Qt::DisplayRole || ori != Qt::Horizontal)
  {
    return {};
  }

  switch (section)
  {
  case 0: return "Producer count";
  case 1: return "Average producers reject probability";
  case 2: return "Average bid time in system";
  case 3: return "Average devices workload";
  default: return {};
  }
}

QHash< int, QByteArray > mss::gui::AutoGraphsProducerCntTableModel::roleNames() const
{
  return {
    {Qt::DisplayRole, "display"},
    {Roles::ProducerCntRole, "producerCnt"},
    {Roles::AvgRejectProbRole, "avgRejectProb"},
    {Roles::AvgTimeInSystemRole, "avgTimeInSystem"},
    {Roles::AvgWorkloadRole, "avgWorkload"}
  };
}

void mss::gui::AutoGraphsProducerCntTableModel::setRows(const Results& rows)
{
  beginResetModel();
  rows_ = rows;
  endResetModel();
}

mss::gui::AutoGraphsDeviceCntTableModel::AutoGraphsDeviceCntTableModel(QObject* parent)
{}

int mss::gui::AutoGraphsDeviceCntTableModel::rowCount(const QModelIndex& index) const
{
  return rows_.size();
}

int mss::gui::AutoGraphsDeviceCntTableModel::columnCount(const QModelIndex& index) const
{
  return Roles::AvgWorkloadRole - Qt::UserRole;
}

QVariant mss::gui::AutoGraphsDeviceCntTableModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return {};
  }

  const auto& row = rows_.at(index.row());

  switch (role)
  {
  case Qt::DisplayRole:
  {
    switch (index.column())
    {
    case 0: return row.device_cnt;
    case 1: return row.res_row.avg_reject_prob;
    case 2: return row.res_row.avg_time_in_system;
    case 3: return row.res_row.avg_workload;
    }
  };
  case Roles::DeviceCntRole: return row.device_cnt;
  case Roles::AvgRejectProbRole: return row.res_row.avg_reject_prob;
  case Roles::AvgTimeInSystemRole: return row.res_row.avg_time_in_system;
  case Roles::AvgWorkloadRole: return row.res_row.avg_workload;
  default: return {};
  }
}

QVariant mss::gui::AutoGraphsDeviceCntTableModel::headerData(int section, Qt::Orientation ori, int role) const
{
  if (role != Qt::DisplayRole || ori != Qt::Horizontal)
  {
    return {};
  }

  switch (section)
  {
  case 0: return "Device count";
  case 1: return "Average producers reject probability";
  case 2: return "Average bid time in system";
  case 3: return "Average devices workload";
  default: return {};
  }
}

QHash< int, QByteArray > mss::gui::AutoGraphsDeviceCntTableModel::roleNames() const
{
  return {
    {Qt::DisplayRole, "display"},
    {Roles::DeviceCntRole, "deviceCnt"},
    {Roles::AvgRejectProbRole, "avgRejectProb"},
    {Roles::AvgTimeInSystemRole, "avgTimeInSystem"},
    {Roles::AvgWorkloadRole, "avgWorkload"}
  };
}

void mss::gui::AutoGraphsDeviceCntTableModel::setRows(const Results& rows)
{
  beginResetModel();
  rows_ = rows;
  endResetModel();
}

mss::gui::AutoGraphsBufferCapTableModel::AutoGraphsBufferCapTableModel(QObject* parent)
{}

int mss::gui::AutoGraphsBufferCapTableModel::rowCount(const QModelIndex& index) const
{
  return rows_.size();
}

int mss::gui::AutoGraphsBufferCapTableModel::columnCount(const QModelIndex& index) const
{
  return Roles::AvgWorkloadRole - Qt::UserRole;
}

QVariant mss::gui::AutoGraphsBufferCapTableModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return {};
  }

  const auto& row = rows_.at(index.row());

  switch (role)
  {
  case Qt::DisplayRole:
  {
    switch (index.column())
    {
    case 0: return row.buffer_cap;
    case 1: return row.res_row.avg_reject_prob;
    case 2: return row.res_row.avg_time_in_system;
    case 3: return row.res_row.avg_workload;
    }
  };
  case Roles::BufferCapRole: return row.buffer_cap;
  case Roles::AvgRejectProbRole: return row.res_row.avg_reject_prob;
  case Roles::AvgTimeInSystemRole: return row.res_row.avg_time_in_system;
  case Roles::AvgWorkloadRole: return row.res_row.avg_workload;
  default: return {};
  }
}

QVariant mss::gui::AutoGraphsBufferCapTableModel::headerData(int section, Qt::Orientation ori, int role) const
{
  if (role != Qt::DisplayRole || ori != Qt::Horizontal)
  {
    return {};
  }

  switch (section)
  {
  case 0: return "Buffer capacity";
  case 1: return "Average producers reject probability";
  case 2: return "Average bid time in system";
  case 3: return "Average devices workload";
  default: return {};
  }
}

QHash< int, QByteArray > mss::gui::AutoGraphsBufferCapTableModel::roleNames() const
{
  return {
    {Qt::DisplayRole, "display"},
    {Roles::BufferCapRole, "bufferCap"},
    {Roles::AvgRejectProbRole, "avgRejectProb"},
    {Roles::AvgTimeInSystemRole, "avgTimeInSystem"},
    {Roles::AvgWorkloadRole, "avgWorkload"}
  };
}

void mss::gui::AutoGraphsBufferCapTableModel::setRows(const Results& rows)
{
  beginResetModel();
  rows_ = rows;
  endResetModel();
}
