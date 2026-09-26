#ifndef CAMPUSGUARD_COMMANDS_EVACUATION_ORDER_COMMAND_H
#define CAMPUSGUARD_COMMANDS_EVACUATION_ORDER_COMMAND_H

#include <string>

#include "Command.h"

class CommunicationsCentre;

// Issues an evacuation instruction for an area. Kept as its own command
// (rather than folded into IssueAlertCommand) because it is a functionally
// distinct operator action per the spec, with its own wording and its own
// meaning for the Mediator to react to.
class EvacuationOrderCommand : public Command {
 public:
  EvacuationOrderCommand(CommunicationsCentre& comms, std::string areaName,
                          std::string message);

  void execute() override;
  void undo() override;
  std::string describe() const override;

 private:
  CommunicationsCentre& comms_;  // receiver (non-owning)
  std::string areaName_;
  std::string message_;
  bool executed_ = false;
};

#endif  // CAMPUSGUARD_COMMANDS_EVACUATION_ORDER_COMMAND_H
