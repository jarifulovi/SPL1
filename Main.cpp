#include <iostream>
#include <string>
#include <cstdlib> // For system("cls") on Windows or system("clear") on Linux/Mac
#include"Words.h"

using namespace std;
int main() {
    string input;

    cout << "Enter 'start' to begin\n";
    cout << "Enter 'close' to exit\n";
    cin >> input;

    if (input == "start") {
        #ifdef _WIN32
        // Clear screen on Windows
        system("cls");
        #else
        // Clear screen on Linux/Mac
        system("clear");
        #endif

        cout << "Application starting..." << endl;
        Words myWords;

        // Load words from "input.text"
        if (myWords.loadFromFile()) {
            //const std::vector<Word>& wordList = myWords.getWordList();

            // Display attributes of each word
            myWords.vocabularyTest();

        } else {
            std::cerr << "Error: Could not open 'input.txt'." << std::endl;
            return 1;
        }
    } 
    else if(input=="close"){
        #ifdef _WIN32
        // Clear screen on Windows
        system("cls");
        #else
        // Clear screen on Linux/Mac
        system("clear");
        #endif
        cout << "Thank you for using this app" << endl;
        exit(0);
    }
    else{
        printf("Invalid input!\n");
    }

    return 0;
}
