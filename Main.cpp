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

    if (input == "start") {     //  starting point of application
        clearMainScreen();

        cout << "Application starting..." << endl;
        Words myWords;
        Profile myprofile;

        myprofile.promptAndStore();
        clearMainScreen();
        // Load words from "input.text"
        if (myWords.loadFromFile()) {      // ready to execute application
            
            cout << "1.Multiple choice question\n";
            cout << "2.flashcard game\n";
            cout << "3.word puzzle\n";
            cout << "4.flashcard 3 cards\n";
            cout << "5.Word Ladder\n";
            cout << "q to quit\n";
            cin >> input;
            // Display attributes of each word
            if(input=="1")  myWords.vocabularyTest(myprofile);
            else if(input=="2") myWords.flashcard(myprofile);
            else if(input=="3")   myWords.wordpuzzle(myprofile);
            else if(input=="4") myWords.flashcard3(myprofile);
            else if(input=="5") myWords.wordLadder(myprofile);
            else{}
            myprofile.updateAndStore();
        } 
        else {
            cerr << "Error: Could not open 'input.txt'." << endl;
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
