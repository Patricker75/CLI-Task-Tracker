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

std::string GetTagAsString(TagNode* node) {
    if (node == nullptr) {
        return "";
    }

    std::string output = GetTagAsString(node->left);

    output += std::to_string(node->key) + "\n";
    
    Node<Task*>* current = node->tasks->GetHead();
    while (current != nullptr) {
        output += current->data->name + "\n";

        current = current->next;
    }

    output += GetTagAsString(node->right);

    return output;
}
