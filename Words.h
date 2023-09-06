#ifndef WORDS_H
#define WORDS_H

#include <vector>
#include <string>
using namespace std;

class Word {
private:
    string word;
    string meaning;
    string partOfSpeech;

public:
    Word(const string& w, const string& m, const string& pos);

    // Getter methods
    string getWord() const;
    string getMeaning() const;
    string getPartOfSpeech() const;
};

class Words {
private:
    vector<Word> wordList;

public:
    Words(); // Constructor

    // Function to load words from a file
    bool loadFromFile();

    // Function to add a word to the list
    void addWord(const Word& word);

    // Function to get the list of words
    const vector<Word>& getWordList() const;
};

#endif
