#include "Building.h"
#include <string>
#include "../common/Logger.h"
#include "../common/TypeUtils.h"

Building::Building(const std::string& name) : name_(name), access_(AccessMode::Open) {}

void Building::setAccess(AccessMode mode) {
    access_ = mode;
    Logger::log("[CAMPUS] Building '" + name_ + "' access set to " + toString(mode) +
                " (recursing into " + std::to_string(children_.size()) + " area(s))");
    for (auto& child : children_) {
        child->setAccess(mode);
    }
}

AccessMode Building::accessMode() const { return access_; }

std::string Building::name() const { return name_; }

void Building::add(std::unique_ptr<CampusArea> child) {
    children_.push_back(std::move(child));
}

CampusArea* Building::find(const std::string& areaName) {
    if (areaName == name_) return this;
    for (auto& child : children_) {
        if (CampusArea* found = child->find(areaName)) {
            return found;
        }
    }
    return nullptr;
}
