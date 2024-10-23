#ifndef TASK_INFO_H
#define TASK_INFO_H

#include <map>
#include <string>

class TaskInfo {
public:
    TaskInfo() {
        taskMap["WiFi Connection Task"] = {0, 6};
        taskMap["OTA Updater Task"] = {0, 5};
        taskMap["Activity Sense Task"] = {0, 4};
        taskMap["Log Server Task"] = {0, 3};
        taskMap["Send Post Task"] = {0, 2};
        taskMap["Notify Run Task"] = {0, 2};
        taskMap["Heartbeat Task"] = {0, 1};
    }

    int getCore(const std::string& taskName) {
        auto it = taskMap.find(taskName);
        if (it != taskMap.end()) {
            return it->second.core;
        } else {
            return -1;
        }
    }

    int getPriority(const std::string& taskName) {
        auto it = taskMap.find(taskName);
        if (it != taskMap.end()) {
            return it->second.priority;
        } else {
            return -1;
        }
    }
    
private:
    struct TaskInfoRecord {
        int core;
        int priority;
    };

    std::map<std::string, TaskInfoRecord> taskMap;
};

#endif
