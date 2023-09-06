#include "Words.h"
#include <fstream>
#include <sstream>
#include<iostream>
#include<ctime>
#include<unistd.h>
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
const Word& Words::generateRandomWord() const {
    // Check if wordList is empty
    if (wordList.empty()) {
        throw runtime_error("Word list is empty. Cannot generate a random word.");
    }
    time_t currentTime = time(nullptr);
    pid_t currentPID = getpid();

    // Combine the time and process ID to create a seed
    unsigned int seed = static_cast<unsigned int>(currentTime) ^ static_cast<unsigned int>(currentPID);

    // Seed the random number generator
    srand(seed);

    // Generate a random index within the bounds of the wordList
    int randomIndex = rand() % wordList.size();

    // Return the random word at the generated index
    return wordList[randomIndex];
}
void Words::vocabularyTest() const {
    // Create an empty vector to store selected words
    std::vector<Word> selectedWords;

    // Repeat until you have selected four different words
    while (selectedWords.size() < 4) {
        // Generate a random word
        const Word& randomWord = generateRandomWord();

        // Check if the word is not already in the list
        bool isUnique = true;
        for (const Word& selectedWord : selectedWords) {
            if (selectedWord.getWord() == randomWord.getWord()) {
                isUnique = false;
                break; // Word is not unique; break out of the loop
            }
        }

        // If the word is unique, add it to the list
        if (isUnique) {
            selectedWords.push_back(randomWord);
        }
    }

    // Display the selected words for the vocabulary test
     // Randomly select one of the words as the correct answer
    int correctAnswerIndex = rand() % 4;
    const Word& correctAnswer = selectedWords[correctAnswerIndex];

    // Display the quiz
    cout << "Vocabulary Test:" << endl;
    // Ask the user for their answer
    int userAnswer;
    cout << "What is the meaning of " << correctAnswer.getWord() << " : "<< endl;
    for (int i = 0; i < 4; ++i) {
        cout << i + 1 << ". " << selectedWords[i].getMeaning() << endl;
    }
    cin >> userAnswer;

    // Check the user's answer
    if (userAnswer == correctAnswerIndex + 1) {
        cout << "Correct! The meaning of \"" << correctAnswer.getWord() << "\" is \"" << correctAnswer.getMeaning() << "\"." << endl;
    } else {
        cout << "Incorrect. The correct meaning of \"" << correctAnswer.getWord() << "\" is \"" << correctAnswer.getMeaning() << "\"." << endl;
    }
}