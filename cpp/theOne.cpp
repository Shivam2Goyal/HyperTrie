#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>
#include <conio.h>

using namespace std;
using namespace std::chrono;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_end_of_url;
    int visit_count;

    TrieNode() : is_end_of_url(false), visit_count(0) {}
    
    ~TrieNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

class Trie {
private:
    TrieNode* root;

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
    
    ~Trie() {
        cleanup(root);
    }

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

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

    void insertURL(const string& url) {
        if (url.empty()) return;
        
        TrieNode* current = root;
        for (char ch : url) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->is_end_of_url = true;
        current->visit_count++;
    }

private:
    void printHistoryHelper(TrieNode* node, string& current_url) const {
        if (!node) return;

        if (node->is_end_of_url) {
            cout << current_url << " - Visits: " << node->visit_count << endl;
        }

        for (const auto& pair : node->children) {
            current_url.push_back(pair.first);
            printHistoryHelper(pair.second, current_url);
            current_url.pop_back();
        }
    }

public:
    void printHistory() const {
        string current_url;
        printHistoryHelper(root, current_url);
    }
};

string readFileContent(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void loadURLsFromFile(const string& filename, Trie& trie) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string url;
    while (getline(file, url)) {
        if (!url.empty()) {
            trie.insertURL(url);
        }
    }
    file.close();
}

int main() {
    const string urls_file = "urls.txt";
    string previousContent = readFileContent(urls_file);
    
    if (previousContent.empty()) {
        cout << "Please create urls.txt file with some URLs before running the program.\n";
        return 1;
    }

    // Initial load
    Trie trie;
    loadURLsFromFile(urls_file, trie);
    
    cout << "Initial Browser History:\n";
    trie.printHistory();
    cout << "\nMonitoring " << urls_file << " for changes...\n";
    cout << "Press 'Q' to exit\n\n";

    bool running = true;
    auto start = steady_clock::now();
    while (running) {
        // Read current file content
        string currentContent = readFileContent(urls_file);

        // If content has changed, update the trie
        if (currentContent != previousContent && !currentContent.empty()) {
            cout << "\nFile content changed. Updating history...\n";
            
            // Clear the existing trie by creating a new instance
            Trie newTrie;
            loadURLsFromFile(urls_file, newTrie);
            trie = std::move(newTrie);
            
            cout << "Updated Browser History:\n";
            trie.printHistory();  // Print the updated history
            cout << "\nMonitoring " << urls_file << " for changes...\n";
            
            // Update previousContent to avoid repeated reloading
            previousContent = currentContent;
        }
  
        // Small delay to prevent high CPU usage
        auto end = steady_clock::now();
        if (duration_cast<milliseconds>(end - start).count() >= 100) {
            start = end;
        }
    }

    cout << "\nExiting program...\n";
    return 0;
}
