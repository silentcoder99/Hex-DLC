#include "Logger.h"

class STDOutLogger : public Logger{
    int m_debugLevel;
public:
    STDOutLogger(int debugLevel);

    void logInfo(std::string message, int debugLevel);
    void logWarning(std::string message);
    void logError(std::string message);
};
