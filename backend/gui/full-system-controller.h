#ifndef FULL_SYSTEM_CONTROLLER_H
#define FULL_SYSTEM_CONTROLLER_H

#include "pd-config-controller.h"
#include "buffer-config-controller.h"
#include "system-step-controller.h"
#include "system-auto-controller.h"

namespace mss
{
  namespace gui
  {
    class FullSystemController
    {
    public:
      FullSystemController();

      PDConfigController* getProducerConfigPtr();
      PDConfigController* getDeviceConfigPtr();
      BufferConfigController* getBufferConfigPtr();
      SystemStepController* getSystemStepPtr();
      SystemAutoController* getSystemAutoPtr();
    private:
      PDConfigController producer_config_;
      PDConfigController device_config_;
      BufferConfigController buffer_config_;
      SystemStepController system_step_;
      SystemAutoController system_auto_;
    };
  }
}

#endif
