#ifndef NOTIFICATIONCHANNEL_H
#define NOTIFICATIONCHANNEL_H
#include <string>
#include "../common/Types.h"

// Adapter pattern - Target interface.
struct AlertMessage {
    std::string text;
    Severity severity;
    std::string areaName;
};

class NotificationChannel {
public:
    virtual ~NotificationChannel() {}
    virtual void send(const AlertMessage& alert) = 0; // throws CommsFailure
    virtual std::string channelName() const = 0;
};

#endif 
