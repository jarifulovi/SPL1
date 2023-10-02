#include "Words.h"
#include <fstream>
#include <sstream>
#include<iostream>
#include<ctime>
#include<unistd.h>
#include<chrono>
#include<random>
#include<map>
#include<vector>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

const short int row = 10;
const short int col = 10;
using namespace std;

void clearScreen() {
    system(CLEAR_SCREEN);
}
void display_card(string eng,string ban){
    cout << "            " << eng << "         " << ban << "\n";
    cout << "..........................................\n";
    cout << "..........................................\n";
    cout << "when match press enter\n";
    cout << "press e/E for next eng card or b/B for next ban card\n";
}
// Custom sleep function that sleeps for the specified milliseconds
void sleep(int milliseconds) {
    clock_t start_time = clock();  // Get the starting time

    // Loop until the desired time has passed
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000) {
        // Do nothing (just wait)
    }
}
vector<vector<char>> convertCharArrayToVector(char grid[row][col]) {
    vector<vector<char>> vec(row, vector<char>(col));

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            vec[i][j] = grid[i][j];
        }
    }

    return vec;
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
template<typename T>
void Words::fisherYatesShuffle(vector<T> &vec) const
{
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = vec.size() - 1; i > 0; --i) {
        uniform_int_distribution<int> distribution(0, i);
        int j = distribution(rng);

        // Swap elements at positions i and j
        T temp = vec[i];
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
bool Words:: flashcard() const {
    bool result = true; 
    vector<Word> templist(wordList);
    string input;
    fisherYatesShuffle(templist);
    vector<Word> cards = getUniqueWordlist(templist,5);
    vector<string> engWord,banWord;
    map<string,string> matching;

    for (const Word& card : cards) {
        engWord.push_back(card.getWord());
        banWord.push_back(card.getMeaning());
        matching[card.getWord()] = card.getMeaning();
    }
    fisherYatesShuffle(banWord);        //  fisherYates doesn't need specific type of vector
    short int curr_eng = 0,curr_ban = 0;

    while(!engWord.empty() && !banWord.empty()){
        display_card(engWord[curr_eng],banWord[curr_ban]);    // doesn't need now
        cout << "curr indices : " << curr_eng << "  " << curr_ban << endl;
        cout << "cards        : " << engWord.size() << "  " << banWord.size() << endl;
        cout << matching[engWord[curr_eng]] << "  " << banWord[curr_ban] << endl;
        cin >> input;

        if(input=="e"||input=="E"){
            // go to next eng string from the eng vector
            curr_eng++;
        }
        else if(input=="b"||input=="B"){
            // go to next ban string from the vector
            curr_ban++;
        }
        else if(input=="s"){                           // if pressed enter
            if(matching[engWord[curr_eng]]==banWord[curr_ban]){
                // remove eng and ban from the string vector
                engWord.erase(engWord.begin() + curr_eng);
                banWord.erase(banWord.begin() + curr_ban);

                if(curr_eng==engWord.size()) curr_eng--;
                if(curr_ban==banWord.size()) curr_ban--;
            }
         //   cout << "The first : " << matching[curr_ban].second << " and second : " << banWord[curr_ban]
            else{ 
                cout << "Wrong ans you lost!\n";
                result = false;
                break;
            }
        }
       
        else{
            cout << "Invalid input please enter e/E or b/B or enter\n";
        }
        if(curr_eng>engWord.size()-1||curr_ban>engWord.size()-1){
            cout << "you lost no cards on the deck\n";
            result = false;
            break;
        }
    }
    if(result) cout << "congrats you won!\n";
    return result;
}
bool Words::isWordList(const string& targetWord) const {
    // WordList is sorted alphabetically by word
    string modified_target = targetWord;
    int left = 0;
    int right = wordList.size() - 1;
    if (!modified_target.empty()) {
        modified_target[0] = toupper(modified_target[0]);  //  change the string according to dictionay strings
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;
        const string& currentWord = wordList[mid].getWord();

        if (currentWord == modified_target) {
            // Word with the given word found
            return true;
        } else if (currentWord < modified_target) {
            left = mid + 1;  // Search in the right half
        } else {
            right = mid - 1;  // Search in the left half
        }
    }
    return false;
}
// boggle algorithm part for checking if a string can be found in the grid or not
bool Words::isSafe(int i, int j, int row, int col, vector<vector<bool>>& visited) const {
    return (i >= 0 && i < row && j >= 0 && j < col && !visited[i][j]);
}

bool Words::findWordUtil(vector<vector<char>>& boggle, vector<vector<bool>>& visited, int i, int j, string& str, const string& target, int row, int col)  const {
    visited[i][j] = true;
    str += boggle[i][j];

    if (str == target) {
        return true;  // The target word is found
    }

    if (str.size() >= target.size()) {
        // The current prefix is longer than the target word, backtrack
        str.pop_back();
        visited[i][j] = false;
        return false;
    }

    int x, y;
    for (x = -1; x <= 1; x++) {
        for (y = -1; y <= 1; y++) {
            int row_new = i + x;
            int col_new = j + y;
            if (isSafe(row_new, col_new, row, col, visited)) {
                if (findWordUtil(boggle, visited, row_new, col_new, str, target, row, col)) {
                    return true;  // The target word is found in one of the directions
                }
            }
        }
    }

    // Not found in this path, backtrack
    str.pop_back();
    visited[i][j] = false;
    return false;
}

bool Words::doesWordExist(vector<vector<char>>& boggle, string target, int row, int col) const {
   
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    string str = "";

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (findWordUtil(boggle, visited, i, j, str, target, row, col)) {
                return true;  // The target word is found
            }
        }
    }

    return false;  // The target word is not found
}



bool Words::wordpuzzle() const{
    clearScreen();
    bool result = true;
    Word placed_word = generateRandomWord();
    while(true){
       
        if(placed_word.getWord().size()<=7) break;
        placed_word = generateRandomWord();
    }
    string ans = placed_word.getWord();
    char puzzle[row][col];
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            char c;
            int r;
            r= rand() % 26;   // generate a random number for char
            c= 'a' + r;            // Convert to a character from a-z
            puzzle[i][j]=c;
        }
    }
    // Generate random starting position for ans
    int startRow = rand() % (row - ans.size());
    int startCol = rand() % (col - ans.size());
    short placement = rand()%3;
    // Place ans in the puzzle grid vertically, horizontally, or diagonally
    for (int i = 0; i < ans.size(); i++) {
        if(placement==0)
        puzzle[startRow + i][startCol] = ans[i];  // Place vertically
        else if(placement==1)
        puzzle[startRow][startCol + i] = ans[i];  // Place horizontally
        else if(placement==2)
        puzzle[startRow + i][startCol + i] = ans[i];  // Place diagonally
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
          cout<<" "<<puzzle[i][j];
          sleep(50);
        }
        cout<<endl;
    }
    cout << "*******************************************\n";
    cout << "The meaning : " << placed_word.getMeaning() << "\n";
    cout << "Find the word in the puzzle(word length should be more than 2)\n";
    string input;
    cin >> input;
    if(input==ans){
        cout << "Wow! you found the word\n";
    }
    else if(isWordList(input)){
        vector<vector<char>> vec = convertCharArrayToVector(puzzle);
        if(doesWordExist(vec,input,row,col)){
            cout << "Wow! you found the word\n";
        }
        else{
            cout << "Sorry wrong answer with valid word\n";
            result = false;
        }
    }
    else {
        cout << "Sorry wrong answer\n";
        result = false;
    }
    return result;
}

