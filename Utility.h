#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <fstream>
#include <iostream>

#include "TaskTree.h"

std::string ListToString(Node<Task>* node);

std::string InOrderTreeTraverse(TNode* node);

int DateParser(std::string date);

#endif