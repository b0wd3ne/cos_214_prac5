#ifndef COMMUNICATIONS_CENTRE_H
#define COMMUNICATIONS_CENTRE_H

#include <string>
#include <vector>
#include "../common/Types.h"
#include "../response/ResponseComponent.h"
#include "NotificationChannel.h"

class CommunicationsCentre : public ResponseComponent {
 public:
  explicit CommunicationsCentre(ResponseMediator* mediator);

  void addChannel(NotificationChannel* channel); // non-owning;

  void broadcastAlert(const std::string& areaName, Severity severity,
                       const std::string& message);
  void broadcastEvacuation(const std::string& areaName, const std::string& message);

  void handle(const ResponseEvent& e) override;

 private:
  std::vector<NotificationChannel*> channels_; // non-owning
};

#endif  // CAMPUSGUARD_COMMS_COMMUNICATIONS_CENTRE_H