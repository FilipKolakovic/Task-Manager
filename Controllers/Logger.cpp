#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>

std::mutex Logger::mLogAcessMutex;

std::string Logger::fileName = "LoggerOutputCommon.txt";

Logger::Logger(const std::string& data)
	: buffer{ data }
{
}

void Logger::doAction()
{
	logger(buffer);
}

std::string Logger::getCurrentDateAndTime() const
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream datetime;
	datetime << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return datetime.str();
}

void Logger::logger(const std::string text)
{
	const auto currentTime = getCurrentDateAndTime();
	std::stringstream ss;
	ss << currentTime << '\t' << text << '\n';
	{
		std::lock_guard<std::mutex> lock(mLogAcessMutex); // Mutext is necessary because multiple tasks log in same .txt file.
		std::ofstream ofs(Logger::fileName.c_str(), std::ios_base::out | std::ios_base::app);
		ofs << ss.str();
		ofs.close();
	}
}
