#include <iostream>
#include <fstream>

#include "TaskTree.h"
#include "TagsList.h"

#include "Utility.h"
#include "DataIO.h"

#include "TestControl.h"

using namespace std;

static TaskTree* tree = new TaskTree();
static TagsList* tags = new TagsList();

void PrintMenu() {
    cout << "Choose an Option:" << endl; // TODO add selection text
    cout << "0 - display all stored tasks" << endl;
    cout << "1 - add new task" << endl;
    cout << "2 - edit stored task" << endl;
    cout << "3 - delete stored task" << endl;
    cout << "4 - search tasks with tag" << endl;

    cout << "-1 - exit" << endl;
}

void AddScreen() {
    cout << "Task Name: ";
    string name;
    getline(cin, name);

    cout << "Due Date (dd/mm/yyyy): ";
    string date;
    getline(cin, date);

    int dueDate = DateParser(date);

    cout << "Notes about Task: ";
    string notes;
    getline(cin, notes);

    Task task(name, dueDate);

    if (notes != "") {
        task.notes = notes;
    }

    Task* ptr = tree->Insert(task.dueDate, task);

    cout << "Task's Tags" << endl;
    string tag;
    getline(cin, tag);
    while (tag != "") {
        task.tags->Insert(tag);

        tags->Insert(tag, ptr);

        getline(cin, tag);
    }

    
}

void EditScreen() {
    if (tree->Empty()) {
        cout << "No Tasks" << endl;
        return;
    }

    cout << "Date of Task to Edit (dd/mm/yyyy): " << endl;
    string choice;
    getline(cin, choice);

    int dueDate = DateParser(choice);
    
    LinkedList<Task>* tasks = tree->Search(dueDate)->tasks;
    if (tasks == nullptr) {
        cout << "Task with given due date does not exist" << endl;
        return;
    }

    int listLength = tasks->GetLength();
    Task* ptrs[listLength]; 
    Node<Task>* current = tasks->GetHead();
    for (int i = 0; i < listLength; i++) {
        ptrs[i] = &current->data;
        current = current->next;

        cout << to_string(i + 1) << " - " << ptrs[i]->name << endl;
    }

    getline(cin, choice);
    int index = stoi(choice) - 1;

    Task* targetTask = ptrs[index];

    cout << "What to Edit: " << endl;
    cout << "1 - Name" << endl;
    cout << "2 - Due Date" << endl;
    cout << "3 - Notes" << endl;
    cout << "4 - Add Tags" << endl;
    cout << "5 - Remove Tags" << endl;
    cout << "0 - Exit" << endl;
    getline(cin, choice);
    int option = stoi(choice);

    while (option != 0) {
        switch (option)
        {
        case 1:
            cout << "New Task Name: " << endl;
            getline(cin, choice);
            
            targetTask->name = choice;
            break;
        case 2:
            cout << "New Due Date (dd/mm/yyyy): " << endl;
            getline(cin, choice);

            targetTask->dueDate = DateParser(choice);
            break;
        case 3:
            cout << "New Notes: " << endl;
            getline(cin, choice);

            targetTask->notes = choice;
            break;
        case 4:
            cout << "New Tag(s): " << endl;
            getline(cin, choice);

            while (choice != "") {
                targetTask->tags->Insert(choice);
                tags->Insert(choice, targetTask);

                getline(cin, choice);
            }
            break;
        case 5:
            if (targetTask->tags->Empty()) {
                cout << "Task has no Tags" << endl;
                break;
            }
            cout << "Delete Tag(s): " << endl;
            cout << PrintTags(*targetTask) << endl;

            getline(cin, choice);
            while (choice != "" && !targetTask->tags->Empty()) {
                targetTask->tags->Delete(choice);
                tags->Remove(choice, targetTask);

                getline(cin, choice);
            }
            break;
        }

        cout << "What to Edit: " << endl;
        getline(cin, choice);
        
        if (choice == "") {
            break;
        }

        option = stoi(choice);
    }

    if (targetTask->dueDate != dueDate) {
        tasks->Delete(*targetTask);
        if (tasks->Empty()) {
            tree->Delete(dueDate);
        }

        tree->Insert(*targetTask);
    }
}

void DeleteScreen() {
    if (tree->Empty()) {
        cout << "No Tasks" << endl;
        return;
    }

    cout << "Date of Task to Delete (dd/mm/yyyy): " << endl;
    string choice;
    getline(cin, choice);

    int dueDate = DateParser(choice);
    
    LinkedList<Task>* tasks = tree->Search(dueDate)->tasks;
    if (tasks == nullptr) {
        cout << "Task with given due date does not exist" << endl;
        return;
    }

    int listLength = tasks->GetLength();
    Task* ptrs[listLength]; 
    Node<Task>* current = tasks->GetHead();
    for (int i = 0; i < listLength; i++) {
        ptrs[i] = &current->data;
        current = current->next;

        cout << to_string(i + 1) << " - " << ptrs[i]->name << endl;
    }

    getline(cin, choice);
    int index = stoi(choice) - 1;
    
    Task* targetTask = ptrs[index];

    tasks->Delete(*targetTask);

    if (tasks->Empty()) {
        tree->Delete(dueDate);
    }
}

void DisplayTagScreen() {
    if (tags->Empty()) {
        cout << "No Tags Added" << endl;

        return;
    }
    cout << "List of Tags:" << endl;
    
    TagPair* current = tags->GetHead();
    while (current != nullptr) {
        cout << current->tag << endl;

        current = current->next;
    }
    free(current);

    string choice;
    cout << endl;
    cout << "Tag to Search: " << endl;
    getline(cin, choice);

    TagPair* target = tags->Search(choice);

    if (target == nullptr) {
        cout << "No task with tag exists" << endl;
        
        return;
    }

    cout << PrintTasks(target->tree->GetRoot()) << endl;
}

void DisplayScreen() {
    if (tree->Empty()) {
        cout << "No Tasks" << endl;
    }
    else {
        cout << InOrderTreeTraverse(tree->GetRoot()) << endl;
    }
}

void MenuScreen(std::string fileName) {
    bool loop = true;

    while (loop) {
        PrintMenu();
        string temp;
        int option = 0;

        getline(cin, temp);
        option = stoi(temp);        

        switch (option) {
            case -1:
                loop = false;
                break;
            case 0:
                DisplayScreen();
                break;
            case 1:
                AddScreen();
                break;
            case 2:
                EditScreen();
                break;
            case 3:
                DeleteScreen();
                break;
            case 4:
                DisplayTagScreen();
                break;
            default:
                cout << "Invalid Input" << endl;
            break;
        }

        cout << endl;

        // SaveData(tree, fileName);
    }
}

void Run(std::string fileName) {
    MenuScreen(fileName);
}

int main(int argc, char* argv []) {
    string fileName = "data.json";

    tree = LoadData(fileName, tags);
    
    Run(fileName);

    // SaveData(tree, fileName);

    return 0;
}