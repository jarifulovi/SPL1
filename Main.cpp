#include <iostream>
#include <string>
#include <cstdlib> // For system("cls") on Windows or system("clear") on Linux/Mac
#include"Words.h"
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;
void clearMainScreen(){
    system(CLEAR_SCREEN);
}

int main() {
    string input;

    cout << "Enter 'start' to begin\n";
    cout << "Enter 'close' to exit\n";
    cin >> input;

    if (input == "start") {
        clearMainScreen();

        cout << "Application starting..." << endl;
        Words myWords;
        Profile myprofile;

        myprofile.promptAndStore();
        clearMainScreen();
        // Load words from "input.text"
        if (myWords.loadFromFile()) {
            //const std::vector<Word>& wordList = myWords.getWordList();
            cout << "1.Vocabulary Test"<<endl;
            cout << "q to quit"<< endl;
            cin >> input;
            // Display attributes of each word
            if(input=="1")  myWords.vocabularyTest();
            else{}

        } else {
            std::cerr << "Error: Could not open 'input.txt'." << std::endl;
            return 1;
        }
    } 
    else if(input=="close"){
        clearMainScreen();
        cout << "Thank you for using this app" << endl;
        exit(0);
    }
    else{
        printf("Invalid input!\n");
    }

    return 0;
}
