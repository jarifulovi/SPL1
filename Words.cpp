#include "Words.h"
#include <fstream>
#include <sstream>
#include<iostream>
#include<ctime>
#include<unistd.h>
#include<chrono>
#include<random>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

void clearScreen() {
    system(CLEAR_SCREEN);
}
   
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

void Words::fisherYatesShuffle(vector<Word> &vec) const
{
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = vec.size() - 1; i > 0; --i) {
        uniform_int_distribution<int> distribution(0, i);
        int j = distribution(rng);

        // Swap elements at positions i and j
        Word temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }
}
vector<Word> Words::getUniqueWordlist(vector<Word> templist,short int num) const{
    vector<Word> selectedWords;
    short int i=0;
    //for(i=0;i<4;i++) selectedWords.push_back(temp[i]);
    // Repeat until you have selected four different words
    while (selectedWords.size() < num) {
        // Generate a random word
        const Word& randomWord = templist[i++];
          
        // Check if the word is not already in the list
        bool isUnique = true;
        for (const Word& selectedWord : selectedWords) {
            if (selectedWord.getMeaning() == randomWord.getMeaning()) {
                isUnique = false;
                break; // Word is not unique; break out of the loop
            }
        }

        // If the word is unique, add it to the list
        if (isUnique) {
            selectedWords.push_back(randomWord);
        }
    }
    return selectedWords;
}

void Words::vocabularyTest() const {
    char userInput;
    short int iteration = 20;
    vector<Word> temp(wordList);
    do {
        if(!iteration){
            clearScreen();
            cout << "Congratulation you passed the first stage" << endl;
            break;
        }
        clearScreen();
        // Create an empty vector to store selected words

        fisherYatesShuffle(temp);
        vector<Word> selectedWords = getUniqueWordlist(temp,4);
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
        cout << "Enter your answer (1, 2, 3, 4) or 'q' to quit: ";
        cin >> userInput;

        if (userInput == 'q') {
            return; // Exit the function if the user wants to quit
        }

        // Check the user's answer
        int userChoice = userInput - '0'; // Convert char to int
        if (userChoice >= 1 && userChoice <= 4) {
            if (userChoice == correctAnswerIndex + 1) {
                cout << "Correct! The meaning of \"" << correctAnswer.getWord() << "\" is \"" << correctAnswer.getMeaning() << "\"." << endl;
            } else {
                cout << "Incorrect. The correct meaning of \"" << correctAnswer.getWord() << "\" is \"" << correctAnswer.getMeaning() << "\"." << endl;
            }
        } else {
            cout << "Invalid input. Please enter 1, 2, 3, 4, or 'q' to quit." << endl;
        }
       
        // Prompt for the next question
        cout << "Press Enter to continue..." << endl;
        cin.ignore(); // Ignore any previous newline character
        cin.get();    // Wait for Enter key
        
    } while (userInput != 'q'&& iteration--);
}
void Words:: flashcard() const {
    vector<Word> templist(wordList);

    fisherYatesShuffle(templist);
    vector<Word> cards = getUniqueWordlist(templist,5);
    
}
