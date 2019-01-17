#pragma once
#include <string>

#include <istream>
#include <iostream>

#include "AzLogLevel.hpp"

namespace Az{
    class LoggerSink{
        protected:
            LoggerSink(std::string name, LogLevel log_level) : mName(name), mLogLevel(log_level){} 
            virtual ~LoggerSink(){}
        protected:
            std::string     mName;
            LogLevel        mLogLevel;
        public:
            virtual void Dispatch(const std::string& string) = 0;
            LogLevel GetLogLevel() const {return mLogLevel;}
            const std::string& GetName() const {return mName;}
    };
}