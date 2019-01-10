#pragma once
#include "AzLoggerSink.hpp"
#include <fstream>

namespace Az{
    class LoggerFileSink : public LoggerSink{
            std::ofstream mOutFile;

        public:
            LoggerFileSink(const std::string& name = "default", LogLevel log_level = LogLevel::Debug, const std::string& file_path = "az.log")
            : LoggerSink(name,log_level), mOutFile(file_path.c_str(),std::ios::out | std::ios::app){
        
            }
            ~LoggerFileSink(){
                mOutFile.close();
            }
            void Dispatch(const std::string& string){
                if(mOutFile.is_open()){
                    mOutFile << string << std::endl;
                }else{
                    std::cout << "Error writing to file" << std::endl;
                }
            }
    };
}