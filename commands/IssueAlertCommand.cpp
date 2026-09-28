#include "IssueAlertCommand.h"

#include "../comms/CommunicationsCentre.h"
#include "../common/Logger.h"

IssueAlertCommand::IssueAlertCommand(CommunicationsCentre& comms,
                                      std::string areaName, Severity severity,
                                      std::string message)
    : comms_(comms),
      areaName_(std::move(areaName)),
      severity_(severity),
      message_(std::move(message)) {}

void IssueAlertCommand::execute() {
  comms_.broadcastAlert(areaName_, severity_, message_);
  executed_ = true;
  Logger::log("[COMMAND] Issued alert for " + areaName_ + ": " + message_);
}

void IssueAlertCommand::undo() {
  if (!executed_) return;
  comms_.broadcastAlert(areaName_, severity_,
                         "Correction: previous alert for " + areaName_ +
                             " has been withdrawn");
  Logger::log("[COMMAND] Undo: withdrawal notice sent for " + areaName_);
  executed_ = false;
}

std::string IssueAlertCommand::describe() const {
  return "Alert " + areaName_ + ": " + message_;
}
