#include "DataIO.h"

#pragma region Loading Data

TaskTree* LoadData (string filePath, TagsList* tags) {
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
            ParseTNode(file, tree, tags);
        }
    }

    file.close();

    return tree;
}

void ParseTNode (ifstream& file, TaskTree* tree, TagsList* tags) {
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

            Task* ptr = tree->Insert(t);

            Node<string>* current = t.tags->GetHead();
            while (current != nullptr) {
                tags->Insert(current->data, ptr);

                current = current->next;
            }
        }
    }

}

Task ParseTask (ifstream& file) {
    Task t;

    string line;

    getline(file, line);

    int indexOfValue = line.find(": ") + 3;
    string temp;
    temp = line.substr(indexOfValue, line.find_last_of("\"") - indexOfValue);
    t.name = Parser(temp);

    getline(file, line);
    indexOfValue = line.find(": ") + 3;
    temp = line.substr(indexOfValue, line.find_last_of("\"") - indexOfValue);
    t.notes = Parser(temp);

    t.tags = ParseTags(file);

    return t;
}

LinkedList<string>* ParseTags(ifstream& file) {
    LinkedList<string>* list = new LinkedList<string>();
    
    string line;

    getline(file, line);
    
    getline(file, line);
    while (line.find("]") == line.npos) {
        line = line.substr(line.find("\"") + 1);
        line = line.substr(0, line.find("\""));

        list->Insert(line);

        getline(file, line);
    }

    return list;
}

string Parser(string& s) {
    stringstream ss{""};

    for(size_t i = 0; i < s.length(); i++)
    {
        if (s.at(i) == '\\')
        {
            switch(s.at(i + 1))
            {
                case 'n':  ss << "\n"; i++; break;
                case '"':  ss << "\""; i++; break;
                default:   ss << "\\";      break;
            }       
        }
        else 
        {
            ss << s.at(i);
        }
    }

    return ss.str();
}

#pragma endregion Loading Data

#pragma region Saving Data

string Indenter(int tabCount) {
    string out = "";

    for (int i = 0; i < tabCount; i++) {
        out += "\t";
    }
    return out;
}

string Formatter(string& s) {
    stringstream ss{""};

    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == '"') {
            ss << "\\\"";
        }
        else {
            ss << s.at(i);
        }
    }

    return ss.str();
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

            file << Indenter(indentCount) << "\"name\": \"" << Formatter(task->data.name) << "\"," << endl;
            file << Indenter(indentCount) << "\"notes\": \"" << Formatter(task->data.notes) << "\"," << endl;

            file << Indenter(indentCount) << "\"tags\": [" << endl;
            indentCount++;

            Node<string>* currentTag = task->data.tags->GetHead();
            while (currentTag != nullptr) {
                file << Indenter(indentCount) << "\"" << currentTag->data << "\"";

                if (currentTag->next != nullptr) {
                    file << ",";
                }
                file << endl;

                currentTag = currentTag->next;
            }
            indentCount--;
            file << Indenter(indentCount) << "]" << endl;

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

#pragma endregion Saving Data
