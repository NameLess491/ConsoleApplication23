#include <iostream>
#include <fstream>
#include <map>
#include <string>

class Dictionary {
private:
    std::map<std::string, std::string> words;

public:
    void addWord(const std::string& word, const std::string& meaning) {
        words[word] = meaning;
    }

    void editWord(const std::string& word, const std::string& newMeaning) {
        if (words.find(word) != words.end()) {
            words[word] = newMeaning;
            std::cout << "Word updated.\n";
        }
        else {
            std::cout << "Word not found.\n";
        }
    }

    void deleteWord(const std::string& word) {
        if (words.erase(word)) {
            std::cout << "Word deleted.\n";
        }
        else {
            std::cout << "Word not found.\n";
        }
    }

    void searchWord(const std::string& word) const {
        auto it = words.find(word);
        if (it != words.end()) {
            std::cout << "Meaning of '" << word << "': " << it->second << "\n";
        }
        else {
            std::cout << "Word not found.\n";
        }
    }

    void displayAll() const {
        for (const auto& entry : words) {
            std::cout << entry.first << ": " << entry.second << "\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file) {
            for (const auto& entry : words) {
                file << entry.first << "\n" << entry.second << "\n";
            }
            std::cout << "Dictionary saved to " << filename << ".\n";
        }
        else {
            std::cerr << "Error saving to file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file) {
            words.clear();
            std::string word, meaning;
            while (std::getline(file, word) && std::getline(file, meaning)) {
                words[word] = meaning;
            }
            std::cout << "Dictionary loaded from " << filename << ".\n";
        }
        else {
            std::cerr << "Error loading from file.\n";
        }
    }
};

int main() {
    Dictionary dict;
    dict.loadFromFile("dictionary.txt");

    int choice;
    std::string word, meaning;

    while (true) {
        std::cout << "\nDictionary Menu:\n";
        std::cout << "1. Add Word\n2. Edit Word\n3. Delete Word\n4. Search Word\n5. Display All\n6. Save to File\n7. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            std::cout << "Enter word: ";
            std::getline(std::cin, word);
            std::cout << "Enter meaning: ";
            std::getline(std::cin, meaning);
            dict.addWord(word, meaning);
            break;
        case 2:
            std::cout << "Enter word to edit: ";
            std::getline(std::cin, word);
            std::cout << "Enter new meaning: ";
            std::getline(std::cin, meaning);
            dict.editWord(word, meaning);
            break;
        case 3:
            std::cout << "Enter word to delete: ";
            std::getline(std::cin, word);
            dict.deleteWord(word);
            break;
        case 4:
            std::cout << "Enter word to search: ";
            std::getline(std::cin, word);
            dict.searchWord(word);
            break;
        case 5:
            dict.displayAll();
            break;
        case 6:
            dict.saveToFile("dictionary.txt");
            break;
        case 7:
            dict.saveToFile("dictionary.txt");
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
