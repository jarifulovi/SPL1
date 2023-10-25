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
        while(true){
            clearMainScreen();
            // first menu
            cout << "1.Word Games\n";
            cout << "2.Display Profile\n";
            cout << "3.Change Password\n";
            cout << "4.Connect Server\n";
            cout << "5.How to play\n";
            cout << "q to Exit\n";
            cin >> input;
            // second menu
            if (input=="1" && myWords.loadFromFile()) {
                while(true){
                    clearMainScreen();
                    cout << "1.Multiple choice question\n";
                    cout << "2.flashcard game\n";
                    cout << "3.word puzzle\n";
                    cout << "4.flashcard 3 cards\n";
                    cout << "5.Word Ladder\n";
                    cout << "q to back\n";
                    cin >> input;
                    // Display attributes of each word
                    if(input=="1")  myWords.vocabularyTest(myprofile);
                    else if(input=="2") myWords.flashcard(myprofile);
                    else if(input=="3")   myWords.wordpuzzle(myprofile);
                    else if(input=="4") myWords.flashcard3(myprofile);
                    else if(input=="5") myWords.wordLadder(myprofile);
                    else if(input=="q") break;
                    else{
                        cout << "Invalid input.Please use numbers (1-5) or q to back\n";
                        cout << "\nPress Enter to continue...";
                        cin.ignore(); // Ignore any previous newline character
                        cin.get();    // Wait for Enter key
                    }
                    myprofile.updateAndStore();
                }
            } 
            else if(input=="2"){
                myprofile.displayProfile();
                continue;
            }
            else if(input=="3"){
                myprofile.changePassword();
                continue;
            }
            else if(input=="4"){
                // connect server
                continue;
            }
            else if(input=="5"){
                myprofile.howToPlay();
                continue;
            }
            else if(input=="q"){
                break;
            }
            else{
                cout << "Invaild input.Try numbers(1-5) or q to exit\n";
                cout << "\nPress Enter to continue...";
                cin.ignore(); // Ignore any previous newline character
                cin.get();    // Wait for Enter key
            }
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
