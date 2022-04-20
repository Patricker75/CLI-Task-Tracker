#ifndef DATAIO_H
#define DATAIO_H

#include <fstream>
#include <string>

#include "TaskTree.h"
#include "Queue.h"

using namespace std;

TaskTree* LoadData (string filePath);

void ParseTNode (ifstream& file, TaskTree* tree);

Task ParseTask (ifstream& file);

void SaveData (TaskTree* tree, string filePath);

#endif