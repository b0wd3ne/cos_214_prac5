#include "SecureAreaCommand.h"

#include "../campus/AccessControlCentre.h"
#include "../common/Logger.h"

namespace {
std::string modeName(AccessMode mode) {
  switch (mode) {
    case AccessMode::Open: return "Open";
    case AccessMode::Restricted: return "Restricted";
    case AccessMode::Locked: return "Locked";
  }
  return "Unknown";
}
}  // namespace

SecureAreaCommand::SecureAreaCommand(AccessControlCentre& access,
                                      std::string areaName, AccessMode newMode)
    : access_(access), areaName_(std::move(areaName)), newMode_(newMode) {}

void SecureAreaCommand::execute() {
  previousMode_ = access_.areaAccess(areaName_);
  access_.setAreaAccess(areaName_, newMode_);
  executed_ = true;
  Logger::log("COMMAND", "Set " + areaName_ + " access to " +
                              modeName(newMode_) + " (was " +
                              modeName(previousMode_) + ")");
}

void SecureAreaCommand::undo() {
  if (!executed_) return;
  access_.setAreaAccess(areaName_, previousMode_);
  Logger::log("COMMAND", "Undo: restored " + areaName_ + " access to " +
                              modeName(previousMode_));
  executed_ = false;
}

std::string SecureAreaCommand::describe() const {
  return "Set " + areaName_ + " access to " + modeName(newMode_);
}
