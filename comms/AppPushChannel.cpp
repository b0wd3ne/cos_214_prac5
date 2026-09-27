#include "AppPushChannel.h"
#include "../common/Logger.h"
#include "../common/TypeUtils.h"

void AppPushChannel::send(const AlertMessage& alert) {
    Logger::log("[COMMS] [AppPush] " + alert.areaName + ": " + alert.text +
                " (severity=" + toString(alert.severity) + ")");
}
