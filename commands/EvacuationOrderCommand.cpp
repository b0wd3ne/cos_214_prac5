#include "EvacuationOrderCommand.h"

#include "../comms/CommunicationsCentre.h"
#include "../common/Logger.h"

EvacuationOrderCommand::EvacuationOrderCommand(CommunicationsCentre& comms,
                                                std::string areaName,
                                                std::string message)
    : comms_(comms),
      areaName_(std::move(areaName)),
      message_(std::move(message)) {}

void EvacuationOrderCommand::execute() {
  comms_.broadcastEvacuation(areaName_, message_);
  executed_ = true;
  Logger::log("[COMMAND] Evacuation ordered for " + areaName_ + ": " + message_);
}

void EvacuationOrderCommand::undo() {
  if (!executed_) return;
  comms_.broadcastEvacuation(
      areaName_, "Evacuation order for " + areaName_ + " has been stood down");
  Logger::log("[COMMAND] Undo: stand-down notice sent for " + areaName_);
  executed_ = false;
}

std::string EvacuationOrderCommand::describe() const {
  return "Evacuate " + areaName_ + ": " + message_;
}
