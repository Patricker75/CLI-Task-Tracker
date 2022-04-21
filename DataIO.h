#ifndef DATAIO_H
#define DATAIO_H

#include <fstream>
#include <string>

#include "TaskTree.h"
#include "TagsList.h"
#include "Queue.h"

using namespace std;

TaskTree* LoadData (string filePath, TagsList* tags);

void ParseTNode (ifstream& file, TaskTree* tree, TagsList* tags);

Task ParseTask (ifstream& file, TagsList* tags);

LinkedList<string>* ParseTags(ifstream& file);

void SaveData (TaskTree* tree, string filePath);

#endif