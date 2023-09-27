#ifndef WORDS_H
#define WORDS_H

#include <vector>
#include <string>
#include<ctime>
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

    // Generating random numbers
    const Word& generateRandomWord() const;

    void fisherYatesShuffle(vector<Word>& vec) const;

    vector<Word> getUniqueWordlist(vector<Word> templist,short int num) const;
    // Vocabulary test
    void vocabularyTest() const;
    void flashcard() const;

};
class Profile {
private:
    string name;
    string password;
    string id;

public:
    Profile();

    string getName() const;
    string getPassword() const;
    bool isFileEmpty();
    void promptAndStore();
    string generateID();
    
};
#endif
