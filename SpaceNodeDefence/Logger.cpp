#include "Logger.h"
#include <ios>
#include <fstream>
#include <iomanip>
#include <ctime>

void Logger::log(LogLevel level, const std::string& msg)
{
	std::lock_guard<std::mutex> lock(mtx_);
	auto now = std::chrono::system_clock::now();
	LogEntry currentLogData{
		.timestamp = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()),
		.logLevel = level,
		.msg = msg,
		.id_thread = std::this_thread::get_id()
	};
	events_.emplace(currentLogData.timestamp, currentLogData);

}

void Logger::flush(const std::string& filename)
{
	std::lock_guard<std::mutex> lock(mtx_);
	std::ofstream file(filename, std::ios::app);
	if (file.is_open())
	{
		for (const auto& event : events_)
		{
			// 1. Разбиваем таймстемп на секунды и миллисекунды
			std::time_t time_sec = event.first / 1000;
			uint64_t ms = event.first % 1000;

			// 2. Конвертируем в локальное время (localtime_s безопасен для твоего компилятора MSVC)
			std::tm tm_info;
			localtime_s(&tm_info, &time_sec);

			// 3. Форматируем строку вывода
			file << '[' << std::put_time(&tm_info, "%H:%M:%S") << '.'
				<< std::setfill('0') << std::setw(3) << ms << "] ["
				<< event.second.id_thread << "] ["
				<< static_cast<int>(event.second.logLevel) << "] "
				<< event.second.msg << '\n';
		}
		events_.clear(); // Очищаем контейнер после записи на диск
	}
}
