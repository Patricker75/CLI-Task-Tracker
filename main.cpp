#include <iostream>

#include "TaskTree.h"

using namespace std;

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

    // cout << "Name of Task: ";
    // getline(cin, name);

    // cout << "Notes: ";
    // getline(cin, notes);

    cout << "Due Date (mm/dd/yyyy): ";
    getline(cin, date);

    month = stoi(date.substr(0, 2));
    date = date.replace(0, 3, "");

    day = stoi(date.substr(0, 2));
    date = date.replace(0, 3, "");

    year = stoi(date);
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
    TaskTree* tree = new TaskTree();

    Task t1("Test");
    Task t2("Test 2", "This is a note");
    Task t3("Test 3", "This is another note");

    tree->Insert(1, t1);
    tree->Insert(2, t2);
    tree->Insert(3, t3);

    LinkedList<Task>* task = tree->Search(1)->tasks;
    cout << task->GetHead() << endl;

    return 0;
}