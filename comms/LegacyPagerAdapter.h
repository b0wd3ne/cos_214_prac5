#ifndef LEGACYPAGERADAPTER_H
#define LEGACYPAGERADAPTER_H
#include <map>
#include <memory>
#include "NotificationChannel.h"
#include "../external/LegacyPagerGateway.h"

// Adapter pattern - Adapter.
// Translates the modern NotificationChannel interface into calls on the
// awkward, C-style LegacyPagerGateway (the Adaptee): maps Severity to a
// 0-9 urgency, maps an area name to a legacy zone code, truncates the
// message to the hardware's 80-character limit, and turns integer error
// codes into a CommsFailure exception.
class LegacyPagerAdapter : public NotificationChannel {
public:
    // explicit LegacyPagerAdapter(std::unique_ptr<LegacyPagerGateway> gateway);

    void send(const AlertMessage& alert) override; // throws CommsFailure
    std::string channelName() const override { return "LegacyPager"; }

    // Lets the composition root (or a test scenario) map building/zone names
    // onto the legacy system's own zone codes.
    void registerZoneCode(const std::string& areaName, const std::string& zoneCode);

private:
    static int severityToUrgency(Severity s);
    std::string zoneCodeFor(const std::string& areaName) const;
    static std::string truncateTo80(const std::string& text);

    // std::unique_ptr<LegacyPagerGateway> gateway_; // owns its adaptee
    std::map<std::string, std::string> zoneCodes_;
};

#endif 