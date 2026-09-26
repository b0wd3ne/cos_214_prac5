#ifndef CAMPUSGUARD_COMMANDS_OPERATOR_CONSOLE_H
#define CAMPUSGUARD_COMMANDS_OPERATOR_CONSOLE_H

#include <memory>
#include <vector>

#include "Command.h"

// Invoker (GoF Command). Knows nothing about what a command does; it only
// runs commands and keeps a history so the most recent one can be undone.
// Owns every command it has executed (unique_ptr), which is why the
// destruction policy for commands is simple: the console's own destructor
// cleans up the whole history automatically.
class OperatorConsole {
 public:
  void execute(std::unique_ptr<Command> command);
  void undoLast();  // throws EmptyHistoryException if history_ is empty

  std::size_t historySize() const { return history_.size(); }

 private:
  std::vector<std::unique_ptr<Command>> history_;  // console owns these
};

#endif  // CAMPUSGUARD_COMMANDS_OPERATOR_CONSOLE_H
