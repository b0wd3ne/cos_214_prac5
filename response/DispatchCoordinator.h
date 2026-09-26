#ifndef DISPATCH_COORDINATOR_H
#define DISPATCH_COORDINATOR_H
#include "ResponseMediator.h"
#include "ResponseComponent.h"
#include "ResponseEvent.h"
#include <map>
#include <vector>

class DispatchCoordinator : public ResponseMediator{
    // The table that decides what response components are notified by a message
    std::map<ResponseEvent::Type, std::vector<ResponseComponent*>> routingTable;
public:
    DispatchCoordinator();
    ~DispatchCoordinator();
    virtual void notify(ResponseComponent* sender, const ResponseEvent& e) override;
    void registerComponent(ResponseEvent::Type eventType, ResponseComponent* component);
};

#endif // DISPATCH_COORDINATOR_H