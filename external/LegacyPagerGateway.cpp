#include "LegacyPagerGateway.h"
#include <cstring>
#include <iostream>

int LegacyPagerGateway::sendPage(const char* zoneCodesCsv, const char* payload, int urgency0to9) {
    if (zoneCodesCsv == nullptr || std::strlen(zoneCodesCsv) == 0) {
        return ERR_BAD_ZONE;
    }
    if (payload == nullptr || std::strlen(payload) > 80) {
        return ERR_MESSAGE_TOO_LONG;
    }
    if (urgency0to9 < 0 || urgency0to9 > 9) {
        return ERR_URGENCY_OUT_OF_RANGE;
    }

    std::cout << "[LEGACY PAGER HARDWARE] zones=" << zoneCodesCsv
              << " urgency=" << urgency0to9
              << " msg=\"" << payload << "\"" << std::endl;
    return SUCCESS;
}
