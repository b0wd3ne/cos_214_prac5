#ifndef COMMUNICATIONSCENTRE_H
#define COMMUNICATIONSCENTRE_H
#include <vector>
#include "../response/ResponseComponent.h"
#include "NotificationChannel.h"

// Mediator colleague, and the Receiver for IssueAlertCommand /
// EvacuationOrderCommand. Holds non-owning pointers to channels; the channel
// objects themselves are owned by CampusGuardSystem (the composition root).
class CommunicationsCentre : public ResponseComponent {
public:
    explicit CommunicationsCentre(ResponseMediator* mediator);

    void addChannel(NotificationChannel* channel); // non-owning

    // Sends the alert on every registered channel. If one channel throws
    // CommsFailure, that failure is logged and the remaining channels still
    // get a chance to deliver the alert.
    void broadcastAlert(const AlertMessage& alert);

    void handle(const ResponseEvent& e) override;

private:
    std::vector<NotificationChannel*> channels_; // non-owning
};

#endif
