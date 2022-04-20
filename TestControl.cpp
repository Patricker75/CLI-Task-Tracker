#include "TestControl.h"

void ParseInput(const std::string filePath, TaskTree* tree) {
    std::ifstream file(filePath);

    std::string line;
    std::string name;
    std::string date;
    while(getline(file, line)) {
        name = line.substr(0, line.find(","));
        date = line.substr(line.find(",") + 2);

        int day = stoi(date.substr(0, date.find("/")));
        date = date.substr(date.find("/") + 1);

        int month = stoi(date.substr(0, date.find("/")));
        date = date.substr(date.find("/") + 1);

        int year = stoi(date);

        Task task(name, year, month, day);
        tree->Insert(task.dueDate, task);
    }
}
