#ifndef DEBUG
#define DEBUG

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Astrocore
{
    class Debug
    {
        private:
            inline static std::string loggingFile = "";

        public:

        // Log a line to the console/file log
        static inline void LogLine(std::string logEntry)
        {
            fmt::print(logEntry + "\n");
        };

        static inline void LogWarning(std::string warningEntry)
        {
            spdlog::warn(warningEntry);
        }

        static inline void LogError(std::string errorEntry)
        {
            spdlog::error(errorEntry);
        }
        // TODO: Add writing to files
        // TODO: Add assert functionality
    };
}

// Macros
#define DBG_LOG(...) ::Astrocore::Debug::LogLine(__VA_ARGS__)
#define DBG_WARN(...) ::Astrocore::Debug::LogWarning(__VA_ARGS__)
#define DBG_ERR(...) ::Astrocore::Debug::LogError(__VA_ARGS__)
#endif