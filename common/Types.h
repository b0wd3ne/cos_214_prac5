#ifndef CAMPUSGUARD_COMMON_TYPES_H
#define CAMPUSGUARD_COMMON_TYPES_H

// Shared, dependency-free enums used across every slice of the project.
// Agreed on day 1 so nobody's classes disagree about what a "Severity" is.

enum class IncidentType { Fire, Medical, SecurityThreat, GasLeak };

enum class Severity { Low = 1, Medium, High, Critical };

enum class AccessMode { Open, Restricted, Locked };

#endif  // CAMPUSGUARD_COMMON_TYPES_H
