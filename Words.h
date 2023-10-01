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

    template<typename T>
    void fisherYatesShuffle(vector<T>& vec) const;

    vector<Word> getUniqueWordlist(vector<Word> templist,short int num) const;
    // Vocabulary test
    void vocabularyTest() const;
    bool flashcard() const;
    bool wordpuzzle() const;
    /// @brief use binary search to find a word in the list
    /// @param isSafe findWordUtil doesWordExist is all part of wordpuzzle
    /// @return found or not by boolean variable
    bool isWordList(const string& targetWord) const;
    bool isSafe(int i, int j, int row, int col, vector<vector<bool>>& visited);
    bool findWordUtil(vector<vector<char>>& boggle, vector<vector<bool>>& visited, int i, int j, string& str, const string& target, int row, int col);
    bool doesWordExist(vector<vector<char>>& boggle, string target, int row, int col);

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
