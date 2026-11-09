#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "pd-config-controller.h"
#include "buffer-config-controller.h"
#include "system-step-controller.h"
#include "system-auto-controller.h"

namespace mss
{
  namespace gui
  {
    class SystemController: public QObject
    {
      Q_OBJECT
    public:
      SystemController(QObject* parent = nullptr);

      PDConfigController* getProducerConfig();
      PDConfigController* getDeviceConfig();
      BufferConfigController* getBufferConfig();
      SystemStepController* getSystemStepController();
      SystemAutoController* getSystemAutoController();

      Q_INVOKABLE void prepareSystemStepController();
      Q_INVOKABLE void prepareSystemAutoController();
    private:
      PDConfigController producer_config_;
      PDConfigController device_config_;
      BufferConfigController buffer_config_;

      SystemStepController system_step_controller_;
      SystemAutoController system_auto_controller_;
    };
  }
}

#endif
