#include<bits/stdc++.h>
using namespace std;

struct Task {
    string name;
    tm due_date;
    int priority;

    bool operator<(const Task& other) const {
        if (priority == other.priority) {
            return difftime(mktime(const_cast<tm*>(&due_date)), mktime(const_cast<tm*>(&other.due_date))) > 0;
        }
        return priority > other.priority;
    }
};

class TodoList {
private:
    priority_queue<Task> tasks;

public:
    void addTask(string name, string due_date_str, int priority) {
        tm due_date = {};
        stringstream ss(due_date_str);
        ss >> get_time(&due_date, "%Y-%m-%d");

        Task new_task = {name, due_date, priority};
        tasks.push(new_task);

        cout << "Task '" << name << "' added with priority " << priority
             << " and due date " << due_date_str << "." << endl;
    }

    void removeTask(string task_name) {
        vector<Task> temp_tasks;
        while (!tasks.empty()) {
            Task t = tasks.top();
            tasks.pop();
            if (t.name != task_name) {
                temp_tasks.push_back(t);
            }
        }

        for (const Task& t : temp_tasks) {
            tasks.push(t);
        }

        cout << "Task '" << task_name << "' has been removed." << endl;
    }

    void markDone(string task_name) {
        removeTask(task_name);
        cout << "Task '" << task_name << "' marked as done." << endl;
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
            return;
        }

        cout << "\nTasks:\n";
        vector<Task> temp_tasks;
        while (!tasks.empty()) {
            Task t = tasks.top();
            tasks.pop();
            temp_tasks.push_back(t);
        }

        for (const Task& task : temp_tasks) {
            cout << task.name << " - Priority: " << task.priority
                 << " - Due: " << formatDate(task.due_date) << endl;
            tasks.push(task);
        }
    }

    void sortByDueDate() {
        vector<Task> all_tasks;
        while (!tasks.empty()) {
            all_tasks.push_back(tasks.top());
            tasks.pop();
        }

        sort(all_tasks.begin(), all_tasks.end(), [](const Task& a, const Task& b) {
            return difftime(mktime(const_cast<tm*>(&a.due_date)), mktime(const_cast<tm*>(&b.due_date))) < 0;
        });

        cout << "Tasks sorted by due date.\n";
        for (const Task& task : all_tasks) {
            cout << task.name << " - Priority: " << task.priority
                 << " - Due: " << formatDate(task.due_date) << endl;
        }

        for (const Task& task : all_tasks) {
            tasks.push(task);
        }
    }

private:
    string formatDate(tm date) {
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        return string(buffer);
    }
};

int main() {
    TodoList todoList;

    todoList.addTask("Complete C++ Project", "2024-12-01", 1);
    todoList.addTask("Buy groceries", "2024-11-20", 3);
    todoList.addTask("Schedule dentist appointment", "2024-11-18", 2);

    todoList.viewTasks();

    todoList.sortByDueDate();

    todoList.markDone("Buy groceries");

    todoList.viewTasks();

    todoList.removeTask("Schedule dentist appointment");

    todoList.viewTasks();

    return 0;
}
