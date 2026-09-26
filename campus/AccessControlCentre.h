#ifndef CAMPUSGUARD_CAMPUS_ACCESS_CONTROL_CENTRE_H
#define CAMPUSGUARD_CAMPUS_ACCESS_CONTROL_CENTRE_H

// =====================================================================
// STUB - owned by Person C (Composite / campus slice).
// Agreed CONTRACT that SecureAreaCommand codes against. Person C replaces
// this with the real class, which will walk the CampusArea/Building/Zone
// composite tree. Do not change these signatures without telling Person A.
// =====================================================================

#include <string>

#include "../common/Types.h"

class AccessControlCentre {
 public:
  virtual ~AccessControlCentre() {}

  virtual void setAreaAccess(const std::string& areaName, AccessMode mode) = 0;
  virtual AccessMode areaAccess(const std::string& areaName) const = 0;
};

#endif  // CAMPUSGUARD_CAMPUS_ACCESS_CONTROL_CENTRE_H
