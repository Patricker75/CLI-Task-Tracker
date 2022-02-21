#include <iostream>

#include "TaskTree.h"

using namespace std;

static TaskTree* taskTree = new TaskTree();

void PrintMenu() {
    cout << "Choose an Option:" << endl; // TODO add selection text
    cout << "0 - display all stored tasks" << endl;
    cout << "1 - add new task" << endl;
    cout << "2 - edit stored task" << endl;
    cout << "3 - delete stored task" << endl;
}

void AddScreen() {
    string name;
    string notes;
    string date;
    int day;
    int month;
    int year;

    cout << "Name of Task: ";
    getline(cin, name);

    cout << "Notes: ";
    getline(cin, notes);

    cout << "Due Date (mm/dd/yyyy): ";
    getline(cin, date);

    month = stoi(date.substr(0, 2));
    date = date.replace(0, 3, "");

    day = stoi(date.substr(0, 2));
    date = date.replace(0, 3, "");

    year = stoi(date);

    int codedDate = (year * 10000) + (month * 100) + day;

    Task newTask(name, notes);
    taskTree->Insert(codedDate, newTask);
}

LinkedList<Task>* GetTargetDate() {
    string date;

    cout << "Date of Task to Edit (mm/dd/yyyy): ";
    getline(cin, date);

    int month = stoi(date.substr(0, 2));
    date = date.replace(0, 3, "");

    int day = stoi(date.substr(0, 2));
    date = date.replace(0, 3, "");

    int year = stoi(date);

    int codedDate = (year * 10000) + (month * 100) + day;

    TaskNode* targetNode = taskTree->Search(codedDate);
    
    if (targetNode == nullptr) {
        return nullptr;
    }
    return targetNode->tasks;
}

Task& GetTargetTask(LinkedList<Task>* list) {
    int count = 0;
    
    Node<Task>* current = list->GetHead();
    while (current != nullptr) {
        cout << count << " - " << current->data.name << endl;

        current = current->next;
        count++;
    }
    cout << "Choose Task You Want to Edit: ";
    
    string _;
    getline(cin, _);
    int choice = stoi(_);

    current = list->GetHead();

    for (int i = 0; i < choice; i++) {
        current = current->next;
    }

    return current->data;
}

void EditScreen() {
    LinkedList<Task>* targetList = GetTargetDate();
    if (targetList == nullptr) {
        cout << "No tasks exist for given date";
    }

    Task target = GetTargetTask(targetList);
}

void MenuScreen() {
    PrintMenu();
    int option;
    cin >> option;

    switch (option) {
        case 0:
            break;
        case 1:
         break;
        case 2:
            break;
        case 3:
            break;
        default:
            return;
        break;
    }
}

void Run() {
    // AddScreen();
    // MenuScreen();
}

int main(int argc, char* argv []) {
    taskTree->Insert(20220221, Task("test 1"));
    taskTree->Insert(20220221, Task("test 2"));
    taskTree->Insert(20220222, Task("test 3"));
    
    EditScreen();

    return 0;
}