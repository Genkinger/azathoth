#pragma once
#include "AzLoggerSink.hpp"

namespace Az{
    class LoggerConsoleSink : public LoggerSink{
        public:
            LoggerConsoleSink(const std::string& name = "default", LogLevel log_level = LogLevel::Debug): LoggerSink(name,log_level){}
            ~LoggerConsoleSink(){}
            void Dispatch(const std::string& string){
                 std::cout << string << std::endl;
            }
            
    };
}