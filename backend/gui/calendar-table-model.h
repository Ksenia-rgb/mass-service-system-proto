#ifndef CALENDAR_TABLE_MODEL_H
#define CALENDAR_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "backend/system/types.h"

namespace mss
{
  namespace gui
  {
    class CalendarTableModel: public QAbstractTableModel
    {
      Q_OBJECT
    public:
      enum Roles
      {
        IdRole = Qt::UserRole + 1,
        TimeRole,
        TypeRole,
      };
      Q_ENUM(Roles);

      CalendarTableModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& index = QModelIndex()) const override;
      int columnCount(const QModelIndex& index = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      QVariant headerData(int section, Qt::Orientation ori, int role) const override;
      QHash< int, QByteArray > roleNames() const override;

      void setRows(const CalendarResultsStr& rows);
    private:
      CalendarResultsStr rows_;
    };
  }
}

#endif
