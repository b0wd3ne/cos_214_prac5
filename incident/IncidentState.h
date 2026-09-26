#ifndef CAMPUSGUARD_INCIDENT_INCIDENT_STATE_H
#define CAMPUSGUARD_INCIDENT_INCIDENT_STATE_H

#include <string>

class Incident;  // forward declaration: state and incident refer to each other

// ---- State (GoF) ---------------------------------------------------------
// Context  = Incident
// State    = IncidentState
// Concrete = ReportedState, VerifiedState, DispatchedState, ContainedState,
//            ResolvedState, CancelledState
//
// Every method has a default body in the base class that rejects the
// transition. A concrete state only overrides the one or two transitions
// that are legal from it, so illegal transitions can never be "forgotten" -
// they simply fall through to the base class and throw. This is what
// replaces the switch-on-enum / if-chain the practical spec forbids.
class IncidentState {
 public:
  virtual ~IncidentState() {}

  virtual void verify(Incident& incident);
  virtual void dispatch(Incident& incident);
  virtual void contain(Incident& incident);
  virtual void resolve(Incident& incident);
  virtual void cancel(Incident& incident);

  virtual std::string name() const = 0;

 protected:
  // Shared by every "this transition is not allowed" case.
  void reject(const std::string& action) const;
};

class ReportedState : public IncidentState {
 public:
  void verify(Incident& incident) override;
  void cancel(Incident& incident) override;
  std::string name() const override { return "Reported"; }
};

class VerifiedState : public IncidentState {
 public:
  void dispatch(Incident& incident) override;
  void cancel(Incident& incident) override;
  std::string name() const override { return "Verified"; }
};

class DispatchedState : public IncidentState {
 public:
  void contain(Incident& incident) override;
  void cancel(Incident& incident) override;
  std::string name() const override { return "Dispatched"; }
};

class ContainedState : public IncidentState {
 public:
  void resolve(Incident& incident) override;
  std::string name() const override { return "Contained"; }
};

// Resolved and Cancelled are terminal: they override nothing, so every
// transition attempted from them falls through to the base class and throws.
class ResolvedState : public IncidentState {
 public:
  std::string name() const override { return "Resolved"; }
};

class CancelledState : public IncidentState {
 public:
  std::string name() const override { return "Cancelled"; }
};

#endif  // CAMPUSGUARD_INCIDENT_INCIDENT_STATE_H
