#include "LegacyPagerAdapter.h"
#include "../common/Exceptions.h"
#include "../common/Logger.h"

LegacyPagerAdapter::LegacyPagerAdapter(std::unique_ptr<LegacyPagerGateway> gateway)
    : gateway_(std::move(gateway)) {}

void LegacyPagerAdapter::registerZoneCode(const std::string& areaName, const std::string& zoneCode) {
    zoneCodes_[areaName] = zoneCode;
}

int LegacyPagerAdapter::severityToUrgency(Severity s) {
    switch (s) {
        case Severity::Low:      return 2;
        case Severity::Medium:   return 4;
        case Severity::High:     return 7;
        case Severity::Critical: return 9;
    }
    return 0;
}

std::string LegacyPagerAdapter::zoneCodeFor(const std::string& areaName) const {
    std::map<std::string, std::string>::const_iterator it = zoneCodes_.find(areaName);
    return (it != zoneCodes_.end()) ? it->second : std::string();
}

std::string LegacyPagerAdapter::truncateTo80(const std::string& text) {
    return (text.size() > 80) ? text.substr(0, 80) : text;
}

void LegacyPagerAdapter::send(const AlertMessage& alert) {
    std::string zoneCode = zoneCodeFor(alert.areaName);
    std::string payload = truncateTo80(alert.text);
    int urgency = severityToUrgency(alert.severity);

    int result = gateway_->sendPage(zoneCode.c_str(), payload.c_str(), urgency);

    if (result != LegacyPagerGateway::SUCCESS) {
        throw CommsFailure("LegacyPagerAdapter: gateway returned error code " +
                            std::to_string(result) + " for area '" + alert.areaName + "'");
    }

    Logger::log("[ADAPTER] Translated alert for '" + alert.areaName +
                "' into legacy page (zone='" + zoneCode + "', urgency=" +
                std::to_string(urgency) + ")");
}
