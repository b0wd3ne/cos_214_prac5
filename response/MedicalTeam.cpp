// response/MedicalTeam.cpp
#include "MedicalTeam.h"
#include "../incident/Incident.h"
#include "../common/Logger.h"
#include "../common/Exceptions.h"

MedicalTeam::MedicalTeam(const std::string& name, ResponseMediator* mediator)
    : ResponseComponent(name, mediator), available_(true) {}

MedicalTeam::~MedicalTeam() {}

void MedicalTeam::dispatchTo(Incident& incident) {
    if (!available_) {
        throw UnitUnavailableException(name_ + " is not available");
    }
    Logger::log("[RECEIVER] " + name_ + " dispatched to incident");
    available_ = false;
    report(ResponseEvent(ResponseEvent::Type::UnitOnScene, &incident, name_ + " on scene"));
}

void MedicalTeam::handle(const ResponseEvent& e) {
    // This is where MedicalTeam actually reacts, unlike SecurityTeam:
    // it's the standby-on-severity target from DispatchCoordinator's
    // conditional branch, so make that visible in the log.
    Logger::log("[COLLEAGUE] " + name_ + " standing by (routed by mediator)");
    (void)e;
}