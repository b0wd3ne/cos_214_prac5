// response/FacilitiesCrew.cpp
#include "FacilitiesCrew.h"
#include "../incident/Incident.h"
#include "../common/Logger.h"
#include "../common/Exceptions.h"

FacilitiesCrew::FacilitiesCrew(const std::string& name, ResponseMediator* mediator)
    : ResponseComponent(name, mediator), available_(true) {}

FacilitiesCrew::~FacilitiesCrew() {}

void FacilitiesCrew::dispatchTo(Incident& incident) {
    if (!available_) {
        throw UnitUnavailableException(name_ + " is not available");
    }
    Logger::log("[RECEIVER] " + name_ + " dispatched to incident");
    available_ = false;
    report(ResponseEvent(ResponseEvent::Type::UnitOnScene, &incident, name_ + " on scene"));
}

void FacilitiesCrew::handle(const ResponseEvent& e) {
    // This is where FacilitiesCrew actually reacts, unlike SecurityTeam:
    // it's the standby-on-severity target from DispatchCoordinator's
    // conditional branch, so make that visible in the log.
    Logger::log("[COLLEAGUE] " + name_ + " standing by (routed by mediator)");
    (void)e;
}