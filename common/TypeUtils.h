#ifndef TYPEUTILS_H
#define TYPEUTILS_H

#include <string>
#include "Types.h"

inline std::string toString(AccessMode mode) {
    switch (mode) {
        case AccessMode::Open:       return "Open";
        case AccessMode::Restricted: return "Restricted";
        case AccessMode::Locked:     return "Locked";
    }
    return "Unknown";
}

inline std::string toString(Severity s) {
    switch (s) {
        case Severity::Low:      return "Low";
        case Severity::Medium:   return "Medium";
        case Severity::High:     return "High";
        case Severity::Critical: return "Critical";
    }
    return "Unknown";
}

#endif 
