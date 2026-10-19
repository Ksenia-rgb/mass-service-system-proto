#ifndef EVENT_MOD_H
#define EVENT_MOD_H

namespace mss
{
  namespace blocks
  {
    class EventMod
    {
    public:
      virtual void mod() = 0;
    };

    class EventModIncomeBid: EventMod
    {
    public:
      virtual void mod() override;
    };

    class EventModDeviceFree: EventMod
    {
    public:
      virtual void mod() override;
    };

    class EventModEnd: EventMod
    {
    public:
      virtual void mod() override;
    };
  }
}

#endif
