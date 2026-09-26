#ifndef CAMPUSGUARD_INCIDENT_INCIDENT_REGISTRY_H
#define CAMPUSGUARD_INCIDENT_INCIDENT_REGISTRY_H

#include <memory>
#include <string>
#include <vector>

#include "Incident.h"

// Owns every Incident for the lifetime of the application and hands out
// non-owning references/pointers to whoever needs to read or act on one
// (commands, the facade, scenarios). Assigns incident IDs so nothing else
// has to.
class IncidentRegistry {
 public:
  Incident& create(const std::string& description, IncidentType type,
                    Severity severity, const std::string& areaName);

  Incident* find(int id);  // nullptr if no incident has that id

  std::size_t count() const { return incidents_.size(); }

 private:
  std::vector<std::unique_ptr<Incident>> incidents_;  // ownership lives here
  int nextId_ = 1;
};

#endif  // CAMPUSGUARD_INCIDENT_INCIDENT_REGISTRY_H
