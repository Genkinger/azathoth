#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "AzLoggerSink.hpp"
#include "AzLoggerConsoleSink.hpp"
#include "AzConsoleColor.hpp"

namespace Az{
    class Logger{
            std::string                         mName;
            std::string                         mPrefix;
            std::string                         mCriticalFormat;
            std::string                         mInfoFormat;
            std::string                         mWarnFormat;
            std::vector<LoggerSink*>            mSinks;
            LoggerConsoleSink                   *mDefaultSink;
        public:
            Logger(const std::string& name);
            ~Logger();
            void Critical(const std::string& string) const;
            void Info(const std::string& string) const;
            void Warn(const std::string& string) const;
            void Log(const std::string& string, LogLevel log_level) const;
            void AttachSink(LoggerSink* sink); 
            void DetachSink(LoggerSink* sink);
    };
}