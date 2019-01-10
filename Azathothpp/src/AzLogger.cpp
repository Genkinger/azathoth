#include "log/AzLogger.hpp"

namespace Az{
    Logger::Logger(const std::string& name) : mName(name), mPrefix("["+mName+"]: "){
        mDefaultSink = new LoggerConsoleSink();
        AttachSink(mDefaultSink);
        Info("Logger initialized...");
    }
    Logger::~Logger(){
        DetachSink(mDefaultSink);
        for(auto sink : mSinks){
            DetachSink(sink);
        }
        delete mDefaultSink;
    }
    void Logger::AttachSink(LoggerSink* sink){
        mSinks.push_back(sink);
        Info("Attached sink '"+sink->GetName()+"'...");
    }
    void Logger::DetachSink(LoggerSink* sink){
        mSinks.erase(std::remove(std::begin(mSinks),std::end(mSinks),sink));
    }
    void Logger::Critical(const std::string& string) const{
        std::stringstream ss;
        ss << mPrefix << ConsoleColor::FG_RED << string << ConsoleColor::FG_DEFAULT;
        Log(ss.str(),LogLevel::Critical);
    }
    void Logger::Info(const std::string& string) const{
        std::stringstream ss;
        ss << mPrefix << ConsoleColor::FG_BLUE << string << ConsoleColor::FG_DEFAULT;
        Log(ss.str(),LogLevel::Info);
    }
    void Logger::Warn(const std::string& string) const{
        std::stringstream ss;
        ss << mPrefix << ConsoleColor::FG_YELLOW << string << ConsoleColor::FG_DEFAULT;
        Log(ss.str(),LogLevel::Warn);
    }
    void Logger::Log(const std::string& string, LogLevel log_level) const {
        for(auto sink : mSinks){
            if(sink){
                if(sink->GetLogLevel() <= log_level){
                    sink->Dispatch(string);
                }
            }
        }
    }
}