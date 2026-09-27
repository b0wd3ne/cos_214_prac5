#ifndef CAMPUS_BUILDING_H
#define CAMPUS_BUILDING_H
#include <memory>
#include <vector>
#include "CampusArea.h"

class Building : public CampusArea {
public:
    explicit Building(const std::string& name);

    void setAccess(AccessMode mode) override;      // recurses into children
    AccessMode accessMode() const override;         // the building's own state
    std::string name() const override;
    void add(std::unique_ptr<CampusArea> child) override;
    CampusArea* find(const std::string& areaName) override;

private:
    std::string name_;
    AccessMode access_;
    std::vector<std::unique_ptr<CampusArea>> children_; // Building owns its children
};

#endif
