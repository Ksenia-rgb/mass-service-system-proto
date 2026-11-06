#include "system-auto-controller.h"

#include "backend/system/system.h"

mss::gui::SystemAutoController::SystemAutoController(QObject* parent):
  producer_cnt_diff_(1),
  device_cnt_diff_(1),
  buffer_cap_diff_(1),
  bid_cnt_(2000)
{}

QAbstractTableModel* mss::gui::SystemAutoController::getProducerCntModel()
{
  return &producer_cnt_model_;
}

QAbstractTableModel* mss::gui::SystemAutoController::getDeviceCntModel()
{
  return &device_cnt_model_;
}

QAbstractTableModel* mss::gui::SystemAutoController::getBufferCapModel()
{
  return &buffer_cap_model_;
}

void mss::gui::SystemAutoController::setSystemConfig(const SystemConfig& config)
{
  setProducerCntRows(config);
  setDeviceCntRows(config);
  setBufferCapRows(config);
}

void mss::gui::SystemAutoController::setProducerCntRows(const SystemConfig& config)
{
  AutoGraphsProducerCntTableModel::Results res(config.producer_config.cnt_max - config.producer_config.cnt_min + 1);

  for (size_t i = 0, cnt = config.producer_config.cnt_min; cnt <= config.producer_config.cnt_max; i++, cnt += producer_cnt_diff_)
  {
    SystemConfig config_cnt{config};
    config_cnt.producer_config.cnt = cnt;

    System system{config_cnt};
    system.start();
    for (size_t bid = 0; bid < bid_cnt_; bid++)
    {
      system.step();
    }
    system.finish();

    res[i] = ProducerCntRowResult{
      static_cast< int >(cnt),
      {system.getAvgRejectProb(), system.getAvgTimeInSystem(), system.getAvgWorkload()}
    };
    //res[i] = ProducerCntRowResult{static_cast< int >(cnt), {0, 0, 0}};
  }
  producer_cnt_model_.setRows(res);
}

void mss::gui::SystemAutoController::setDeviceCntRows(const SystemConfig& config)
{
  AutoGraphsDeviceCntTableModel::Results res(config.device_config.cnt_max - config.device_config.cnt_min + 1);

  for (size_t i = 0, cnt = config.device_config.cnt_min; cnt <= config.device_config.cnt_max; i++, cnt += device_cnt_diff_)
  {
    SystemConfig config_cnt{config};
    config_cnt.device_config.cnt = cnt;

    System system{config_cnt};
    system.start();
    for (size_t bid = 0; bid < bid_cnt_; bid++)
    {
      system.step();
    }
    system.finish();

    res[i] = DeviceCntRowResult{
      static_cast< int >(cnt),
      {system.getAvgRejectProb(), system.getAvgTimeInSystem(), system.getAvgWorkload()}
    };
    //res[i] = DeviceCntRowResult{static_cast< int >(cnt), {0, 0, 0}};
  }
  device_cnt_model_.setRows(res);
}

void mss::gui::SystemAutoController::setBufferCapRows(const SystemConfig& config)
{
  AutoGraphsBufferCapTableModel::Results res(config.buffer_config.cap_max - config.buffer_config.cap_min + 1);

  for (size_t i = 0, cap = config.buffer_config.cap_min; cap <= config.buffer_config.cap_max; i++, cap += buffer_cap_diff_)
  {
    SystemConfig config_cap{config};
    config_cap.buffer_config.cap = cap;

    System system{config_cap};
    system.start();
    for (size_t bid = 0; bid < bid_cnt_; bid++)
    {
      system.step();
    }
    system.finish();

    res[i] = BufferCapRowResult{
      static_cast< int >(cap),
      {system.getAvgRejectProb(), system.getAvgTimeInSystem(), system.getAvgWorkload()}
    };
    //res[i] = BufferCapRowResult{static_cast< int >(cap), {0, 0, 0}};
  }
}
