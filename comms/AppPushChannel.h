#ifndef APPPUSHCHANNEL_H
#define APPPUSHCHANNEL_H
#include "NotificationChannel.h"

// A modern channel that already speaks NotificationChannel - no
// adapting needed. Used alongside LegacyPagerAdapter to show two concrete
// channels behind the same interface.
class AppPushChannel : public NotificationChannel {
public:
    void send(const AlertMessage& alert) override;
    std::string channelName() const override { return "AppPush"; }
};

#endif 
