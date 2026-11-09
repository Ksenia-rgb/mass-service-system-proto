#ifndef AUTO_GRAPHS_TABLE_MODEL_H
#define AUTO_GRAPHS_TABLE_MODEL_H

#include <QAbstractTableModel>

namespace mss
{
  namespace gui
  {
    struct DataRowResult
    {
      double avg_reject_prob;
      double avg_time_in_system;
      double avg_workload;
    };
    struct ProducerCntRowResult
    {
      int producer_cnt;
      DataRowResult res_row;
    };
    struct DeviceCntRowResult
    {
      int device_cnt;
      DataRowResult res_row;
    };
    struct BufferCapRowResult
    {
      int buffer_cap;
      DataRowResult res_row;
    };

    class AutoGraphsProducerCntTableModel: public QAbstractTableModel
    {
      Q_OBJECT
    public:
      using Results = QVector< ProducerCntRowResult >;
      enum Roles
      {
        ProducerCntRole = Qt::UserRole + 1,
        AvgRejectProbRole,
        AvgTimeInSystemRole,
        AvgWorkloadRole
      };
      Q_ENUM(Roles);

      AutoGraphsProducerCntTableModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& index = QModelIndex()) const override;
      int columnCount(const QModelIndex& index = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      QVariant headerData(int section, Qt::Orientation ori, int role) const override;
      QHash< int, QByteArray > roleNames() const override;

      void setRows(const Results& rows);
    private:
      Results rows_;
    };

    class AutoGraphsDeviceCntTableModel: public QAbstractTableModel
    {
      Q_OBJECT
    public:
      using Results = QVector< DeviceCntRowResult >;
      enum Roles
      {
        DeviceCntRole = Qt::UserRole + 1,
        AvgRejectProbRole,
        AvgTimeInSystemRole,
        AvgWorkloadRole
      };
      Q_ENUM(Roles);

      AutoGraphsDeviceCntTableModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& index = QModelIndex()) const override;
      int columnCount(const QModelIndex& index = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      QVariant headerData(int section, Qt::Orientation ori, int role) const override;
      QHash< int, QByteArray > roleNames() const override;

      void setRows(const Results& rows);
    private:
      Results rows_;
    };

    class AutoGraphsBufferCapTableModel: public QAbstractTableModel
    {
      Q_OBJECT
    public:
      using Results = QVector< BufferCapRowResult >;
      enum Roles
      {
        BufferCapRole = Qt::UserRole + 1,
        AvgRejectProbRole,
        AvgTimeInSystemRole,
        AvgWorkloadRole
      };
      Q_ENUM(Roles);

      AutoGraphsBufferCapTableModel(QObject* parent = nullptr);

      int rowCount(const QModelIndex& index = QModelIndex()) const override;
      int columnCount(const QModelIndex& index = QModelIndex()) const override;
      QVariant data(const QModelIndex& index, int role) const override;
      QVariant headerData(int section, Qt::Orientation ori, int role) const override;
      QHash< int, QByteArray > roleNames() const override;

      void setRows(const Results& rows);
    private:
      Results rows_;
    };
  }
}

#endif
