#include "Words.h"
#include <fstream>
#include <sstream>
using namespace std;

Words::Words() {} // Constructor

bool Words::loadFromFile() {
    ifstream inputFile("input.text"); // Hardcoded filename
    if (!inputFile.is_open()) {
        return false; // Failed to open the file.
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string w, m, pos;
        if (getline(iss, w, ',') && getline(iss, m, ',') && getline(iss, pos)) {
            addWord(Word(w, m, pos));
        }
    }

    inputFile.close();
    return true;
}


void Words::addWord(const Word& word) {
    wordList.push_back(word);
}

const vector<Word>& Words::getWordList() const {
    return wordList;
}
