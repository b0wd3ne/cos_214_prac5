#ifndef CAMPUSGUARD_INCIDENT_INCIDENT_H
#define CAMPUSGUARD_INCIDENT_INCIDENT_H

#include <memory>
#include <string>

#include "IncidentState.h"
#include "../common/Types.h"

// Context (GoF State). Owns its current IncidentState and delegates every
// lifecycle call to it, so Incident itself never needs to know which
// transitions are legal - that knowledge lives entirely in the states.
class Incident {
 public:
  Incident(int id, const std::string& description, IncidentType type,
           Severity severity, const std::string& areaName);

  // Not copyable (it owns a unique_ptr and represents one real incident);
  // moving is fine if you ever need it, but isn't required by the practical.
  Incident(const Incident&) = delete;
  Incident& operator=(const Incident&) = delete;

  void verify();
  void dispatch();
  void contain();
  void resolve();
  void cancel();

  // Called by IncidentState subclasses to perform a transition. Public so
  // the state classes (which are not members of Incident) can call it, but
  // ordinary client code should drive transitions via verify()/dispatch()/
  // etc. above rather than calling this directly.
  void setState(std::unique_ptr<IncidentState> newState);

  int id() const { return id_; }
  const std::string& description() const { return description_; }
  IncidentType type() const { return type_; }
  Severity severity() const { return severity_; }
  const std::string& areaName() const { return areaName_; }
  std::string stateName() const { return state_->name(); }

 private:
  int id_;
  std::string description_;
  IncidentType type_;
  Severity severity_;
  std::string areaName_;
  std::unique_ptr<IncidentState> state_;  // Incident owns its current state
};

#endif  // CAMPUSGUARD_INCIDENT_INCIDENT_H
