#include "CommunicationsCentre.h"
#include "../common/Exceptions.h"
#include "../common/Logger.h"

CommunicationsCentre::CommunicationsCentre(ResponseMediator* mediator)
    : ResponseComponent("CommunicationsCentre", mediator) {}

void CommunicationsCentre::addChannel(NotificationChannel* channel) {
    channels_.push_back(channel);
}

void CommunicationsCentre::broadcastAlert(const AlertMessage& alert) {
    bool anySucceeded = false;

    for (std::vector<NotificationChannel*>::iterator it = channels_.begin(); it != channels_.end(); ++it) {
        NotificationChannel* channel = *it;
        try {
            channel->send(alert);
            anySucceeded = true;
        } catch (const CommsFailure& ex) {
            Logger::log(std::string("[COMMS] Channel '") + channel->channelName() +
                        "' failed: " + ex.what() + " - trying remaining channels");
        }
    }

    if (!anySucceeded) {
        Logger::log("[COMMS] All channels failed to deliver the alert for " + alert.areaName);
    }
}

void CommunicationsCentre::handle(const ResponseEvent& e) {
    Logger::log("[COMMS] Observed event: " + e.detail);
}
