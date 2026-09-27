#ifndef ACCESSCONTROLCENTRE_H
#define ACCESSCONTROLCENTRE_H
#include "../response/ResponseComponent.h"
#include "CampusArea.h"

class AccessControlCentre : public ResponseComponent {
public:
    AccessControlCentre(CampusArea* campusRoot, ResponseMediator* mediator);

    void setAreaAccess(const std::string& areaName, AccessMode mode);
    AccessMode areaAccess(const std::string& areaName) const;
    void handle(const ResponseEvent& e) override;

private:
    CampusArea* campusRoot_; // non-owning
};

#endif
