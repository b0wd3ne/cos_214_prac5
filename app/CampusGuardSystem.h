#ifndef CAMPUSGUARD_APP_CAMPUS_GUARD_SYSTEM_H
#define CAMPUSGUARD_APP_CAMPUS_GUARD_SYSTEM_H

#include <memory>
#include <string>

#include "../campus/AccessControlCentre.h"
#include "../campus/CampusArea.h"
#include "../comms/AppPushChannel.h"
#include "../comms/CommunicationsCentre.h"
#include "../comms/LegacyPagerAdapter.h"
#include "../facade/CampusGuardFacade.h"
#include "../incident/Incident.h"
#include "../incident/IncidentRegistry.h"
#include "../commands/OperatorConsole.h"
#include "../response/DispatchCoordinator.h"
#include "../response/FacilitiesCrew.h"
#include "../response/MedicalTeam.h"
#include "../response/SecurityTeam.h"

// Composition root. Builds and owns every object CampusGuard needs for one
// run, wires the Mediator's routing table, and wires the Facade's hooks
// back into real Commands via the OperatorConsole, so Scenarios.cpp can
// drive the two demo stories through non-owning references handed out
// below.
//
// Ownership policy (see also the PDF's ownership table):
//   - CampusGuardSystem owns everything below, via direct members or
//     unique_ptr; nothing here is owned by more than one place.
//   - campusRoot_ owns the whole Building/Zone composite tree.
//   - legacyPager_ owns its LegacyPagerGateway adaptee.
//   - console_ owns every Command it has ever executed.
//   - registry_ owns every Incident.
//   - Everything else (teams, access, comms, facade) holds non-owning
//     raw pointers to collaborators, matching the "colleagues never own
//     each other" rule of Mediator.
// Declaration order below is also construction order (and reverse
// destruction order): dependencies are declared before their dependents.
class CampusGuardSystem {
 public:
  CampusGuardSystem();

  // Not copyable/movable: components hold raw pointers back into this
  // object's other members, so copying or moving would leave them
  // dangling. One CampusGuardSystem per run is all the spec needs.
  CampusGuardSystem(const CampusGuardSystem&) = delete;
  CampusGuardSystem& operator=(const CampusGuardSystem&) = delete;

  IncidentRegistry& registry() { return registry_; }
  OperatorConsole& console() { return console_; }
  CampusGuardFacade& facade() { return *facade_; }

  SecurityTeam& security() { return security_; }
  MedicalTeam& medical() { return medical_; }
  FacilitiesCrew& facilities() { return facilities_; }
  AccessControlCentre& access() { return access_; }
  CommunicationsCentre& comms() { return comms_; }

  CampusArea& campus() { return *campusRoot_; }

  // Scenarios calls this immediately before a facade workflow so that
  // dispatchByUnitType() (wired as the Facade's dispatch hook) knows which
  // Incident to act on - the Facade's own hook signature only carries a
  // unit type and an area name, not an Incident reference.
  void setActiveIncident(Incident* incident) { activeIncident_ = incident; }

 private:
  static std::unique_ptr<CampusArea> buildCampusTree();

  // Routes an operator-facing unit type ("Security"/"Medical"/"Facilities")
  // and an area name to the matching team's DispatchUnitCommand, run
  // through the console, so that respondToFire()/evacuateBuilding() drive
  // real Commands instead of duplicating dispatch logic inside the Facade.
  void dispatchByUnitType(const std::string& unitType,
                           const std::string& areaName);

  DispatchCoordinator mediator_;  // Mediator (concrete)

  SecurityTeam security_;      // Colleague
  MedicalTeam medical_;        // Colleague
  FacilitiesCrew facilities_;  // Colleague

  std::unique_ptr<CampusArea> campusRoot_;  // Composite tree (owns children)
  AccessControlCentre access_;              // Colleague + Composite client
  CommunicationsCentre comms_;              // Colleague + Adapter client

  AppPushChannel appPush_;                           // concrete channel
  std::unique_ptr<LegacyPagerAdapter> legacyPager_;  // Adapter (owns Adaptee)

  IncidentRegistry registry_;  // owns every Incident
  OperatorConsole console_;    // Invoker, owns Command history

  std::unique_ptr<CampusGuardFacade> facade_;  // Facade

  Incident* activeIncident_ = nullptr;  // non-owning, set by Scenarios
};

#endif  // CAMPUSGUARD_APP_CAMPUS_GUARD_SYSTEM_H
