//using un ordermap & priority queue
//main

#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Task {
    string description;
    string name;
    string deadline;
    int priority;
};

struct TaskComparator {
    bool operator()(const Task& t1, const Task& t2) const {
        if (t1.deadline == t2.deadline) {
            return t1.priority < t2.priority;
        }
        return t1.deadline > t2.deadline;
    }
};

priority_queue<Task, vector<Task>, TaskComparator> taskQueue;
unordered_map<string, Task> taskMap;

void addTask() {
    cout << "Enter task details:" << endl;
    Task task;
    cin.ignore();
    cout << "Name: ";
    getline(cin, task.name);
    cout << "Description: ";
    getline(cin, task.description);
    cout << "Deadline: ";
    getline(cin, task.deadline);
    cout << "Priority: ";
    cin >> task.priority;

    taskQueue.push(task);
    taskMap[task.name] = task;
    cout << "Task added successfully!" << endl;
}

void viewTasks() {
    if (taskQueue.empty()) {
        cout << "No tasks found." << endl;
    } else {
        cout << "Tasks:" << endl;
        priority_queue<Task, vector<Task>, TaskComparator> tempQueue = taskQueue;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            cout << "Name: " << task.name << endl;
            cout << "Description: " << task.description << endl;
            cout << "Deadline: " << task.deadline << endl;
            cout << "Priority: " << task.priority << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}

void completeTask() {
    string taskName;
    cout << "Enter the name of the task you want to mark as completed: ";
    cin.ignore();
    getline(cin, taskName);

    if (taskMap.find(taskName) != taskMap.end()) {
        taskMap.erase(taskName);
        cout << "Task '" << taskName << "' marked as completed." << endl;
    } else {
        cout << "Task '" << taskName << "' not found." << endl;
    }

    // Remove completed task from the priority queue
    priority_queue<Task, vector<Task>, TaskComparator> tempQueue;
    while (!taskQueue.empty()) {
        Task task = taskQueue.top();
        taskQueue.pop();
        if (task.name != taskName) {
            tempQueue.push(task);
        }
    }
    taskQueue = tempQueue;
}

void deleteTask() {
    string taskName;
    cout << "Enter the name of the task you want to delete: ";
    cin.ignore();
    getline(cin, taskName);

    if (taskMap.find(taskName) != taskMap.end()) {
        taskMap.erase(taskName);
        cout << "Task '" << taskName << "' deleted successfully." << endl;
    } else {
        cout << "Task '" << taskName << "' not found." << endl;
    }

    // Remove task from the priority queue
    priority_queue<Task, vector<Task>, TaskComparator> tempQueue;
    while (!taskQueue.empty()) {
        Task task = taskQueue.top();
        taskQueue.pop();
        if (task.name != taskName) {
            tempQueue.push(task);
        }
    }
    taskQueue = tempQueue;
}

void searchTask() {
    string taskName;
    cout << "Enter the name of the task you want to search: ";
    cin.ignore();
    getline(cin, taskName);

    if (taskMap.find(taskName) != taskMap.end()) {
        Task task = taskMap[taskName];
        cout << "Task Found:" << endl;
        cout << "Name: " << task.name << endl;
        cout << "Description: " << task.description << endl;
        cout << "Deadline: " << task.deadline << endl;
        cout << "Priority: " << task.priority << endl;
    } else {
        cout << "Task '" << taskName << "' not found." << endl;
    }
}


void updateTask() {
    string taskName;
    cout << "Enter the name of the task you want to update: ";
    cin.ignore();
    getline(cin, taskName);

    if (taskMap.find(taskName) != taskMap.end()) {
        Task& task = taskMap[taskName];
        bool validChoice = false;

        while (!validChoice) {
            cout << "Enter the field you want to update:" << endl;
            cout << "1. Priority" << endl;
            cout << "2. Description" << endl;
            cout << "3. Deadline" << endl;
            cout << "4. Priority and Description" << endl;
            cout << "5. Priority and Deadline" << endl;
            cout << "6. Description and Deadline" << endl;
            cout << "7. Priority, Description, and Deadline" << endl;

            int choice;
            cout << "Enter your choice (1-7): ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "New Priority: ";
                    cin >> task.priority;
                    validChoice = true;
                    break;
                }
                case 2: {
                    cout << "New Description: ";
                    cin.ignore();
                    getline(cin, task.description);
                    validChoice = true;
                    break;
                }
                case 3: {
                    cout << "New Deadline: ";
                    cin.ignore();
                    getline(cin, task.deadline);
                    validChoice = true;
                    break;
                }
                case 4: {
                    cout << "New Priority: ";
                    cin >> task.priority;
                    cout << "New Description: ";
                    cin.ignore();
                    getline(cin, task.description);
                    validChoice = true;
                    break;
                }
                case 5: {
                    cout << "New Priority: ";
                    cin >> task.priority;
                    cout << "New Deadline: ";
                    cin.ignore();
                    getline(cin, task.deadline);
                    validChoice = true;
                    break;
                }
                case 6: {
                    cout << "New Description: ";
                    cin.ignore();
                    getline(cin, task.description);
                    cout << "New Deadline: ";
                    getline(cin, task.deadline);
                    validChoice = true;
                    break;
                }
                case 7: {
                    cout << "New Priority: ";
                    cin >> task.priority;
                    cout << "New Description: ";
                    cin.ignore();
                    getline(cin, task.description);
                    cout << "New Deadline: ";
                    getline(cin, task.deadline);
                    validChoice = true;
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }

        cout << "Task '" << taskName << "' updated successfully." << endl;

        // Update task in the priority queue
        priority_queue<Task, vector<Task>, TaskComparator> tempQueue;
        while (!taskQueue.empty()) {
            Task oldTask = taskQueue.top();
            taskQueue.pop();
            if (oldTask.name != taskName) {
                tempQueue.push(oldTask);
            }
        }
        tempQueue.push(taskMap[taskName]);
        taskQueue = tempQueue;
    } else {
        cout << "Task " << taskName << " not found" << endl;
    }
}




void scheduleTasks() {
    if (taskQueue.empty()) {
        cout << "No tasks found." << endl;
    } else {
        cout << "Scheduled Tasks:" << endl;
        priority_queue<Task, vector<Task>, TaskComparator> tempQueue = taskQueue;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            cout << "Name: " << task.name << endl;
            cout << "Description: " << task.description << endl;
            cout << "Deadline: " << task.deadline << endl;
            cout << "Priority: " << task.priority << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}

int main() {
    while (true) {
        cout << "\nTask Scheduler Menu:" << endl;
        cout << "1. Add a task" << endl;
        cout << "2. View tasks" << endl;
        cout << "3. Complete a task" << endl;
        cout << "4. Delete a task" << endl;
        cout << "5. Search a task" << endl;
        cout << "6. Update task" << endl;
        cout << "7. Schedule tasks" << endl;
        cout << "8. Exit" << endl;

        int choice;
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                completeTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                searchTask();
                break;
            case 6:
                updateTask();
                break;
            case 7:
                scheduleTasks();
                break;
            case 8:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
