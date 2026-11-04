#ifndef PD_CONFIG_H
#define PD_CONFIG_H

#include <QObject>

#include "../system/types.h"

namespace mss
{
  namespace gui
  {
    class PDConfigController: public QObject
    {
      Q_OBJECT

      Q_PROPERTY(int cntMin READ getCntMin WRITE setCntMin NOTIFY cntMinChanged FINAL)
      Q_PROPERTY(int cntMax READ getCntMax WRITE setCntMax NOTIFY cntMaxChanged FINAL)
      Q_PROPERTY(int cnt READ getCnt WRITE setCnt NOTIFY cntChanged FINAL)
      Q_PROPERTY(double timeMin READ getTimeMin WRITE setTimeMin NOTIFY timeMinChanged FINAL)
      Q_PROPERTY(double timeMax READ getTimeMax WRITE setTimeMax NOTIFY timeMaxChanged FINAL)
      Q_PROPERTY(double rate READ getRate WRITE setRate NOTIFY rateChanged FINAL)
      Q_PROPERTY(bool distLaw READ getDistLaw WRITE setDistLaw NOTIFY distLawChanged FINAL)
    public:
      PDConfigController(QObject* parent = nullptr);

      int getCntMin() const;
      int getCntMax() const;
      int getCnt() const;
      double getTimeMin() const;
      double getTimeMax() const;
      double getRate() const;
      bool getDistLaw() const;

      void setCntMin(int val);
      void setCntMax(int val);
      void setCnt(int val);
      void setTimeMin(double val);
      void setTimeMax(double val);
      void setRate(double val);
      void setDistLaw(bool is_exp);
    signals:
      void cntMinChanged(int);
      void cntMaxChanged(int);
      void cntChanged(int);
      void timeMinChanged(double);
      void timeMaxChanged(double);
      void rateChanged(double);
      void distLawChanged(bool);
    private:
      ProducerDeviceConfig config_;
    };
  }
}

#endif
