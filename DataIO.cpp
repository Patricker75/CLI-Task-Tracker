#include "DataIO.h"

TaskTree* LoadData (string filePath) {
    ifstream file(filePath);

    if (!file) {
        return new TaskTree();
    }

    string line;
    getline(file, line);
    getline(file, line);

    TaskTree* tree = new TaskTree();

    while (!file.eof()) {
        getline(file, line);

        if (line.find("{") != line.npos) {
            ParseTNode(file, tree);
        }
    }

    file.close();

    return tree;
}

void ParseTNode (ifstream& file, TaskTree* tree) {
    ofstream out("tempfile.txt");
    string line;

    getline(file, line);

    int dueDate = stoi(line.substr(line.find(": ") + 2, 8));
    
    while (!file.eof()) {
        getline(file, line);

        if (line.find("]") != line.npos) {
            break;
        }

        if (line.find("{") != line.npos) {
            Task t = ParseTask(file);
            t.dueDate = dueDate;

            tree->Insert(t);
        }
    }

}

Task ParseTask (ifstream& file) {
    Task t;

    string line;

    while (!file.eof()) {
        getline(file, line);

        if (line.find("}") != line.npos) {
            break;
        }

        int indexOfValue = line.find(": ") + 3;
        t.name = line.substr(indexOfValue, line.length() - indexOfValue - 1);
    }

    return t;
}

string Indenter(int tabCount) {
    string out = "";

    for (int i = 0; i < tabCount; i++) {
        out += "\t";
    }
    return out;
}


void SaveData (TaskTree* tree, string filePath) {
    

    ofstream file(filePath);

    int indentCount = 0;

    file << Indenter(indentCount) << "{" << endl;
    indentCount++;

    file << Indenter(indentCount) << "\"tree\": [" << endl;
    indentCount++;

    TNode* node;
    Queue<TNode*>* queue = new Queue<TNode*>();

    queue->Enqueue(tree->GetRoot());

    while (!queue->Empty()) {
        node = queue->Dequeue()->data;

        if (node == nullptr) {
            continue;
        }

        if (node->left != nullptr) {
            queue->Enqueue(node->left);
        }
        if (node->right != nullptr) {
            queue->Enqueue(node->right);
        }

        file << Indenter(indentCount) << "{" << endl;
        indentCount++;

        file << Indenter(indentCount) << "\"dueDate\": " << node->key << "," << endl;
        
        file << Indenter(indentCount) << "\"tasks\": [" << endl;
        indentCount++;

        Node<Task>* task = node->tasks->GetHead();
        while (task != nullptr) {
            file << Indenter(indentCount) << "{" << endl;
            indentCount++;

            file << Indenter(indentCount) << "\"name\": \"" << task->data.name << "\"" << endl;
            indentCount--;

            file << Indenter(indentCount) << "}";
            if (task->next != nullptr) {
                file << ",";
            }
            file << endl;

            task = task->next;
        }
        indentCount--;
        file << Indenter(indentCount) << "]" << endl;
        
        indentCount--;
        file << Indenter(indentCount) << "}";
        if (!queue->Empty()) {
            file << ",";
        }
        file << endl;
    }
    indentCount--;
    file << Indenter(indentCount) << "]" << endl;

    indentCount--;
    file << Indenter(indentCount) << "}" << endl;

    file.flush();
    file.close();
}
