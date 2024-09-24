
#include "trie.h"

TrieNode::TrieNode() {
    isEnd = false;
    count = 0;
    capacity = 0;
    values = nullptr;
    children = nullptr;
}

TrieNode::~TrieNode() {
    if (children != nullptr) {
        for (int i=0;i<capacity;i++) {
            if (children[i] != nullptr) {
                delete children[i];
            }
        }
        delete[] children;
    }
    if (values!= nullptr) {
        delete[] values;
    }
}

inline int TrieNode::getHashPos(char value) {
    int h = ((unsigned char)value) % capacity;
    for (int i=0;i<capacity;i++) {
        if (values[h] == value || values[h] == '\0') {
            return h;
        }
        h = (h + 1) % capacity;
    }
    return h;
}

bool TrieNode::expend() {
    int oldCapacity = capacity;
    char* oldValues = values;
    TrieNode** oldChildren = children;
    if (capacity == 0) {
        capacity = 1;
    }
    capacity = capacity * 2 + 1;
    values = new char[capacity];
    children = new TrieNode*[capacity];
    for (int i=0;i<capacity;i++) {
        values[i] = '\0';
        children[i] = nullptr;
    }
    if (oldValues != nullptr) {
        for (int i=0;i<oldCapacity;i++) {
            if (oldValues[i]!= '\0') {
                int h = getHashPos(oldValues[i]);
                children[h] = oldChildren[i];
                values[h] = oldValues[i];
            }
        }
        delete[] oldValues;
        delete[] oldChildren;
    }
    return true;
}

TrieNode* TrieNode::addChild(char value) {
    if (this->capacity == 0) {
        this->expend();
    }
    int h = getHashPos(value);
    if (this->values[h] == value) {
        return children[h];
    }
    if (((this->count + 1.0f) / this->capacity) > LOADRATE) {
        this->expend();
    }
    h = getHashPos(value);
    values[h] = value;
    children[h] = new TrieNode();
    count++;
    return children[h];
}

TrieNode* TrieNode::getChild(char value) {
    int h = getHashPos(value);
    if (values[h] == value) {
        return children[h];
    }
    return nullptr;
}

Trie::Trie()
{
    root = new TrieNode();   
}

Trie::~Trie()
{
    delete root;
}

bool Trie::insert(const char *word) {
    TrieNode* node = root;
    while (*word!= '\0') {
        node = node->addChild(*word);
        word++;
    }
    bool isNew = !node->isEnd;
    node->isEnd = true;
    return isNew;
}

bool Trie::search(const char *word) {
    TrieNode* node = root;
    while (*word!= '\0') {
        node = node->getChild(*word);
        if (node == nullptr) {
            return false;
        }
        word++;
    }
    return node->isEnd;
}