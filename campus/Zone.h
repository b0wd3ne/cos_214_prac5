#ifndef ZONE_H
#define ZONE_H
#include "CampusArea.h"

class Zone : public CampusArea {
public:
    explicit Zone(const std::string& name);

    void setAccess(AccessMode mode) override;
    AccessMode accessMode() const override;
    std::string name() const override;
    CampusArea* find(const std::string& areaName) override;

private:
    std::string name_;
    AccessMode access_;
};

#endif