// response/SecurityTeam.h
#ifndef SECURITY_TEAM_H
#define SECURITY_TEAM_H

#include "ResponseComponent.h"
#include "ResponseEvent.h"

class Incident;

class SecurityTeam : public ResponseComponent {
public:
    SecurityTeam(const std::string& name, ResponseMediator* mediator);
    ~SecurityTeam() override;

    // Called by Person A's DispatchUnitCommand::execute()
    void dispatchTo(Incident& incident) override;

    void handle(const ResponseEvent& e) override;

    bool isAvailable() const override { return available_; }

private:
    bool available_;
};

#endif // SECURITY_TEAM_H
