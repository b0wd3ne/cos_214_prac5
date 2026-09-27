#include "IncidentRegistry.h"

Incident& IncidentRegistry::create(const std::string& description,
                                    IncidentType type, Severity severity,
                                    const std::string& areaName) {
  incidents_.push_back(std::unique_ptr<Incident>(
      new Incident(nextId_++, description, type, severity, areaName)));
  return *incidents_.back();
}

Incident* IncidentRegistry::find(int id) {
  for (auto& incident : incidents_) {
    if (incident->id() == id) return incident.get();
  }
  return nullptr;
}
