#include "DispatchUnitCommand.h"

#include "../common/Exceptions.h"
#include "../common/Logger.h"
#include "../incident/Incident.h"
#include "../response/ResponseComponent.h"

DispatchUnitCommand::DispatchUnitCommand(ResponseComponent& unit,
                                          Incident& incident)
    : unit_(unit), incident_(incident) {}

void DispatchUnitCommand::execute() {
  if (!unit_.isAvailable()) {
    throw UnitUnavailableException(unit_.name() +
                                    " is not available to dispatch");
  }
  unit_.dispatchTo(incident_);  // real domain behaviour on the receiver
  incident_.dispatch();         // drives the incident's State transition
  executed_ = true;
  Logger::log("COMMAND", "Dispatched " + unit_.name() + " to incident #" +
                              std::to_string(incident_.id()));
}

void DispatchUnitCommand::undo() {
  if (!executed_) return;
  Logger::log("COMMAND", "Undo: recalling " + unit_.name() +
                              " from incident #" +
                              std::to_string(incident_.id()));
  executed_ = false;
}

std::string DispatchUnitCommand::describe() const {
  return "Dispatch " + unit_.name() + " to incident #" +
         std::to_string(incident_.id());
}
