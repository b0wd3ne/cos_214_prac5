#ifndef CAMPUSGUARDFACADE_H
#define CAMPUSGUARDFACADE_H
#include <functional>
#include <string>
#include "../campus/AccessControlCentre.h"
#include "../comms/CommunicationsCentre.h"
#include "../common/Types.h"

// Facade pattern - Facade.
//
//   facade.setVerifyIncidentHook([&](int id) { registry.find(id)->verify(); });
//   facade.setDispatchHook([&](const std::string& unit, const std::string& area) {
//       console.execute(unique_ptr<Command>(new DispatchUnitCommand(unit, area)));
//   });
class CampusGuardFacade {
public:
    using VerifyIncidentHook = std::function<void(int incidentId)>;
    using DispatchHook = std::function<void(const std::string& unitType, const std::string& areaName)>;

    CampusGuardFacade(CampusArea* campusRoot,
                       AccessControlCentre* accessControl,
                       CommunicationsCentre* comms);

    void setVerifyIncidentHook(VerifyIncidentHook hook);
    void setDispatchHook(DispatchHook hook);

    // Subsystem operations coordinated: verify incident, dispatch security,
    // dispatch facilities, lock the building, broadcast the alert.
    void respondToFire(int incidentId, const std::string& buildingName);

    // Subsystem operations coordinated: verify incident, dispatch medical,
    // restrict the building, broadcast an evacuation alert.
    void evacuateBuilding(int incidentId, const std::string& buildingName);

    // Subsystem operations coordinated: reopen the building, broadcast an
    // all-clear alert.
    void standDown(const std::string& buildingName);

private:
    CampusArea* campusRoot_;      // non-owning
    AccessControlCentre* access_; // non-owning
    CommunicationsCentre* comms_; // non-owning
    VerifyIncidentHook verifyIncident_;
    DispatchHook dispatchUnit_;
};

#endif 
