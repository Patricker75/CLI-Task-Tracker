#include "Utility.h"

std::string ListToString(Node<Task>* node) {
    std::string output = "";

    while (node != nullptr) {
        output += node->data.name;

        if (node->data.notes != "") {
            output += " --- " + node->data.notes;
        }

        output += "\n";

        node = node->next;
    }

    return output;
}

std::string InOrderTreeTraverse(TNode* node) {
    if (node == nullptr) {
        return "";
    }

    std::string output = InOrderTreeTraverse(node->left);
    output += std::to_string(node->key) + "\n";
    output += ListToString(node->tasks->GetHead());
    output += InOrderTreeTraverse(node->right);
    
    return output;
}

int DateParser(std::string date) {
    int day = stoi(date.substr(0, date.find("/")));
    date = date.substr(date.find("/") + 1);

    int month = stoi(date.substr(0, date.find("/")));
    date = date.substr(date.find("/") + 1);

    int year = stoi(date);

    return year * 10000 + month * 100 + day;
}

std::string PrintTags(Task t) {
    Node<std::string>* current = t.tags->GetHead();

    std::string output = "";
    while (current != nullptr) {
        output += current->data + "\n";
        
        current = current->next;
    }

    return output;
}

std::string PrintTasks(TagNode* node) {
    if (node == nullptr) {
        return "";
    }

    std::string output = PrintTasks(node->left);

    output += std::to_string(node->key) + "\n";
    
    Node<Task*>* current = node->tasks->GetHead();
    while (current != nullptr) {
        output += current->data->name + "\n";

        current = current->next;
    }

    output += PrintTasks(node->right);

    return output;
}
