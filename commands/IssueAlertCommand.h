#ifndef CAMPUSGUARD_COMMANDS_ISSUE_ALERT_COMMAND_H
#define CAMPUSGUARD_COMMANDS_ISSUE_ALERT_COMMAND_H

#include <string>

#include "Command.h"
#include "../common/Types.h"

class CommunicationsCentre;

// Broadcasts an alert for an area via every channel the CommunicationsCentre
// knows about (app push and, via the Adapter, the legacy pager). Undo is a
// "cancellation notice" rather than an unsend, since a real broadcast can't
// be recalled - that distinction is worth mentioning in the demo.
class IssueAlertCommand : public Command {
 public:
  IssueAlertCommand(CommunicationsCentre& comms, std::string areaName,
                     Severity severity, std::string message);

  void execute() override;
  void undo() override;
  std::string describe() const override;

 private:
  CommunicationsCentre& comms_;  // receiver (non-owning)
  std::string areaName_;
  Severity severity_;
  std::string message_;
  bool executed_ = false;
};

#endif  // CAMPUSGUARD_COMMANDS_ISSUE_ALERT_COMMAND_H
