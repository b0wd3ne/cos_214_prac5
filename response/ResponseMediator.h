#ifndef RESPONSE_MEDIATOR_H
#define RESPONSE_MEDIATOR_H

class ResponseComponent;
struct ResponseEvent;

class ResponseMediator {
public:
    virtual ~ResponseMediator() {}
    virtual void notify(ResponseComponent* sender, const ResponseEvent& e) = 0;
};

#endif // RESPONSE_MEDIATOR_H