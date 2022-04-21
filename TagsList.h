#ifndef TAGSLIST_H
#define TAGSLIST_H

#include "TagsTree.h"

struct TagPair {
    TagPair(std::string tag) {
        this->tag = tag;
        this->tree = new TagsTree();

        this->next = nullptr;
    }

    std::string tag;
    TagsTree* tree;

    TagPair* next;
};

class TagsList {
private:
    TagPair* head;
    TagPair* tail;
public:
    TagsList() {
        this->head = nullptr;
        this->tail = nullptr;
    };

    void Insert(std::string tag, Task* t) {
        if (this->head == nullptr) {
            this->head = new TagPair(tag);
            this->tail = this->head;
            this->head->tree->Insert(t->dueDate, t);

            return;
        }
    
        TagPair* target = this->Search(tag);

        if (target == nullptr) {
            target = new TagPair(tag);
            this->tail->next = target;
            this->tail = target;

            target->tree->Insert(t->dueDate, t);

            return;
        }

        target->tree->Insert(t->dueDate, t);
    }
    
    TagPair* Search(std::string tag) {
        TagPair* current = this->head;

        while (current != nullptr) {
            if (tag == current->tag) {
                break;
            }
            current = current->next;
        }

        return current;
    }

    void Remove(std::string tag, Task* t) {
        TagPair* target = this->Search(tag);

        if (target == nullptr) {
            return;
        }

        target->tree->Remove(t);
    }
};

#endif