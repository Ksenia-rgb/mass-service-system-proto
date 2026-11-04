#include "system-step-controller.h"

mss::gui::SystemStepController::SystemStepController(const SystemConfig& config, QObject* parent):
  system_(config)
{}
