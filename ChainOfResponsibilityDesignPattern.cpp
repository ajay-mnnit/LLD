#include <iostream>
#include <memory>

using namespace std;

// Design a log system LLD
// Log type:
//    1. INFO
//    2. ERROR
//    3. DEBUG

class Logger
{
private:
    shared_ptr<Logger> nextLogger;
public:
    Logger(shared_ptr<Logger> next) : nextLogger(next) {};

    virtual void log(string logType)
    {
        if(nextLogger)
            nextLogger->log(logType);
        else
            cout<<"Bad logger type \n";
    }
};


class InfoLogger: public Logger
{
public:
    InfoLogger(shared_ptr<Logger> next): Logger(next){};

    void log(string logType) override
    {
        if(logType == "INFO")
        {
            // process info logs here
            cout<<"info logger system \n";
        }
        else
        {
            Logger::log(logType);
        }
    }
};


class ErrorLogger: public Logger
{
public:
    ErrorLogger(shared_ptr<Logger> next): Logger(next){};

    void log(string logType) override
    {
        if(logType == "ERROR")
        {
            // process error logs here
            cout<<"Error logger system \n";
        }
        else
        {
            Logger::log(logType);
        }
    }
};


class DebugLogger: public Logger
{
public:
    DebugLogger(shared_ptr<Logger> next): Logger(next){};

    void log(string logType) override
    {
        if(logType == "DEBUG")
        {
            // process debug logs here
            cout<<"debug logger system \n";
        }
        else
        {
            Logger::log(logType);
        }
    }
};


int main()
{
    shared_ptr<Logger> sLog = make_shared<InfoLogger>(make_shared<ErrorLogger>(make_shared<DebugLogger>(nullptr)));

    sLog->log("INFO");
    sLog->log("DEBUG");
    sLog->log("ERROR");
    sLog->log("level1");

    return 0;
}