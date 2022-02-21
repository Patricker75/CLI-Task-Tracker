#include <iostream>
#include <fstream>

#include "Stack.h"
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

    Task newTask(name, codedDate, notes);
    taskTree->Insert(newTask);
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

Task* GetTargetTask(LinkedList<Task>* list) {
    int count = 0;
    
    Node<Task>* current = list->GetHead();
    while (current != nullptr) {
        cout << count << " - " << current->data.name << endl;

        current = current->next;
        count++;
    }
    cout << "-1 - Exit" << endl;
    cout << "Choose Task You Want to Edit: ";
    
    string _;
    getline(cin, _);
    int choice = stoi(_);

    if (choice == -1) {
        return nullptr;
    }

    current = list->GetHead();

    for (int i = 0; i < choice; i++) {
        current = current->next;
    }

    return &current->data;
}

void EditTask(Task* task) {
    cout << "Choose a field to change:" << endl;
    cout << "0 - Change Name" << endl;
    cout << "1 - Change Notes" << endl;
    cout << "2 - Change Due Date" << endl;
    cout << "-1 - Quit" << endl;

    int choice;
    cin >> choice;

    string discard;
    getline(cin, discard);

    string newData;
    if (choice == 0) {
        cout << "New Task Name: ";
        getline(cin, newData);

        task->name = newData;
    }
    else if (choice == 1) {
        cout << "New Notes: ";
        getline(cin, newData);

        task->notes = newData;
    }
    else if (choice == 2) {
        cout << "New Due Date (mm/dd/yyyy): ";
        getline(cin, newData);

        int month = stoi(newData.substr(0, 2));
        newData = newData.replace(0, 3, "");

        int day = stoi(newData.substr(0, 2));
        newData = newData.replace(0, 3, "");

        int year = stoi(newData);

        int codedDate = (year * 10000) + (month * 100) + day;

        task->dueDate = codedDate;
    }
}

void EditScreen() {
    LinkedList<Task>* targetList = GetTargetDate();
    int listDate = targetList->GetHead()->data.dueDate;

    if (targetList == nullptr) {
        cout << "No tasks exist for given date";
    }

    Task* target = GetTargetTask(targetList);
    EditTask(target);

    if (target->dueDate != listDate) {
        targetList->Remove(*target);
    }
    
    Node<Task>* curr = targetList->GetHead();
    while (curr != nullptr) {
        cout << curr->data.name << endl;
        curr = curr->next;
    }
}

void DeleteScreen() {
    LinkedList<Task>* targetList = GetTargetDate();
    Task* target = GetTargetTask(targetList);

    targetList->Remove(*target);
}

void DisplayScreen() {
    cout << taskTree->GetAllTasks();
    // TaskNode* current = taskTree->GetRoot();
    // Stack<TaskNode*>* stack = new Stack<TaskNode*>();

    // while (current != nullptr || !stack->Empty()) {
    //     stack->Push(current);
    //     current = static_cast<TaskNode*>(current->left);
    // }
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

void SaveTree() {
    ofstream file("./task_data.txt");

    TaskNode* node = taskTree->GetRoot();
    Stack<TaskNode*>* stack = new Stack<TaskNode*>();
    stack->Push(node);

    while(!stack->Empty()) {
        node = stack->Pop()->data;
        
        if (node->left != nullptr) {
            stack->Push(static_cast<TaskNode*>(node->left));
        }
        if (node->right != nullptr) {
            stack->Push(static_cast<TaskNode*>(node->right));
        }

        file << to_string(node->data) + " ";

        Node<Task>* task = node->tasks->GetHead();
        while (task != nullptr) {
            file << task->data.name + "&delim&";
            task = task->next;
        }

        file << "\n";
    }

    file.flush();
    file.close();
}

void Run() {
    // AddScreen();
    // MenuScreen();
}

int main(int argc, char* argv []) {
    // taskTree->Insert(Task("test 1", 20220221));
    // taskTree->Insert(Task("test 2", 20220221));
    // taskTree->Insert(Task("test 3", 20220221));
    // taskTree->Insert(Task("test 4", 20200531));
    // taskTree->Insert(Task("Test 19", 20230615));

    Task t1("Test 1 - Copy", 20220221);
    Task t2("Test 2", 20220221);
    Task t3("Test 3", 20220301);
    Task t4("Test 4", 20220304);
    Task t5("Test 5- Copy", 20220520);

    taskTree->Insert(t1);
    taskTree->Insert(t2);
    taskTree->Insert(t3);
    taskTree->Insert(t4);
    taskTree->Insert(t5);

    // LinkedList<Task*>* tagged = new LinkedList<Task*>();
    // tagged->Add(taskTree->SearchTask(t1));
    // tagged->Add(taskTree->SearchTask(t5));

    // tagged->GetHead()->data->name = "Overwritten";

    // DisplayScreen();
    // SaveTree();

    return 0;
}