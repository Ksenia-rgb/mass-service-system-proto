#ifndef SYSTEM_STEP_CONTROLLER_H
#define SYSTEM_STEP_CONTROLLER_H

#include <QObject>

#include "../system/system.h"

namespace mss
{
  namespace gui
  {
    class SystemStepController: public QObject
    {
      Q_OBJECT
    public:
      SystemStepController(const SystemConfig& config, QObject* parent = nullptr);
    private:
      System system_;
    };
  }
}

#endif
