#ifndef TRIE_H
#define TRIE_H

#define LOADRATE 0.75f

class TrieNode {
public:
    TrieNode();
    ~TrieNode();
    TrieNode* addChild(char value);
    TrieNode* getChild(char value);
    bool checkExpend();

    bool isEnd;
    int count;
    int capacity;
    char* values;
    TrieNode** children;
private:
    bool expend();
    inline int getHashPos(char value);
};

class Trie {
    public:
        Trie();
        ~Trie();
        bool insert(const char* word);
        bool search(const char* word);

    private:
        TrieNode* root;
        int maxDepth;
};

#endif // TRIE_H