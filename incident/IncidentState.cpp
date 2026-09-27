#include "IncidentState.h"

#include <memory>

#include "Incident.h"
#include "../common/Exceptions.h"

// ---- base class: every transition defaults to "not allowed" -------------
void IncidentState::verify(Incident&)   { reject("verify"); }
void IncidentState::dispatch(Incident&) { reject("dispatch"); }
void IncidentState::contain(Incident&)  { reject("contain"); }
void IncidentState::resolve(Incident&)  { reject("resolve"); }
void IncidentState::cancel(Incident&)   { reject("cancel"); }

void IncidentState::reject(const std::string& action) const {
  throw InvalidTransitionException("Cannot " + action +
                                    " an incident while it is " + name());
}

// ---- Reported -> Verified | Cancelled ------------------------------------
void ReportedState::verify(Incident& incident) {
  incident.setState(std::unique_ptr<IncidentState>(new VerifiedState()));
}
void ReportedState::cancel(Incident& incident) {
  incident.setState(std::unique_ptr<IncidentState>(new CancelledState()));
}

// ---- Verified -> Dispatched | Cancelled ----------------------------------
void VerifiedState::dispatch(Incident& incident) {
  incident.setState(std::unique_ptr<IncidentState>(new DispatchedState()));
}
void VerifiedState::cancel(Incident& incident) {
  incident.setState(std::unique_ptr<IncidentState>(new CancelledState()));
}

// ---- Dispatched -> Contained | Cancelled ---------------------------------
void DispatchedState::contain(Incident& incident) {
  incident.setState(std::unique_ptr<IncidentState>(new ContainedState()));
}
void DispatchedState::cancel(Incident& incident) {
  incident.setState(std::unique_ptr<IncidentState>(new CancelledState()));
}

// ---- Contained -> Resolved ------------------------------------------------
void ContainedState::resolve(Incident& incident) {
  incident.setState(std::unique_ptr<IncidentState>(new ResolvedState()));
}

// Resolved and Cancelled define no transitions: they are terminal states.
