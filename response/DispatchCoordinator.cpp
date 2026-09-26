#include "DispatchCoordinator.h"

DispatchCoordinator::~DispatchCoordinator() {
}

// The way I implement it is that the mediator informs specific colleagues using the list of colleagues to inform stored in the map
// E.g. FireNotice -> Inform Facilitis, Medical Team and Security Team
void DispatchCoordinator::notify(ResponseComponent* sender, const ResponseEvent& e) {
    for(ResponseComponent* c : routingTable[e.type]) {
        if(sender == c) continue;
        c->handle(e);
    }
}
DispatchCoordinator::DispatchCoordinator() {
    
}
void DispatchCoordinator::registerComponent(ResponseEvent::Type type, ResponseComponent* component) {
    routingTable[type].push_back(component);
}