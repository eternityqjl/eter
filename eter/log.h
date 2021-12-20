#ifndef __LOG_H__
#define __LOG_H__
#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <iostream>
#include <fstream>

namespace eter {

//日志事件
class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
private:
    const char* m_file = nullptr;   //文件名
    int32_t m_line = 0;             //行号
    uint32_t m_elapse = 0;          //程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;        //线程id
    uint32_t m_fiberId = 0;         //携程id
    uint64_t m_time;                //时间戳
    std::string m_content;
};

//日志级别
class LogLevel {
public:
    enum Level{
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4, 
        FATAL = 5
    };
};

//日志器
class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);

private:
    std::string m_name;                         //日志名称
    LogLevel::Level m_level;                    //日志级别
    std::list<LogAppender::ptr> m_appenders;    //Appender集合

};


//日志格式化
class LogFormatter
{
private:
    /* data */
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    std::string format(LogEvent::ptr event);

    LogFormatter(const std::string& pattern);
    ~LogFormatter() {};

private:
    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem();

    };

private:
};



//日志输出目标
class LogAppender
{
public:

    typedef std::shared_ptr<LogAppender> ptr;
    LogAppender(/* args */) {};
    virtual ~LogAppender() {};

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level, LogEvent::ptr event) = 0;

    //更改日志格式器
    void setFormatter (LogFormatter::ptr val);
protected:
    LogLevel::Level m_level = LogLevel::DEBUG;

};

//输出到控制台的Appender
class StdoutLogAppender : public LogAppender
{
private:
    /* data */
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent event);
    StdoutLogAppender(/* args */);
    ~StdoutLogAppender();
};

//输出到文件的Appender
class FileLogAppender : public LogAppender
{

public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);

    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
    
    //重新打开文件，打开成功返回true
    bool reopen();

private:
    std::string m_filename;
    std::ofstream m_filestream;
    uint64_t m_lastTime = 0;

};





} //namespace eter








#endif