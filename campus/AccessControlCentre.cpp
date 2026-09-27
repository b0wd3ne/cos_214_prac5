#include "AccessControlCentre.h"
#include "../common/Exceptions.h"
#include "../common/Logger.h"
#include "../common/TypeUtils.h"

AccessControlCentre::AccessControlCentre(CampusArea* campusRoot, ResponseMediator* mediator)
    : ResponseComponent("AccessControlCentre", mediator), campusRoot_(campusRoot) {}

void AccessControlCentre::setAreaAccess(const std::string& areaName, AccessMode mode) {
    CampusArea* area = campusRoot_->find(areaName);
    if (area == nullptr) {
        throw UnknownAreaException("AccessControlCentre: unknown area '" + areaName + "'");
    }

    area->setAccess(mode);

    ResponseEvent event(ResponseEvent::Type::AreaSecured, nullptr,
                         "AccessControlCentre set '" + areaName + "' to " + toString(mode));
    report(event);
}

AccessMode AccessControlCentre::areaAccess(const std::string& areaName) const {
    CampusArea* area = campusRoot_->find(areaName);
    if (area == nullptr) {
        throw UnknownAreaException("AccessControlCentre: unknown area '" + areaName + "'");
    }
    return area->accessMode();
}

void AccessControlCentre::handle(const ResponseEvent& e) {
    Logger::log("[ACCESS] Observed event: " + e.detail);
}