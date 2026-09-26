// Defined by Tafadzwa
// EXCEPTIONS.H

// common/Exceptions.h
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class InvalidTransitionException : public std::runtime_error {
public:
    explicit InvalidTransitionException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class UnitUnavailableException : public std::runtime_error {
public:
    explicit UnitUnavailableException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class CommsFailure : public std::runtime_error {
public:
    explicit CommsFailure(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif // EXCEPTIONS_H