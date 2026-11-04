#ifndef BUFFER_CONFIG_H
#define BUFFER_CONFIG_H

#include <QObject>

#include "../system/types.h"

namespace mss
{
  namespace gui
  {
    class BufferConfigController: public QObject
    {
      Q_OBJECT

      Q_PROPERTY(int capMin READ getCapMin WRITE setCapMin NOTIFY capMinChanged FINAL)
      Q_PROPERTY(int capMax READ getCapMax WRITE setCapMax NOTIFY capMaxChanged FINAL)
      Q_PROPERTY(int cap READ getCap WRITE setCap NOTIFY capChanged FINAL)
    public:
      BufferConfigController(QObject* parent = nullptr);

      int getCapMin() const;
      int getCapMax() const;
      int getCap() const;

      void setCapMin(int val);
      void setCapMax(int val);
      void setCap(int val);
    signals:
      void capMinChanged(int);
      void capMaxChanged(int);
      void capChanged(int);
    private:
      BufferConfig config_;
    };
  }
}

#endif
