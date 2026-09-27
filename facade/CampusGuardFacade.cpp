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
    access_->secureArea(buildingName, AccessMode::Locked);

    AlertMessage alert;
    alert.text = "Fire response in progress at " + buildingName;
    alert.severity = Severity::Critical;
    alert.areaName = buildingName;
    comms_->broadcastAlert(alert);

    Logger::log("[FACADE] respondToFire('" + buildingName + "') complete");
}

void CampusGuardFacade::evacuateBuilding(int incidentId, const std::string& buildingName) {
    Logger::log("[FACADE] evacuateBuilding('" + buildingName + "') starting");

    verifyIncident_(incidentId);
    dispatchUnit_("Medical", buildingName);
    access_->secureArea(buildingName, AccessMode::Restricted);

    AlertMessage alert;
    alert.text = "Evacuate " + buildingName + " immediately";
    alert.severity = Severity::High;
    alert.areaName = buildingName;
    comms_->broadcastAlert(alert);

    Logger::log("[FACADE] evacuateBuilding('" + buildingName + "') complete");
}

void CampusGuardFacade::standDown(const std::string& buildingName) {
    Logger::log("[FACADE] standDown('" + buildingName + "') starting");

    access_->secureArea(buildingName, AccessMode::Open);

    AlertMessage alert;
    alert.text = buildingName + " is now clear, all-clear issued";
    alert.severity = Severity::Low;
    alert.areaName = buildingName;
    comms_->broadcastAlert(alert);

    Logger::log("[FACADE] standDown('" + buildingName + "') complete");
}
