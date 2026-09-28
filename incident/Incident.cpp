#include "Incident.h"

#include "../common/Logger.h"

Incident::Incident(int id, const std::string& description, IncidentType type,
                    Severity severity, const std::string& areaName)
    : id_(id),
      description_(description),
      type_(type),
      severity_(severity),
      areaName_(areaName),
      state_(new ReportedState()) {
  Logger::log("[STATE] Incident #" + std::to_string(id_) + " (" +
                            description_ + ") created in state Reported");
}

void Incident::verify()   { state_->verify(*this); }
void Incident::dispatch() { state_->dispatch(*this); }
void Incident::contain()  { state_->contain(*this); }
void Incident::resolve()  { state_->resolve(*this); }
void Incident::cancel()   { state_->cancel(*this); }

void Incident::setState(std::unique_ptr<IncidentState> newState) {
  std::string from = state_->name();
  std::string to = newState->name();
  // NOTE: this destroys the IncidentState object that is currently running
  // the code which called us (e.g. ReportedState::verify). That is safe
  // ONLY because every caller treats setState() as its last statement and
  // touches no members afterwards - see IncidentState.cpp. Moving this call
  // earlier in a transition method, or reading a member after calling it,
  // is a real use-after-free bug and a good candidate for the GDB task.
  state_ = std::move(newState);
  Logger::log("[STATE] Incident #" + std::to_string(id_) + ": " + from +
                            " -> " + to);
}
