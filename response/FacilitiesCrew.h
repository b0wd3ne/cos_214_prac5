// response/FacilitiesCrew.h
#ifndef FACILITIES_CREW
#define FACILITIES_CREW

#include "ResponseComponent.h"
#include "ResponseEvent.h"

class Incident;

class FacilitiesCrew : public ResponseComponent {
public:
    FacilitiesCrew(const std::string& name, ResponseMediator* mediator);
    ~FacilitiesCrew() override;

    // Called by Person A's DispatchUnitCommand::execute()
    void dispatchTo(Incident& incident) override;

    void handle(const ResponseEvent& e) override;

    bool isAvailable() const override { return available_; }

private:
    bool available_;
};

#endif // FACILITIES_CREW
