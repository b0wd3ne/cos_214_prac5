#ifndef CAMPUSGUARD_COMMANDS_DISPATCH_UNIT_COMMAND_H
#define CAMPUSGUARD_COMMANDS_DISPATCH_UNIT_COMMAND_H

#include "Command.h"

class Incident;
class ResponseComponent;

// Sends a response team (receiver) to an incident, then drives the
// incident's own State transition (Verified -> Dispatched). This is the
// command whose execution the Mediator reacts to: once the receiver
// reports UnitOnScene, DispatchCoordinator fans out further actions.
class DispatchUnitCommand : public Command {
 public:
  DispatchUnitCommand(ResponseComponent& unit, Incident& incident);

  void execute() override;
  void undo() override;
  std::string describe() const override;

 private:
  ResponseComponent& unit_;  // receiver (non-owning)
  Incident& incident_;       // non-owning
  bool executed_ = false;
};

#endif  // CAMPUSGUARD_COMMANDS_DISPATCH_UNIT_COMMAND_H
