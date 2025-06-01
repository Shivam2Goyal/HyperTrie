#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>
#include <conio.h>  // For _kbhit() and _getch() to detect key press (Windows-only)

using namespace std;
using namespace std::chrono;

// ------------------------ Trie Node Definition ------------------------
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;  // Maps characters to their respective child nodes
    bool is_end_of_url;                       // Marks if this node is the end of a complete URL
    int visit_count;                          // How many times this URL has been inserted

    TrieNode() : is_end_of_url(false), visit_count(0) {}
    
    // Recursively delete all child nodes to prevent memory leaks
    ~TrieNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

// ------------------------ Trie Structure ------------------------
class Trie {
private:
    TrieNode* root;

    // Helper function to recursively delete nodes
    void cleanup(TrieNode* node) {
        if (node) {
            for (auto& pair : node->children) {
                cleanup(pair.second);
            }
            delete node;
        }
    }

public:
    Trie() : root(new TrieNode()) {}

    // Destructor calls cleanup to free memory
    ~Trie() {
        cleanup(root);
    }

    // Disable copy constructor and assignment (deep copies are complex and not needed)
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Enable move semantics for efficient object replacement
    Trie(Trie&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    Trie& operator=(Trie&& other) noexcept {
        if (this != &other) {
            cleanup(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    // Insert a URL into the Trie, character by character
    void insertURL(const string& url) {
        if (url.empty()) return;

        TrieNode* current = root;
        for (char ch : url) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();  // Create node if not present
            }
            current = current->children[ch];
        }
        current->is_end_of_url = true;
        current->visit_count++;  // Increment visit count
    }

private:
    // Helper for recursively printing the stored URLs
    void printHistoryHelper(TrieNode* node, string& current_url) const {
        if (!node) return;

        if (node->is_end_of_url) {
            cout << current_url << " - Visits: " << node->visit_count << endl;
        }

        for (const auto& pair : node->children) {
            current_url.push_back(pair.first);               // Add next character
            printHistoryHelper(pair.second, current_url);    // Recurse into child
            current_url.pop_back();                          // Backtrack
        }
    }

public:
    // Public function to print all URLs stored in the trie
    void printHistory() const {
        string current_url;
        printHistoryHelper(root, current_url);
    }
};

// ------------------------ Utility Functions ------------------------

// Read full content of a file into a string
string readFileContent(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Load URLs from a file and insert them into the Trie
void loadURLsFromFile(const string& filename, Trie& trie) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string url;
    while (getline(file, url)) {
        if (!url.empty()) {
            trie.insertURL(url);  // Add each non-empty line as a URL
        }
    }
    file.close();
}

// ------------------------ Main Program ------------------------
int main() {
    const string urls_file = "urls.txt";

    // Check if file has content
    string previousContent = readFileContent(urls_file);
    if (previousContent.empty()) {
        cout << "Please create urls.txt file with some URLs before running the program.\n";
        return 1;
    }

    // Load initial data into Trie
    Trie trie;
    loadURLsFromFile(urls_file, trie);

    cout << "Initial Browser History:\n";
    trie.printHistory();
    cout << "\nMonitoring " << urls_file << " for changes...\n";
    cout << "Press 'Q' to exit\n\n";

    bool running = true;
    auto start = steady_clock::now();

    while (running) {
        // Check for file update
        string currentContent = readFileContent(urls_file);

        if (currentContent != previousContent && !currentContent.empty()) {
            cout << "\nFile content changed. Updating history...\n";

            // Rebuild the Trie with updated content
            Trie newTrie;
            loadURLsFromFile(urls_file, newTrie);
            trie = std::move(newTrie);  // Move assignment to replace the trie efficiently

            cout << "Updated Browser History:\n";
            trie.printHistory();
            cout << "\nMonitoring " << urls_file << " for changes...\n";

            previousContent = currentContent;  // Update cached content
        }

        // Optional: Check if the user wants to quit
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'q' || ch == 'Q') {
                running = false;
            }
        }

        // Throttle loop speed (every ~100ms)
        auto end = steady_clock::now();
        if (duration_cast<milliseconds>(end - start).count() >= 100) {
            start = end;
        }
    }

    cout << "\nExiting program...\n";
    return 0;
}
