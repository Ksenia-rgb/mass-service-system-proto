#include "calendar-table-model.h"

mss::gui::CalendarTableModel::CalendarTableModel(QObject* parent)
{}

int mss::gui::CalendarTableModel::rowCount(const QModelIndex& index) const
{
  return rows_.size();
}

int mss::gui::CalendarTableModel::columnCount(const QModelIndex& index) const
{
  return Roles::TypeRole - Qt::UserRole;
}

QVariant mss::gui::CalendarTableModel::data(const QModelIndex& index, int role) const
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
    case 0: return row.id;
    case 1: return row.time;
    case 2: return row.type;
    }
  };
  case Roles::IdRole: return row.id;
  case Roles::TimeRole: return row.time;
  case Roles::TypeRole: return row.type;
  default: return {};
  }
}

QVariant mss::gui::CalendarTableModel::headerData(int section, Qt::Orientation ori, int role) const
{
  if (role != Qt::DisplayRole || ori != Qt::Horizontal)
  {
    return {};
  }

  switch (section)
  {
  case 0: return "Id";
  case 1: return "Time";
  case 2: return "Type";
  default: return {};
  }
}

QHash< int, QByteArray > mss::gui::CalendarTableModel::roleNames() const
{
  return {
    {Qt::DisplayRole, "display"},
    {Roles::IdRole, "id"},
    {Roles::TimeRole, "time"},
    {Roles::TypeRole, "type"}
  };
}

void mss::gui::CalendarTableModel::setRows(const CalendarResultsStr& rows)
{
  beginResetModel();
  rows_ = rows;
  endResetModel();
}

















