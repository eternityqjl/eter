#include "log.h"

namespace eter {

Logger::Logger(const std::string& name) : m_name(name) {
    
}

void Logger::addAppender(LogAppender::ptr appender) {

}

void Logger::delAppender(LogAppender::ptr appender) {

}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        for (auto& i : m_appenders) {

        }
    }
}

void Logger::debug(LogEvent::ptr event) {
    debug(LogLevel::DEBUG, event);
}
void Logger::info(LogEvent::ptr event) {

}
void Logger::warn(LogEvent::ptr event) {

}
void Logger::error(LogEvent::ptr event) {

}
void Logger::fatal(LogEvent::ptr event) {

}

FileLogAppender::FileLogAppender

bool FileLogAppender::reopen() {

}

}