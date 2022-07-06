#pragma once

#include "IController.h"

#include <memory>
#include <string>

enum class TaskType
{
	PrintToConsole,
	WriteInCommonLog,
	WriteInSepareteFile
};

using IControllerPtr = std::shared_ptr<IController>;

class Task
{
public:
	Task(const TaskType &type, const std::string& data, const std::string& taskName = "defaultName");

	IControllerPtr getController() const;
	std::string getTaskName() const;
	TaskType getTaskType() const;
	std::string getTaskData() const;
private:
	IControllerPtr createController(const TaskType& type, const std::string& data);
private:
	TaskType mType;
	std::string mData;
	std::string mTaskName;
	IControllerPtr mController;
};

