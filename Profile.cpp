#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include<algorithm>
#include<cctype>
#include "Words.h"
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

void clearProfileScreen(){
    system(CLEAR_SCREEN);
}

void enterPressedProfile() {
    cout << "\n\nPress Enter to continue...";
    cin.ignore(); // Ignore any previous newline character
    cin.get();    // Wait for Enter key
}

Profile :: Profile() {}
   
// Getter methods for profile data
string Profile::getName() const {
    return Profile::name;
}
string Profile::getPassword() const {
    return Profile::password;
}
void Profile::setPassword(string pass) {
    Profile::password = pass;
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
short int Profile::getLoop2() const {
    return Profile:: loop2;
}
void Profile::setLoop2(short int loop) {
    Profile::loop2 = loop;
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
short int Profile::getTime5() const {
    return Profile::time5;
}
void Profile::setTime5(short int time) {
    Profile::time5 = time;
}
short int Profile::getTime6() const {
    return Profile::time6;
}
void Profile::setTime6(short int time) {
    Profile::time6 = time;
}
short int Profile::getTrial6() const {
    return Profile::trial6;
}
void Profile::setTrial6(short int trial) {
    Profile::trial6 = trial;
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
                loop2 = stoi(tokens[6]);
                time3 = stoi(tokens[7]);
                time4 = stoi(tokens[8]);
                loop4 = stoi(tokens[9]);
                time5 = stoi(tokens[10]);
                time6 = stoi(tokens[11]);
                trial6 = stoi(tokens[12]);
            }

            inFile.close();
        }
        return;
    }
    // initialize user stats
    time1 = 0;
    correct1 = 0;
    time2 = 0;
    loop2 = 1;
    time3 = 0;
    time4 = 0;
    loop4 = 2;
    time5 = 0;
    time6 = 0;
    trial6 = 0;
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
                       << "," << time2 << "," << loop2 << "," << time3 << "," << time4 
                       << "," << loop4 << "," << time5 <<  "," << time6 << "," << trial6
                       << std::endl;
    cout << "Profile created and stored successfully." << endl;
    enterPressedProfile();
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
                << "," << time2 << "," << loop2 << "," << time3 << "," << time4 << "," << loop4 
                << "," << time5 << "," << time6 << "," << trial6 << std::endl;
        //std::cout << "Profile information updated and saved to profile.txt." << std::endl;
        outFile.close();
    } 
    else {
        std::cerr << "Error opening the file." << std::endl;
    }
}
void Profile::loginProfile() {
    string input_name,input_pass;
    while(true){
        clearProfileScreen();
        cout << "   Login Profile\n";
        cout << "\n\nEnter your name : ";
        cin >> input_name;
        cout << "\nEnter your password : ";
        cin >> input_pass;
        if(input_name==Profile::name && input_pass==Profile::password){
            cout << "Login successful\n";
            enterPressedProfile();
            break;
        }
        else {
            cout << "Wrong name or password\n";
            cout << "Press enter to try again\n";
            enterPressedProfile();
            continue;
        }
    }
}
void Profile::changePassword() {
    loginProfile();
    clearProfileScreen();
    cout << " New profile password\n";
    cout << "\nEnter password : ";
    string input_pass;
    cin >> input_pass;
    setPassword(input_pass);
    updateAndStore();
    cout << "Password updated successfully\n";
    enterPressedProfile();
}
// display part
void Profile::displayProfile() const {
    clearProfileScreen();
    cout << "User Profile : \n";
    cout << "*************\n\n";
    cout << "Name : " << getName() << "\n\n";
    cout << "Achievements :\n";
    cout << "*************\n";
    cout << "\nMultiple choice question :\n";
    achievement1(getCorrect1(),getTime1());
    cout << "Best score : Time : " << getTime1() << " | Correct : " << getCorrect1() << "\n";
    cout << "\nFlashCard :\n";
    achievement2(getTime2(),getLoop2());
    cout << "Best score : Time : " << getTime2() << " | Loop trial : " << getLoop2() << "\n";
    cout << "\nWord Puzzle :\n";
    achievement3(getTime3());
    cout << "Best score : Time : " << getTime3() << "\n";
    cout << "\nFlashCard 3 cards :\n";
    achievement4(getTime4(),getLoop4());
    cout << "Best score : Time : " << getTime4() << " | Loop trial : " << getLoop4() << "\n";
    cout << "\nWord Ladder : \n";
    achievement5(getTime5());
    cout << "Best score : Time : " << getTime5() << "\n";
    enterPressedProfile();
    cout << "\nHangman : \n";
    achievement6(getTrial6(),getTime6());
    cout << "Best score : Trial : " << getTrial6() << " | Time : " << getTime6() << "\n";
}
void Profile::howToPlay() const {
    std::ifstream file("instruction.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << "instruction.txt" << std::endl;
        return;
    }
    std::string fileContents;    // hold all the file data
    std::string line;

    while (std::getline(file, line)) {
        fileContents += line + '\n';
    }
    file.close();
    std::vector<std::string> game;
    std::istringstream iss(fileContents);
    std::string portion;

    while (std::getline(iss, portion, '|')) {
        game.push_back(portion);
    }
    while(true) {
        clearProfileScreen();
        cout << "Select the game instructions\n";
        cout << "1.Multiple choice question\n";
        cout << "2.flashcard game\n";
        cout << "3.word puzzle\n";
        cout << "4.flashcard 3 cards\n";
        cout << "5.Word Ladder\n";
        cout << "6.Hangman\n";
        cout << "q to back\n";
        string input;
        cin >> input;
        clearProfileScreen();
        if(input=="1") cout << game[0];
        else if(input=="2") cout << game[1];
        else if(input=="3") cout << game[2];
        else if(input=="4") cout << game[3];
        else if(input=="5") cout << game[4];
        else if(input=="6") cout << game[5];
        else if(input=="q") break;
        else                cout << "Invalid input.Please try numbers(1-6) or q to back\n";
        enterPressedProfile();
    }
}
// achievement part
void Profile::achievement1(short int correct,short int time) const {
    if(time==0){
        cout << "RANK : " << "NULL\n";
        return;
    }
    if(correct>0 && correct<=10){
        cout << "RANK : Bronze ";
    }
    else if(correct>10 && correct <=15){
        cout << "RANK : Silver ";
    }
    else if(correct>15 && correct<19){
        cout << "RANK : Diamond ";
    }
    else if(correct>=19 && correct<=20){
        cout << "RANK : Platinum ";
    }
    if(time>=30) cout << "I\n";
    else if(time>=15 && time<30) cout << "II\n";
    else if(time>0 && time<15) cout << "III\n"; 
}
void Profile::achievement2(short int time,short int loop) const {
    if(time==0) cout << "RANK : NULL\n";
    if(time>=20)    cout << "RANK : Bronze\n";
    else if(time>=15 && time<20)    cout << "RANK : Silver ";
    else if(time>=10 && time<15)    cout << "RANK : Platinum ";
    else if(time>=5 && time<10)     cout << "RANK : Diamond ";
    else if(time>=1 && time<5)      cout << "RANK : Legend ";
    if(loop==0) cout << "II\n";
    else        cout << "I\n";

}
void Profile::achievement3(short int time) const {
    if(time==0) cout << "RANK : NULL\n";
    if(time>30) cout << "RANK : Bronze\n";
    else if(time>=20 && time<30) cout << "RANK : Silver\n";
    else if(time>=10 && time<20) cout << "RANK : Platinum\n";
    else if(time>=5 && time<10)  cout << "RANK : Diamond\n";
    else if(time>=1 && time<5)   cout << "RANK : Legend\n";
    
}
void Profile::achievement4(short int time,short int loop) const {
    if(time==0){ 
        cout << "RANK : NULL\n";
        return;
    }
    if(time>=20)                    cout << "RANK : Bronze ";
    else if(time>=15 && time<20)    cout << "RANK : Silver ";
    else if(time>=10 && time<15)    cout << "RANK : Platinum ";
    else if(time>=5 && time<10)     cout << "RANK : Diamond ";
    else if(time>=1 && time<5)      cout << "RANK : Legend ";
    int i=0;
    while(i++ < 3 - loop) cout << "I";
    cout << "\n";
}
void Profile::achievement5(short int time) const {
    if(time==0) cout << "RANK : NULL\n";
    if(time>=20) cout << "RANK : Bronze\n";
    else if(time>=10 && time<20) cout << "RANK : Silver\n";
    else if(time>=8 && time<10)  cout << "RANK : Platinum\n";
    else if(time>=5 && time<8)   cout << "RANK : Diamond\n";
    else if(time>=1 && time<5)   cout << "RANK : Legend\n";
}
void Profile::achievement6(short int trial,short int time) const {
    if(time==0){
        cout << "RANK : NULL\n";
        return;
    }
    if(trial==1) cout << "RANK : Bronze ";
    else if(trial>=2 && trial<=3) cout << "RANK : Silver ";
    else if(trial>=4 && trial<=5) cout << "RANK : Platinum ";
    else if(trial>=6 && trial<=8) cout << "RANK : Diamond ";
    else if(trial>=9 && trial<=10) cout << "RANK : Legend ";
    if(time>30) cout << "I\n";
    else if(time>=10 && time<=30) cout << "II\n";
    else cout << "III\n";
}