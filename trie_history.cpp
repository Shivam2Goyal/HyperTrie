    #include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfUrl;
    int visitCount;

    TrieNode() {
        isEndOfUrl = false;
        visitCount = 0;
    }
};

class Trie {
private:
    TrieNode* root;

    void displayHelper(TrieNode* node, string prefix) {
        if (node->isEndOfUrl) {
            cout << prefix << " (Visited: " << node->visitCount << " times)" << endl;
        }
        for (auto it : node->children) {
            displayHelper(it.second, prefix + it.first);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string url) {
        TrieNode* node = root;
        for (char ch : url) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfUrl = true;
        node->visitCount++;
    }

    void display() {
        displayHelper(root, "");
    }
};

int main(int argc, char* argv[]) {
    static Trie trie;

    if (argc == 2) {
        string url = argv[1];
        trie.insert(url);
        cout << "URL inserted: " << url << endl;
    } else {
        cout << "Displaying all URLs and their visit counts:" << endl;
        trie.display();
    }

    return 0;
}
