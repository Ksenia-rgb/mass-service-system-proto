#ifndef BUFFER_TABLE_MODEL_H
#define BUFFER_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "backend/system/types.h"

namespace mss
{
  namespace gui
  {
    class BufferTableModel: public QAbstractTableModel
    {
      Q_OBJECT
    public:
      enum Roles
      {
        IdRole = Qt::UserRole + 1,
        TimeRole
      };
      Q_ENUM(Roles);

      BufferTableModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& index) const override;
      int columnCount(const QModelIndex& index) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      QVariant headerData(int section, Qt::Orientation ori, int role) const override;
      QHash< int, QByteArray > roleNames() const override;

      void setRows(const BufferResultsStr& rows);
    private:
      BufferResultsStr rows_;
    };
  }
}

#endif
