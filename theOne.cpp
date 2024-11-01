#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_end_of_url;
    int visit_count;

    TrieNode() {
        is_end_of_url = false;
        visit_count = 0;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Function to insert a URL into the trie
    void insertURL(const string& url) {
        TrieNode* current = root;

        for (char ch : url) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }

        // Mark the end of the URL and increment the visit count
        current->is_end_of_url = true;
        current->visit_count++;
    }

    // Helper function to recursively print the trie content (browsing history)
    void printHistoryHelper(TrieNode* node, string& current_url) {
        if (node->is_end_of_url) {
            // Print the URL along with its visit count
            cout << current_url << " - Visits: " << node->visit_count << endl;
        }

        // Recursively visit all the children nodes
        for (auto& child : node->children) {
            current_url.push_back(child.first);
            printHistoryHelper(child.second, current_url);
            current_url.pop_back();
        }
    }

    // Function to print the complete browsing history
    void printHistory() {
        string current_url = "";
        printHistoryHelper(root, current_url);
    }
};

int main() {
    Trie trie;
    string url;

    // Input loop to allow the user to enter URLs until the special key 'A' is entered
    while (true) {
        cout << "Enter URL (or 'A' to stop and print history): ";
        getline(cin, url);  // Take the entire input as a URL

        if (url == "A") {
            // If the special key "A" is entered, stop taking input and print history
            break;
        }

        // Insert the URL into the Trie
        trie.insertURL(url);
    }

    // Print the browsing history with visit counts
    cout << "\nBrowsing History:" << endl;
    trie.printHistory();

    return 0;
}