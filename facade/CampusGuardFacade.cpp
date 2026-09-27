#include "CampusGuardFacade.h"
#include "../common/Logger.h"

CampusGuardFacade::CampusGuardFacade(CampusArea* campusRoot,
                                      AccessControlCentre* accessControl,
                                      CommunicationsCentre* comms)
    : campusRoot_(campusRoot), access_(accessControl), comms_(comms) {
    verifyIncident_ = [](int) { Logger::log("[FACADE] (no verify-incident hook wired yet)"); };
    dispatchUnit_ = [](const std::string& unit, const std::string& area) {
        Logger::log("[FACADE] (no dispatch hook wired yet) would dispatch " + unit + " to " + area);
    };
}

void CampusGuardFacade::setVerifyIncidentHook(VerifyIncidentHook hook) { verifyIncident_ = std::move(hook); }
void CampusGuardFacade::setDispatchHook(DispatchHook hook) { dispatchUnit_ = std::move(hook); }

void CampusGuardFacade::respondToFire(int incidentId, const std::string& buildingName) {
    Logger::log("[FACADE] respondToFire('" + buildingName + "') starting");

    verifyIncident_(incidentId);
    dispatchUnit_("Security", buildingName);
    dispatchUnit_("Facilities", buildingName);
    access_->setAreaAccess(buildingName, AccessMode::Locked);
    comms_->broadcastAlert(buildingName, Severity::Critical,
                            "Fire response in progress at " + buildingName);

    Logger::log("[FACADE] respondToFire('" + buildingName + "') complete");
}

void CampusGuardFacade::evacuateBuilding(int incidentId, const std::string& buildingName) {
    Logger::log("[FACADE] evacuateBuilding('" + buildingName + "') starting");

    verifyIncident_(incidentId);
    dispatchUnit_("Medical", buildingName);
    access_->setAreaAccess(buildingName, AccessMode::Restricted);
    comms_->broadcastEvacuation(buildingName, "Evacuate " + buildingName + " immediately");

    Logger::log("[FACADE] evacuateBuilding('" + buildingName + "') complete");
}

void CampusGuardFacade::standDown(const std::string& buildingName) {
    Logger::log("[FACADE] standDown('" + buildingName + "') starting");

    access_->setAreaAccess(buildingName, AccessMode::Open);
    comms_->broadcastAlert(buildingName, Severity::Low,
                            buildingName + " is now clear, all-clear issued");

    Logger::log("[FACADE] standDown('" + buildingName + "') complete");
}