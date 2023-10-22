#include <iostream>
#include <fstream>
#include<sstream>
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
short int Profile::getTime1() const {
    return Profile::time1;
}
short int Profile::getCorrect1() const {
    return Profile::correct1;
}
void Profile::setTime1(short int time) {
    Profile::time1 = time;
}
void Profile::setCorrect1(short int correct) {
    Profile::correct1 = correct;
}
short int Profile::getTime2() const {
    return Profile::time2;
}
void Profile::setTime2(short int time) {
    Profile::time2 = time;
}
short int Profile::getTime3() const {
    return Profile::time3;
}
void Profile::setTime3(short int time) {
    Profile::time3 = time;
}
short int Profile::getTime4() const {
    return Profile::time4;
}
void Profile::setTime4(short int time) {
    Profile::time4 = time;
}
short int Profile::getLoop4() const {
    return Profile::loop4;
}
void Profile::setLoop4(short int loop) {
    Profile::loop4 = loop;
}
// Check if the profile data file is empty
bool Profile::isFileEmpty() {
    ifstream inputFile("profile.txt");
    return inputFile.peek() == ifstream::traits_type::eof();
}
string Profile::generateID() {
    const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int idLength = 6;  // length of id

    srand(time(0));  // Seed for random number generation

    string generatedID;
    for (int i = 0; i < idLength; ++i) {
        generatedID.push_back(alphabet[std::rand() % alphabet.size()]);
    }
  
    return generatedID;
}

// Prompt the user for input and store in the file
void Profile::promptAndStore() {
    if (!isFileEmpty()) {
        // File has data to collect
        ifstream inFile("profile.txt");
        if (inFile.is_open()) {
            string line;
            if (getline(inFile, line)) {
                istringstream iss(line);
                vector<string> tokens;
                string token;

                while (getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
                name = tokens[0];
                password = tokens[1];
                id = tokens[2];
                // Convert the time and correct values to integers, if present
                time1 = stoi(tokens[3]);
                correct1 = stoi(tokens[4]);
                time2 = stoi(tokens[5]);
                time3 = stoi(tokens[6]);
                time4 = stoi(tokens[7]);
                loop4 = stoi(tokens[8]);
            }

            inFile.close();
        }
        return;
    }
    // initialize user stats
    time1 = 0;
    correct1 = 0;
    time2 = 0;
    time3 = 0;
    time4 = 0;
    loop4 = 2;
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
    ofstream outputFile("profile.txt");
    outputFile << name << "," << password << "," << id << "," << time1 << "," << correct1 
                       << "," << time2 << "," << time3 << "," << time4 << "," << loop4 
                       << std::endl;
    cout << "Profile created and stored successfully." << endl;
    cout << "Press Enter to continue...";
    cin.ignore(); // Ignore any previous newline character
    cin.get();    // Wait for Enter key
}
void Profile::updateAndStore() {
    std::ifstream inFile("profile.txt");
    // Check if the file is empty
    if (isFileEmpty()) {
        std::cout << "File is empty. Nothing to update." << std::endl;
        return;
    }

    inFile.close();  // Close the file

    // Open the file in truncate mode (clear contents)
    std::ofstream outFile("profile.txt", std::ios::trunc);

    // Write the class variables to the file separated by commas
    if (outFile.is_open()) {
        outFile << name << "," << password << "," << id << "," << time1 << "," << correct1 
                << "," << time2 << "," <<time3 << "," << time4 << "," << loop4 << std::endl;
        std::cout << "Profile information updated and saved to profile.txt." << std::endl;
        outFile.close();
    } 
    else {
        std::cerr << "Error opening the file." << std::endl;
    }
}
void Profile::achievement1(short int correct,short int time) const {
    if(correct==0) cout << "RANK : " << "NULL";
    if(correct>0 && correct<=10){
        if(time>=30) cout << "RANK : Bronze I\n";
        else if(time>=20 && time<30) cout << "RANK : Bronze II\n";
        else if(time>=10 && time<20) cout << "RANK : Bronze III\n";
        else cout << "RANK : Speed Bronze\n";
    }
    else if(correct>10 && correct <=15){
        if(time>30) cout << "RANK : Silver I\n";
        else if(time>=20 && time<30) cout << "RANK : Silver II\n";
        else if(time>=10 && time<20) cout << "RANK : Silver III\n";
        else cout << "RANK : Speed Silver\n";
    }
    else if(correct>15 && correct<19){
        if(time>=30) cout << "RANK : Gold I\n";
        else if(time>=20 && time<30) cout << "RANK : Gold II\n";
        else if(time>=10 && time<20) cout << "RANK : Gold III\n";
        else cout << "RANK : Speed Gold\n";
    }
    else if(correct==19){
        if(time>=30) cout << "RANK : Platinum I\n";
        else if(time>=20 && time<30) cout << "RANK : Platinum II\n";
        else if(time>=10 && time<20) cout << "RANK : Platinum III\n"; 
        else cout << "RANK : Speed Platinum\n";  
    }
    else if(correct==20){
        if(time>=30) cout << "RANK : Legend I\n";
        else if(time>=20 && time<30) cout << "RANK : Legend II\n";
        else if(time>=10 && time<20) cout << "RANK : Legend III\n";  
        else cout << "RANK : Speed Legend\n";
    }
}
void Profile::achievement2(short int time) const {
    if(time==0) cout << "RANK : NULL\n";
    if(time>=20)    cout << "RANK : Bronze\n";
    else if(time>=15 && time<20)    cout << "RANK : Silver\n";
    else if(time>=10 && time<15)    cout << "RANK : Platinum\n";
    else if(time>=5 && time<10)     cout << "RANK : Diamond\n";
    else                            cout << "RANK : Legend\n";
}
void Profile::achievement3(short int time) const {
    if(time==0) cout << "RANK : NULL\n";

}
void Profile::achievement4(short int time,short int loop) const {
    if(time==0) cout << "RANK : NULL\n";
    
}