#include "system-auto-controller.h"

#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <exception>

#include "backend/system/system.h"

mss::gui::SystemAutoController::SystemAutoController(QObject* parent)
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

namespace
{
  using namespace mss;
  using namespace mss::gui;
  using ProducerModel = AutoGraphsProducerCntTableModel;
  using DeviceModel = AutoGraphsDeviceCntTableModel;
  using BufferModel = AutoGraphsBufferCapTableModel;

  ProducerModel::Results getProducerResults(mss::SystemConfig config, size_t n, size_t diff, size_t bid_cnt)
  {
    ProducerModel::Results res(n);

    size_t i = 0;
    for (size_t cnt = config.producer_config.cnt_min; cnt <= config.producer_config.cnt_max; i++, cnt += diff)
    {
      SystemConfig config_cnt{config};
      config_cnt.producer_config.cnt = cnt;

      System system{config_cnt};
      system.start();
      for (size_t bid = 0; bid < bid_cnt; bid++)
      {
        system.step();
      }
      //system.finish();

      res[i] = ProducerCntRowResult{
        static_cast< int >(cnt),
        {system.getAvgRejectProb(), system.getAvgTimeInSystem(), system.getAvgWorkload()}
      };
    }

    return res;
  }

  DeviceModel::Results getDeviceResults(mss::SystemConfig config, size_t n, size_t diff, size_t bid_cnt)
  {
    DeviceModel::Results res(n);

    size_t i = 0;
    for (size_t cnt = config.device_config.cnt_min; cnt <= config.device_config.cnt_max; i++, cnt += diff)
    {
      SystemConfig config_cnt{config};
      config_cnt.device_config.cnt = cnt;

      System system{config_cnt};
      system.start();
      for (size_t bid = 0; bid < bid_cnt; bid++)
      {
        system.step();
      }
      //system.finish();

      res[i] = DeviceCntRowResult{
        static_cast< int >(cnt),
        {system.getAvgRejectProb(), system.getAvgTimeInSystem(), system.getAvgWorkload()}
      };
    }

    return res;
  }

  BufferModel::Results getBufferResults(mss::SystemConfig config, size_t n, size_t diff, size_t bid_cnt)
  {
    BufferModel::Results res(n);

    size_t i = 0;
    for (size_t cap = config.buffer_config.cap_min; cap <= config.buffer_config.cap_max; i++, cap += diff)
    {
      SystemConfig config_cnt{config};
      config_cnt.buffer_config.cap = cap;

      System system{config_cnt};
      system.start();
      for (size_t bid = 0; bid < bid_cnt; bid++)
      {
        system.step();
      }
      //system.finish();

      res[i] = BufferCapRowResult{
        static_cast< int >(cap),
        {system.getAvgRejectProb(), system.getAvgTimeInSystem(), system.getAvgWorkload()}
      };
    }

    return res;
  }
}

void mss::gui::SystemAutoController::setProducerCntRows(const SystemConfig& config)
{
  const size_t n = (config.producer_config.cnt_max - config.producer_config.cnt_min) / producer_cnt_diff_ + 1;
  auto* watcher = new QFutureWatcher< AutoGraphsProducerCntTableModel::Results >(this);
  connect(watcher,
    &QFutureWatcherBase::finished,
    this,
    [this, watcher]() {
            try {
              auto res = watcher->result();
              qDebug() << "[gui] got rows: " << res.size();
              producer_cnt_model_.setRows(std::move(res));
            } catch (const std::exception& e) {
              qCritical() << "[gui] worker exception: " << e.what();
            } catch (...) {
              qCritical() << "[gui] unknown expection";
            }
      //producer_cnt_model_.setRows(watcher->result());
      watcher->deleteLater();
    }
  );

  QFuture< AutoGraphsProducerCntTableModel::Results > future = QtConcurrent::run(getProducerResults, config, n, producer_cnt_diff_, bid_cnt_);
  watcher->setFuture(future);
}

void mss::gui::SystemAutoController::setDeviceCntRows(const SystemConfig& config)
{
  const size_t n = (config.device_config.cnt_max - config.device_config.cnt_min) / device_cnt_diff_ + 1;
  auto* watcher = new QFutureWatcher< AutoGraphsDeviceCntTableModel::Results >(this);
  connect(watcher,
    &QFutureWatcherBase::finished,
    this,
    [this, watcher]() {
            try {
              auto res = watcher->result();
              qDebug() << "[gui] got rows: " << res.size();
              device_cnt_model_.setRows(std::move(res));
            } catch (const std::exception& e) {
              qCritical() << "[gui] worker exception: " << e.what();
            } catch (...) {
              qCritical() << "[gui] unknown expection";
            }
      //device_cnt_model_.setRows(watcher->result());
      watcher->deleteLater();
    }
  );

  QFuture< AutoGraphsDeviceCntTableModel::Results > future = QtConcurrent::run(getDeviceResults, config, n, device_cnt_diff_, bid_cnt_);
  watcher->setFuture(future);
}

void mss::gui::SystemAutoController::setBufferCapRows(const SystemConfig& config)
{
  const size_t n = (config.buffer_config.cap_max - config.buffer_config.cap_min) / buffer_cap_diff_ + 1;
  auto* watcher = new QFutureWatcher< AutoGraphsBufferCapTableModel::Results >(this);
  connect(watcher,
    &QFutureWatcherBase::finished,
    this,
    [this, watcher]() {
            try {
              auto res = watcher->result();
              qDebug() << "[gui] got rows: " << res.size();
              buffer_cap_model_.setRows(std::move(res));
            } catch (const std::exception& e) {
              qCritical() << "[gui] worker exception: " << e.what();
            } catch (...) {
              qCritical() << "[gui] unknown expection";
            }

      //buffer_cap_model_.setRows(watcher->result());
      watcher->deleteLater();
    }
  );

  QFuture< AutoGraphsBufferCapTableModel::Results > future = QtConcurrent::run(getBufferResults, config, n, buffer_cap_diff_, bid_cnt_);
  watcher->setFuture(future);
}
