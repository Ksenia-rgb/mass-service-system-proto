#ifndef CONFIG-CONTROLLER_H
#define CONFIG-CONTROLLER_H

#include <QObject>

#include "../system/system.h"

namespace mss
{
  namespace control
  {
    class ConfigController: public QObject
    {
      Q_OBJECT
    public:
      ConfigController(QObject* parent = nullptr);

      Q_INVOKABLE void enterProducerCnt(std::string cnt);
      Q_INVOKABLE void enterDeviceCnt(std::string cnt);
      Q_INVOKABLE void enterBufferCap(std::string cap);

      Q_INVOKABLE std::string strConfig();

    private:
      SystemConfig config_;
    };
  }
}

#endif
