#include "CommunicationsCentre.h"
#include "../common/Exceptions.h"
#include "../common/Logger.h"

CommunicationsCentre::CommunicationsCentre(ResponseMediator* mediator)
    : ResponseComponent("CommunicationsCentre", mediator) {}

void CommunicationsCentre::addChannel(NotificationChannel* channel) {
    channels_.push_back(channel);
}

void CommunicationsCentre::broadcastAlert(const std::string& areaName, Severity severity,
                                           const std::string& message) {
    AlertMessage alert;
    alert.text = message;
    alert.severity = severity;
    alert.areaName = areaName;

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
        Logger::log("[COMMS] All channels failed to deliver the alert for " + areaName);
    }
}

void CommunicationsCentre::broadcastEvacuation(const std::string& areaName, const std::string& message) {
    broadcastAlert(areaName, Severity::Critical, "EVACUATE: " + message);
}

void CommunicationsCentre::handle(const ResponseEvent& e) {
    Logger::log("[COMMS] Observed event: " + e.detail);
}