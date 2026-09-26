// response/SecurityTeam.cpp
#include "SecurityTeam.h"
#include "../incident/Incident.h"
#include "../common/Logger.h"
#include "../common/Exceptions.h"

SecurityTeam::SecurityTeam(const std::string& name, ResponseMediator* mediator)
    : ResponseComponent(name, mediator), available_(true) {}

SecurityTeam::~SecurityTeam() {}

void SecurityTeam::dispatchTo(Incident& incident) {
    if (!available_) {
        throw UnitUnavailableException(name_ + " is not available");
    }
    Logger::log("[RECEIVER] " + name_ + " dispatched to incident");
    available_ = false;
    report(ResponseEvent(ResponseEvent::Type::UnitOnScene, &incident, name_ + " on scene"));
}

void SecurityTeam::handle(const ResponseEvent& e) {
    // SecurityTeam mostly initiates events rather than reacting to them,
    // but log anything routed back so it's visible in the demo trace.
    Logger::log("[COLLEAGUE] " + name_ + " notified of event");
    (void)e;
}