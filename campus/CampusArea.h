#ifndef CAMPUSAREA_H
#define CAMPUSAREA_H
#include <memory>
#include <stdexcept>
#include <string>
#include "../common/Types.h"

// Composite pattern - Component.
class CampusArea {
public:
    virtual ~CampusArea() {}
    virtual void setAccess(AccessMode mode) = 0;
    virtual AccessMode accessMode() const = 0;
    virtual std::string name() const = 0;

    virtual void add(std::unique_ptr<CampusArea> child) {
        (void)child;
        throw std::logic_error(name() + " cannot contain other areas");
    }

    virtual CampusArea* find(const std::string& areaName) = 0;
};

#endif
