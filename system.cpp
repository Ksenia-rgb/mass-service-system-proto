#include "system.h"

#include <cmath>
#include <iostream>
#include <iomanip>

mss::System::System(const SystemConfig& config):
  system_time_(),
  is_end_(false),
  prods_(config.produce_cnt, config.gen_start_time, config.gen_finish_time),
  devices_(config.device_cnt, config.prod_rate_per_hour),
  buffer_(config.buffer_cap),
  calendar_(prods_, devices_, system_time_)
{
  for (size_t i = 0; i < prods_.size(); i++)
  {
    prods_.generateNextBid(i, system_time_);
  }
}

void mss::System::step()
{
  print(std::cout) << std::endl;

  if (!is_end_)
  {
    auto res = determineNextEvent();
    analyseEvent(res.first, res.second);
    return;
  }
  return;
}

void mss::System::end()
{
  is_end_ = true;
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
    return eventModIncomeBid(index, entry);
  }
  if (index < prods_.size() + devices_.size())
  {
    return eventModFreeDevice();
  }
  return eventModEnd();
}

void mss::System::eventModIncomeBid(size_t index, base::CalendarEntry entry)
{
  // БМС1 - обработка события "Поступление заявки"
  // 0. Сгенерировать новую заявку на этом источнике
  // 1. Если есть свободный прибор, поставить заявку на прибор
  // 2. Иначе, если есть место в буфере, поместить заявку в буфер
  // 3. Иначе провести отказ заявки из буфера и поместить на ее место новую заявку

  prods_.generateNextBid(index, system_time_);

  if (devices_.setBid(entry, system_time_))
  {
    return;
  }

  if (buffer_.addBid(entry))
  {
    return;
  }

  size_t reject_id = buffer_.getRejectBidId(entry);
  prods_.reject(reject_id);
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

  devices_.setBid(buffer_.get(index_service), system_time_);
  return;
}

void mss::System::eventModEnd()
{
  // БМС3 - обработка события "Конец моделирования"

  is_end_ = true;
}

std::ostream& mss::System::print(std::ostream& out)
{
  out << "SYSTEM TIME: " << std::fixed << std::setprecision(3) << system_time_.time_sec << '\n';
  calendar_.print(out);

  out << "\nBUFFER:\n";
  return buffer_.print(out);
}
