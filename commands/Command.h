#ifndef CAMPUSGUARD_COMMANDS_COMMAND_H
#define CAMPUSGUARD_COMMANDS_COMMAND_H

#include <string>

// ---- Command (GoF) -------------------------------------------------------
// Command   = Command
// Concrete  = DispatchUnitCommand, SecureAreaCommand, IssueAlertCommand,
//             EvacuationOrderCommand
// Invoker   = OperatorConsole
// Receivers = ResponseComponent, AccessControlCentre, CommunicationsCentre
class Command {
 public:
  virtual ~Command() {}
  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual std::string describe() const = 0;
};

#endif  // CAMPUSGUARD_COMMANDS_COMMAND_H
