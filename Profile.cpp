#include <iostream>
#include <fstream>
#include <string>
#include<algorithm>
#include<cctype>
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
string Profile::generateID() {
    const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int idLength = 6;  // Adjust as needed

    srand(time(0));  // Seed for random number generation

    string generatedID;
    for (int i = 0; i < idLength; ++i) {
        generatedID.push_back(alphabet[std::rand() % alphabet.size()]);
    }
  
    return generatedID;  // Return a string of asterisks of the same length as the ID
}

// Prompt the user for input and store in the file
void Profile::promptAndStore() {
    if (!isFileEmpty()) {
        // File is not empty, do nothing
        return;
    }

    while (true) {
        cout << "Enter your name: ";
        cin.ignore(); // Clear buffer before getline
        getline(cin, name);

        bool validName = all_of(name.begin(), name.end(), [](char c) {
            return isalnum(c) || isspace(c);
        });

        if (validName) {
            break;
        } else {
            cout << "Invalid characters in the name. Please use only alphabets and numbers." << endl;
        }
    }

    while (true) {
        cout << "Enter your password: ";
        cin >> password;

        // Password validation rules 

        break;
    }
    id = generateID();
    // Store the input in the file
    ofstream outputFile("profile.text");
    outputFile << name << "," << password << "," << id << endl;
    cout << "Profile created and stored successfully." << endl;
    cout << "The id is : " << id << endl;
    cout << "Press Enter to continue...";
    cin.ignore(); // Ignore any previous newline character
    cin.get();    // Wait for Enter key
}
