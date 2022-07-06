#include "TaskManager.h"

#include <chrono>
#include <future>
#include <iostream>
#include <thread>


int main()
{
    using namespace std::chrono_literals;


    /// Following 4 lambdas (for each type of controller and one for group execution) are tasks that are going to be executed when the initial task is completed
    auto endPrintFunc = [](std::string s)
    {
        std::cout << "Successfully printed : " + s + "\n";
    };

    auto endLogFunc = [](std::string s)
    {
        std::cout << "Successfully logged : " + s + "\n";
    };

    auto endFileCreationFunc = [](std::string s)
    {
        std::cout << "Successfully created file : " + s + "\n";
    };

    auto endGroupFunc = []()
    {
        std::cout << "Successfully executed task group!\n";
    };
    
    std::shared_ptr<TaskManager> taskManager = std::make_shared<TaskManager>("Task Manager");

    for (int i = 1; i <= 10; i++)
    {
        taskManager->createAndRunTask(TaskType::PrintToConsole, "Print " + std::to_string(i) + "\n", "PrintTask_" + std::to_string(i), endPrintFunc);
    }

    for (int i = 1; i <= 10; i++)
    {
        taskManager->createAndRunTask(TaskType::WriteInCommonLog, "Logging_" + std::to_string(i), "LogTask_" + std::to_string(i), endLogFunc);
    }

    for (int i = 1; i <= 3; i++)
    {
        taskManager->createAndRunTask(TaskType::WriteInSepareteFile, "Writting " + std::to_string(i), "FileTask_" + std::to_string(i), endFileCreationFunc);
    }

    taskManager->createTaskAndStoreInGroup(TaskType::PrintToConsole, "Group_Task_Print_1\n", "GroupTask1");
    taskManager->createTaskAndStoreInGroup(TaskType::PrintToConsole, "Group_Task_Print_2\n", "GroupTask2");
    taskManager->createTaskAndStoreInGroup(TaskType::PrintToConsole, "Group_Task_Print_3\n", "GroupTask3");
    taskManager->createTaskAndStoreInGroup(TaskType::PrintToConsole, "Group_Task_Print_4\n", "GroupTask4");
    taskManager->createTaskAndStoreInGroup(TaskType::PrintToConsole, "Group_Task_Print_5\n", "GroupTask5");
    taskManager->createTaskAndStoreInGroup(TaskType::PrintToConsole, "Group_Task_Print_6\n", "GroupTask6");

    taskManager->createTaskAndStoreInGroup(TaskType::WriteInCommonLog, "Group_Task_Log_1", "GroupTask7");
    taskManager->createTaskAndStoreInGroup(TaskType::WriteInCommonLog, "Group_Task_Log_2", "GroupTask8");

    taskManager->createTaskAndStoreInGroup(TaskType::WriteInSepareteFile, "Group_Task_File_1\n", "GroupTask10");
    taskManager->createTaskAndStoreInGroup(TaskType::WriteInSepareteFile, "Group_Task_File_2\n", "GroupTask11");
    
    taskManager->executeTasksFromGroup(endGroupFunc);    
}