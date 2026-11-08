#ifndef SYSTEM_AUTO_CONTROLLER_H
#define SYSTEM_AUTO_CONTROLLER_H

#include <QObject>

#include "backend/system/types.h"
#include "auto-graphs-table-model.h"

namespace mss
{
  namespace gui
  {
    class SystemAutoController: public QObject
    {
      Q_OBJECT
      Q_PROPERTY(QAbstractTableModel* producerCntModel READ getProducerCntModel CONSTANT)
      Q_PROPERTY(QAbstractTableModel* deviceCntModel READ getDeviceCntModel CONSTANT)
      Q_PROPERTY(QAbstractTableModel* bufferCapModel READ getBufferCapModel CONSTANT)
    public:
      SystemAutoController(QObject* parent = nullptr);

      QAbstractTableModel* getProducerCntModel();
      QAbstractTableModel* getDeviceCntModel();
      QAbstractTableModel* getBufferCapModel();

      void setSystemConfig(const SystemConfig& config);
    private:
      AutoGraphsProducerCntTableModel producer_cnt_model_;
      AutoGraphsDeviceCntTableModel device_cnt_model_;
      AutoGraphsBufferCapTableModel buffer_cap_model_;

      static constexpr size_t producer_cnt_diff_ = 1;
      static constexpr size_t device_cnt_diff_ = 1;
      static constexpr size_t buffer_cap_diff_ = 1;
      static constexpr size_t bid_cnt_ = 20;

      void setProducerCntRows(const SystemConfig& config);
      void setDeviceCntRows(const SystemConfig& config);
      void setBufferCapRows(const SystemConfig& config);
    };
  }
}

#endif
