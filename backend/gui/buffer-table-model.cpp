#include "buffer-table-model.h"

mss::gui::BufferTableModel::BufferTableModel(QObject* parent)
{}

int mss::gui::BufferTableModel::rowCount(const QModelIndex& index) const
{
  return rows_.size();
}

int mss::gui::BufferTableModel::columnCount(const QModelIndex& index) const
{
  return Roles::TimeRole - Qt::UserRole;
}

QVariant mss::gui::BufferTableModel::data(const QModelIndex& index, int role) const
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
    }
  };
  case Roles::IdRole: return row.id;
  case Roles::TimeRole: return row.time;
  default: return {};
  }
}

QVariant mss::gui::BufferTableModel::headerData(int section, Qt::Orientation ori, int role) const
{
  if (role != Qt::DisplayRole || ori != Qt::Horizontal)
  {
    return {};
  }

  switch (section)
  {
  case 0: return "Id";
  case 1: return "Time";
  default: return {};
  }
}

QHash< int, QByteArray > mss::gui::BufferTableModel::roleNames() const
{
  return {
    {Qt::DisplayRole, "display"},
    {Roles::IdRole, "id"},
    {Roles::TimeRole, "time"}
  };
}

void mss::gui::BufferTableModel::setRows(const BufferResultsStr& rows)
{
  beginResetModel();
  rows_ = rows;
  endResetModel();
}
