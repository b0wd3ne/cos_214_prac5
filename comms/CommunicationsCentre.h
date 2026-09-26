#ifndef CAMPUSGUARD_COMMS_COMMUNICATIONS_CENTRE_H
#define CAMPUSGUARD_COMMS_COMMUNICATIONS_CENTRE_H

// =====================================================================
// STUB - owned by Person C (Adapter / comms slice).
// Agreed CONTRACT that IssueAlertCommand and EvacuationOrderCommand code
// against. Person C replaces this with the real class, which will fan a
// message out across every registered NotificationChannel, including the
// LegacyPagerAdapter. Do not change these signatures without telling A.
// =====================================================================

#include <string>

#include "../common/Types.h"

class CommunicationsCentre {
 public:
  virtual ~CommunicationsCentre() {}

  virtual void broadcastAlert(const std::string& areaName, Severity severity,
                               const std::string& message) = 0;
  virtual void broadcastEvacuation(const std::string& areaName,
                                    const std::string& message) = 0;
};

#endif  // CAMPUSGUARD_COMMS_COMMUNICATIONS_CENTRE_H
