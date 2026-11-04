#ifndef SYSTEM_AUTO_CONTROLLER_H
#define SYSTEM_AUTO_CONTROLLER_H

#include <QObject>

namespace mss
{
  namespace gui
  {
    class SystemAutoController: public QObject
    {
      Q_OBJECT
    public:
      SystemAutoController(QObject* parent = nullptr);
    };
  }
}

#endif
