#include "OperatorConsole.h"

#include "../common/Exceptions.h"
#include "../common/Logger.h"

void OperatorConsole::execute(std::unique_ptr<Command> command) {
  Logger::log("[OPERATOR] Executing: " + command->describe());
  command->execute();
  history_.push_back(std::move(command));
}

void OperatorConsole::undoLast() {
  if (history_.empty()) {
    throw EmptyHistoryException("No command to undo");
  }
  Logger::log("[OPERATOR] Undoing: " + history_.back()->describe());
  history_.back()->undo();
  history_.pop_back();
}
