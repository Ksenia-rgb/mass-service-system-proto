#include "system.h"

#include <cmath>
#include <iostream>
#include <iomanip>

mss::System::System(const SystemConfig& config):
  system_time_(),
  is_end_(false),
  prods_(config.producer_config),
  devices_(config.device_config),
  buffer_(config.buffer_config),
  calendar_(prods_, devices_, system_time_)
{
  for (size_t i = 0; i < prods_.size(); i++)
  {
    prods_.generateNextBid(i, system_time_);
  }

  // print(std::cout) << std::endl;
}

void mss::System::step()
{
  if (!is_end_)
  {
    auto res = determineNextEvent();
    analyseEvent(res.first, res.second);
  }
  // print(std::cout) << std::endl;
}

void mss::System::finish()
{
  calendar_.finish(system_time_);
  step();
}

double mss::System::getAvgRejectProb()
{
  return prods_.getAvgRejectProb();
}

double mss::System::getAvgTimeInSystem()
{
  return prods_.getAvgTimeInSystem();
}

double mss::System::getAvgWorkload()
{
  return devices_.getAvgWorkload(system_time_);
}

std::pair< size_t, mss::base::CalendarEntry > mss::System::determineNextEvent()
{
  // БООС - блок определения очередного события

  base::CalendarEntry res;
  size_t index = calendar_.next();
  if (index < prods_.size() + devices_.size() + 1)
  {
    res = calendar_.get(index);
    system_time_ = res.time;
  }
  return {index, res};
}

void mss::System::analyseEvent(size_t index, base::CalendarEntry entry)
{
  // БАС - блок анализа события

  if (index < prods_.size())
  {
    return eventModIncomeBid(entry);
  }
  if (index < prods_.size() + devices_.size())
  {
    return eventModFreeDevice();
  }
  return eventModEnd();
}

void mss::System::eventModIncomeBid(base::CalendarEntry entry)
{
  // БМС1 - обработка события "Поступление заявки"
  // 0. Сгенерировать новую заявку на этом источнике
  // 1. Если есть свободный прибор, поставить заявку на прибор
  // 2. Иначе, если есть место в буфере, поместить заявку в буфер
  // 3. Иначе провести отказ заявки из буфера и поместить на ее место новую заявку

  if (!calendar_.isFinished())
  {
    prods_.generateNextBid(entry.id - 1, system_time_);
  }

  base::MssTime time_service = devices_.setBid(entry, system_time_);
  if (!time_service.isNull())
  {
    prods_.setOnDeviceTime(entry.id - 1, time_service);
    return;
  }

  if (buffer_.addBid(entry))
  {
    return;
  }

  base::CalendarEntry reject_entry = buffer_.getRejectBid(entry);
  prods_.reject(reject_entry.id - 1);
  prods_.setInBufferTime(reject_entry.id - 1, system_time_ - reject_entry.time);
  return;
}

void mss::System::eventModFreeDevice()
{
  // БМС2 - обработка событие "Прибор освободился"
  // 1. Если в буфере есть заявки, забрать заявку на освободившийся прибор

  size_t index_service = buffer_.getServiceBidIndex();
  if (index_service >= buffer_.size())
  {
    return;
  }

  base::CalendarEntry entry = buffer_.get(index_service);
  prods_.setInBufferTime(entry.id - 1, system_time_ - entry.time);

  base::MssTime time_service = devices_.setBid(entry, system_time_);
  if (!time_service.isNull())
  {
    prods_.setOnDeviceTime(entry.id - 1, time_service);
  }
  return;
}

void mss::System::eventModEnd()
{
  // БМС3 - обработка события "Конец моделирования"

  while (calendar_.hasEntries())
  {
    step();
  }
  is_end_ = true;
}

std::ostream& mss::System::print(std::ostream& out)
{
  out << "SYSTEM TIME: " << std::fixed << std::setprecision(3) << system_time_.time_sec << '\n';
  calendar_.print(out);

  out << "\nBUFFER:\n";
  return buffer_.print(out);
}
