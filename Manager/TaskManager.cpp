#include "TaskManager.h"
#include <iostream>

TaskManager::TaskManager(const std::string& name)
	: mName(name)
{
}

// Creates task and runs it
TaskResult TaskManager::createAndRunTask(const TaskType& taskType, const std::string& dataToProcess, const std::string& taskName, ContinuationTask continuationTask)   
{
	std::shared_ptr<Task> processTask = std::make_shared<Task>(taskType, dataToProcess, taskName);

	return concurrency::create_task([processTask]() {processTask->getController()->doAction(); })
        .then([taskName, continuationTask](const concurrency::task<void>& prevTask) {
        try
        {
            //prevTask.get();
            if(continuationTask)
            {
                continuationTask(taskName);
            }
        }

        catch (const std::exception& e)
        {
           std::cout<<"Exception thrown when executing task: " << taskName << ", " << e.what();
        }
        catch (...)
        {
            std::cout << "Unknown exception thrown when executing task: " << taskName;
        }
    });
}

// creates Task (but doesn't run it atm.) and places it in the vector of Tasks
void TaskManager::createTaskAndStoreInGroup(const TaskType& taskType, const std::string& dataToProcess, const std::string& taskName)
{
    mTasks.push_back(Task(taskType, dataToProcess, taskName));
}

// execute all Tasks in the vector and run Continuation task at the end
void TaskManager::executeTasksFromGroup(ContinuationTaskForGroup groupContinuationTask)
{
    for(auto t: mTasks)
    {
        groupOfReadyTasks.push_back(concurrency::create_task([t]() {
            Task task(t.getTaskType(), t.getTaskData(), t.getTaskName());
            task.getController()->doAction();
        }));
    }

    if (!groupOfReadyTasks.empty())
    {
        auto joinTask = concurrency::when_all(std::begin(groupOfReadyTasks), std::end(groupOfReadyTasks)).then([groupContinuationTask]() {groupContinuationTask(); });
        joinTask.wait();
    }
}

