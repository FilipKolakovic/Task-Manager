#include "Task.h"

#include "FileCreator.h"
#include "Logger.h"
#include "Printer.h"

Task::Task(const TaskType& type, const std::string& data, const std::string& taskName)
	: mType{ type }
	, mTaskName{ taskName }
	, mData{data}
{
	mController = createController(type, data);
}

IControllerPtr Task::getController() const
{
	return mController;
}

std::string Task::getTaskName() const
{
	return mTaskName;
}

TaskType Task::getTaskType() const
{
	return mType;
}

std::string Task::getTaskData() const
{
	return mData;
}

// Create Controller depending on type
IControllerPtr Task::createController(const TaskType& type, const std::string& data)
{
	switch (type)
	{
		case TaskType::PrintToConsole:
		{
			return std::make_shared<Printer>(data);
		}
		case TaskType::WriteInCommonLog:
		{
			return std::make_shared<Logger>(data);
		}
		case TaskType::WriteInSepareteFile:
		{
			return std::make_shared<FileCreator>(data, mTaskName);
		}
	}
}
