#include "AccessControlCentre.h"
#include "../common/Exceptions.h"
#include "../common/TypeUtils.h"
#include "../common/Logger.h"

AccessControlCentre::AccessControlCentre(CampusArea* campusRoot, ResponseMediator* mediator)
    : ResponseComponent("AccessControlCentre", mediator), campusRoot_(campusRoot) {}

AccessMode AccessControlCentre::secureArea(const std::string& areaName, AccessMode mode) {
    CampusArea* area = campusRoot_->find(areaName);
    if (area == nullptr) {
        throw UnknownAreaException("AccessControlCentre: unknown area '" + areaName + "'");
    }

    AccessMode previous = area->accessMode();
    area->setAccess(mode);

    ResponseEvent event(ResponseEvent::Type::AreaSecured, nullptr,
                         "AccessControlCentre set '" + areaName + "' to " + toString(mode));
    report(event);

    return previous;
}

void AccessControlCentre::handle(const ResponseEvent& e) {
    // AccessControlCentre mostly acts (via secureArea) rather than reacts to
    // other colleagues, but it still logs what the mediator routes to it.
    Logger::log("[ACCESS] Observed event: " + e.detail);
}
