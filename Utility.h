#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <fstream>
#include <iostream>

#include "TaskTree.h"
#include "TagsList.h"

std::string ListToString(Node<Task>* node);

std::string InOrderTreeTraverse(TNode* node);

int DateParser(std::string date);

std::string PrintTags(Task t);

std::string PrintTasks(TagNode* node); 

#endif