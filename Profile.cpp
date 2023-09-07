#include <iostream>
#include <fstream>
#include <string>
#include "Words.h"
using namespace std;


Profile :: Profile() {}
   
// Getter methods for profile data
string Profile::getName() const {
    return Profile::name;
}

string Profile::getPassword() const {
    return Profile::password;
}

// Check if the profile data file is empty
bool Profile::isFileEmpty() {
    ifstream inputFile("profile.text");
    return inputFile.peek() == ifstream::traits_type::eof();
}

// Prompt the user for input and store in the file
void Profile::promptAndStore() {
    if (!isFileEmpty()) {
        // File is not empty, do nothing
        return;
    }

    // File is empty, prompt for input
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;

    // Store the input in the file
    ofstream outputFile("profile.text");
    outputFile << name << "," << password << endl;
    cout << "Profile created and stored successfully." << endl;

    cout << "Press Enter to continue...";
    cin.ignore(); // Ignore any previous newline character
    cin.get();    // Wait for Enter key

}
