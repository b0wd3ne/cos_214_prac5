// Defined by Tafadzwa
// common/Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class Logger {
public:
    static void log(const std::string& message) {
        std::cout << message << std::endl;
    }
};

#endif // LOGGER_H