#ifndef LEGACYPAGERGATEWAY_H
#define LEGACYPAGERGATEWAY_H

// ---------------------------------------------------------------------------
// LEGACY THIRD-PARTY CODE.
// Simulates an old campus paging system with a C-style interface that
// CampusGuard does not control. This is the Adaptee: awkward on purpose, and
// treated as read-only "someone else's code" that the Adapter works around.
// ---------------------------------------------------------------------------
class LegacyPagerGateway {
public:
    // Error codes returned by sendPage()
    static const int SUCCESS = 0;
    static const int ERR_BAD_ZONE = -1;
    static const int ERR_MESSAGE_TOO_LONG = -2;
    static const int ERR_URGENCY_OUT_OF_RANGE = -3;

    // zoneCodesCsv: comma-separated legacy zone code(s), e.g. "Z12,Z13"
    // payload:      max 80 characters; the real hardware silently drops more
    // urgency0to9:  0 = lowest, 9 = highest
    // returns one of the codes above
    int sendPage(const char* zoneCodesCsv, const char* payload, int urgency0to9);
};

#endif 
