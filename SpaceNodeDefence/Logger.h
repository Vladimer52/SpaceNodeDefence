#pragma once
#include <chrono>
#include <string>
#include <thread>
#include <mutex>
#include <map>
enum class LogLevel {
	INFO, 
	WARNING, 
	ERROR,
	DEBUG
};

struct LogEntry {
	uint64_t timestamp;
	LogLevel logLevel;
	std::string msg;
	std::thread::id id_thread;
};

class Logger {
private: 
	std::multimap<uint64_t, LogEntry> events_;
	std::mutex mtx_;
public:
	void log(LogLevel level, const std::string& msg);
	void flush(const std::string& filename);

	void log_i(const std::string& msg) { log(LogLevel::INFO, msg); }
	void log_w(const std::string& msg) { log(LogLevel::WARNING, msg); }
	void log_e(const std::string& msg) { log(LogLevel::ERROR, msg); }
	void log_d(const std::string& msg) { log(LogLevel::DEBUG, msg); }
};