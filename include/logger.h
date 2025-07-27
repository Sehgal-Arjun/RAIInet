#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <memory>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    std::ofstream logFile;
    
    Logger() {
        logFile.open("run.log", std::ios::out | std::ios::app);
        if (logFile.is_open()) {
            logFile << "\n=== NEW RUN STARTED ===" << std::endl;
        }
    }

public:
    static Logger& getInstance() {
        if (!instance) {
            instance = std::unique_ptr<Logger>(new Logger());
        }
        return *instance;
    }
    
    void log(const std::string& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
            logFile.flush();
        }
    }
    
    ~Logger() {
        if (logFile.is_open()) {
            logFile << "=== RUN ENDED ===" << std::endl;
            logFile.close();
        }
    }
};

#endif // LOGGER_H
