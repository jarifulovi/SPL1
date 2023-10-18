#ifndef WORDS_H
#define WORDS_H

#include <vector>
#include <string>
#include<ctime>
using namespace std;

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
    string generateID() const;
    void updateAndStore();
    
};

class Word {
private:
    string word;
    string meaning;
    string partOfSpeech;

public:
    Word(const string& w, const string& m, const string& pos);

    // Getter methods
    string getWord() const;
    string getSmallLetter() const;
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
    void vocabularyTest(Profile& myprofile) const;
    // Flashcard
    bool flashcard(Profile& myprofile) const;
    // WordPuzzle
    bool wordpuzzle(Profile& myprofile) const;
    bool isWordList(const string& targetWord) const;
    bool isSafe(int i, int j, int row, int col, vector<vector<bool>>& visited) const ;
    bool findWordUtil(vector<vector<char>>& boggle, vector<vector<bool>>& visited, int i, int j, string& str, const string& target, int row, int col) const;
    bool doesWordExist(vector<vector<char>>& boggle, string target, int row, int col) const ;
    // Flashcard 3 Cards
    bool flashcard3(Profile& myprofile) const;
    // Word ladder game
    bool isAdjacent(const std::string& word1, const std::string& word2) const;
    std::vector<std::string> findPathWords(const std::string& start_word, const std::string& end_word, const std::vector<Word>& wordList) const;
    bool wordLadder(Profile& myprofile) const;
};

class tri {
public:
    string a, b, c;

    // Default constructor
    tri() : a(""), b(""), c("") {}

    // Constructor with parameters
    tri(const string& a_val, const string& b_val, const string& c_val)
        : a(a_val), b(b_val), c(c_val) {}
};
#endif
