#pragma once

#include "IController.h"
#include <string>
#include <mutex>

// Controller Logger - logging data in the common log file

class Logger : public IController
{
public:
	Logger() = delete;
	Logger(const std::string& data);
	~Logger() override = default;

	void doAction() override;

private:
	std::string getCurrentDateAndTime() const;
	void logger(const std::string text);
private:
	std::string buffer;

	static std::mutex mLogAcessMutex;
	static std::string fileName;
};

