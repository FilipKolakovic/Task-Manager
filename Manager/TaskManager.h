#pragma once
#include "Task.h"

#include <ppl.h>
#include <ppltasks.h>

using ContinuationTask = std::function<void(std::string)>;
using TaskResult = concurrency::task<void>;
using ContinuationTaskForGroup = std::function<void()>;

class TaskManager
{
public:
	TaskManager(const std::string& name="TaskManager");
	
	TaskResult createAndRunTask(const TaskType& taskType, const std::string& dataToProcess, const std::string& taskName = std::string(), ContinuationTask continuationTask = nullptr);
	void createTaskAndStoreInGroup(const TaskType& taskType, const std::string& dataToProcess, const std::string& taskName = std::string());
	void executeTasksFromGroup(ContinuationTaskForGroup groupContinuationTask = nullptr);
private:
	std::string mName;
	std::vector<Task> mTasks;
	std::vector<TaskResult> groupOfReadyTasks;
};

