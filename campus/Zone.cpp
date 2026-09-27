#include "Zone.h"
#include "../common/Logger.h"
#include "../common/TypeUtils.h"

Zone::Zone(const std::string& name) : name_(name), access_(AccessMode::Open) {}

void Zone::setAccess(AccessMode mode) {
    access_ = mode;
    Logger::log("[CAMPUS] Zone '" + name_ + "' access set to " + toString(mode));
}

AccessMode Zone::accessMode() const { return access_; }

std::string Zone::name() const { return name_; }

CampusArea* Zone::find(const std::string& areaName) {
    return (areaName == name_) ? this : nullptr;
}
