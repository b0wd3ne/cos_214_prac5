#ifndef RESPONSE_EVENT_H
#define RESPONSE_EVENT_H

#include <string>

class Incident;

struct ResponseEvent {
    enum class Type {
        ThreatConfirmed,
        UnitOnScene,
        CasualtiesReported,
        AreaSecured,
        IncidentResolved
    };

    Type type;
    Incident* incident;   // non-owning
    std::string detail;

    ResponseEvent(Type t, Incident* inc, const std::string& d = "")
        : type(t), incident(inc), detail(d) {}
};

#endif // RESPONSE_EVENT_H