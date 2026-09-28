// response/MedicalTeam.h
#ifndef MEDICAL_TEAM_H
#define MEDICAL_TEAM_H

#include "ResponseComponent.h"
#include "ResponseEvent.h"

class Incident;

class MedicalTeam : public ResponseComponent {
public:
    MedicalTeam(const std::string& name, ResponseMediator* mediator);
    ~MedicalTeam() override;

    void dispatchTo(Incident& incident) override;
    void handle(const ResponseEvent& e) override;

    bool isAvailable() const override { return available_; }

private:
    bool available_;
};

#endif // MEDICAL_TEAM_H
