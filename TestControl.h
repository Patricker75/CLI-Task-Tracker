#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <string>
#include <fstream>

#include "TaskTree.h"
#include "TagsList.h"

void ParseInput(const std::string filePath, TaskTree* tree);

std::string GetTagAsString(TagNode* node);

#endif