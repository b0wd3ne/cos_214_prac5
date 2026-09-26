#ifndef RESPONSE_COMPONENT_H
#define RESPONSE_COMPONENT_H

#include <string>
#include "ResponseMediator.h"
#include "ResponseEvent.h"

// GoF Mediator role: Colleague. SecurityTeam, MedicalTeam, FacilitiesCrew,
// AccessControlCentre and CommunicationsCentre all derive from this.
// A colleague never talks to another colleague directly - only through
// report(), which forwards to the mediator.
class ResponseComponent {
public:
    ResponseComponent(const std::string& name, ResponseMediator* mediator)
        : name_(name), mediator_(mediator) {}

    virtual ~ResponseComponent() {}

    // Subclasses react to events routed to them by the mediator.
    virtual void handle(const ResponseEvent& e) = 0;

    const std::string& name() const { return name_; }

protected:
    // Colleagues call this instead of reaching for another colleague.
    void report(const ResponseEvent& e) {
        if (mediator_) {
            mediator_->notify(this, e);
        }
    }

    std::string name_;
    ResponseMediator* mediator_;
};

#endif // RESPONSE_COMPONENT_H