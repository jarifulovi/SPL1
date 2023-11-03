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
#include<queue>
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
void enterPress() {
    cout << "\nPress Enter to continue..." << endl;
    cin.ignore(); // Ignore any previous newline character
    cin.get();    // Wait for Enter key
}
void display_card(const vector<string>& eng,const vector<string>& ban,const int& curr_eng,const int& curr_ban){
    clearScreen();
    int ban_len = ban[curr_ban].size();
    int eng_len = eng[curr_eng].size();
    cout << " _________________     _________________\n";
    cout << "|                 |   |                 |\n";
    cout << "|     CARD A      |   |     CARD B      |\n";
    cout << "|                 |   |                 |\n";
    cout << "|                 |   |                 |\n";
    cout << "|                 |   |                 |\n";
    cout << "|   "<< eng[curr_eng];
    for(int i=0;i<14-eng_len;i++) cout << " "; cout << "|   ";
    cout << "|   "<< ban[curr_ban];
    for(int i=0;i<14-ban_len;i++) cout << " "; cout << "|\n";
    cout << "|                 |   |                 |\n";
    cout << "|_________________|   |_________________|\n";
    cout << "..........................................\n";
    cout << "curr indices : " << curr_eng+1 << "  " << curr_ban+1 << endl;
    cout << "cards        : " << eng.size() << "  " << ban.size() << endl;
    cout << "when match press s\n";
    cout << "press A/a for next eng card or B/b for next ban card\n";
}
void display_card3(const vector<string>& eng,const vector<string>& ban,const vector<string>& pot,const int& curr_eng,const int& curr_ban,const int& curr_pot){
    clearScreen();
    int ban_len = ban[curr_ban].size();
    int eng_len = eng[curr_eng].size();
    int pot_len = pot[curr_pot].size();
    cout << " _________________     _________________     _________________\n";
    cout << "|                 |   |                 |   |                 |\n";
    cout << "|     CARD A      |   |     CARD B      |   |     CARD  C     |\n";
    cout << "|                 |   |                 |   |                 |\n";
    cout << "|                 |   |                 |   |                 |\n";
    cout << "|                 |   |                 |   |                 |\n";
    cout << "|   "<< eng[curr_eng];
    for(int i=0;i<14-eng_len;i++) cout << " "; cout << "|   ";
    cout << "|   "<< pot[curr_pot];
    for(int i=0;i<14-pot_len;i++) cout << " "; cout << "|   ";
    cout << "|   "<< ban[curr_ban];
    for(int i=0;i<14-ban_len;i++) cout << " "; cout << "|\n";
    cout << "|                 |   |                 |   |                 |\n";
    cout << "|_________________|   |_________________|   |_________________|\n";
   
    cout << "when match press s\n";
    cout << "press A/a for next A card or B/b for B card or C/c for next C card\n";
    cout << "curr indices : " << curr_eng+1 << "  " << curr_pot+1 << "  " << curr_ban+1 << endl;
    cout << "cards        : " << eng.size() << "  " << pot.size() << "  " << ban.size() << endl;
}
// Custom sleep function that sleeps for the specified milliseconds
void sleep(int milliseconds) {
    clock_t start_time = clock();  // Get the starting time

    // Loop until the desired time has passed
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000) {
        // Do nothing (just wait)
    }
}
void display_puzzle(char puzzle[row][col]) {
    cout << "   ---------------------------------------------\n";
    cout << "   ------------------PUZZLE---------------------\n";
    cout << "   ---------------------------------------------\n\n";
    cout << " **************************************************\n";
    for(int i=0;i<10;i++)
    {
        cout << "|";
        for(int j=0;j<10;j++)
        {
          cout<<" ["<<puzzle[i][j] << "] ";
          sleep(50);
        }
        cout << "|\n";
    }
    cout << " **************************************************\n";
}
void display_hangman_steps(Word selectedWord,short int i,string& dash,short int trial) {
    string answer = selectedWord.getWord();
    cout << "Hint for step " << i+1 << " :\n";
    if(i==0){
        cout << "Meaning : " << selectedWord.getMeaning() << "\n";
        cout << "Parts of speech : " << selectedWord.getPartOfSpeech() << "\n";
    }
    else if(i==1){
        short int pos1=0,pos2;
        srand(time(0));
        short int length = answer.size();
        pos2 = rand()%(length-1) + 1;
        dash[pos1] = answer[pos1];
        dash[pos2] = answer[pos2];
    }
    else if(i==2) {
        cout << "Parts of speech : " << selectedWord.getPartOfSpeech() << "\n";
    }
    cout << "The hidden word : " << dash << "\n";
    cout << "Trial remaining : " << trial+1 << "\n";
    cout << "\nThe hidden word is : " << answer << "\n";
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
Word Words::generateRandomWord() const {
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

void Words::vocabularyTest(Profile& myprofile) const {
    char userInput;
    short int iteration = 10,correct_ans=0;
    vector<Word> temp(wordList);
    auto start = std::chrono::high_resolution_clock::now();
    do {
        if(!iteration){
            clearScreen();
            cout << "Congratulation you won!\n";
            enterPress();
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
                correct_ans++;
            } else {
                cout << "Incorrect. The correct meaning of \"" << correctAnswer.getWord() << "\" is \"" << correctAnswer.getMeaning() << "\"." << endl;
            }
        } 
        else {
            cout << "Invalid input. Please enter 1, 2, 3, 4, or 'q' to quit." << endl;
        }
       
        // Prompt for the next question
        enterPress();
        
    } while (userInput != 'q'&& iteration--);

    if(iteration<1){ 
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        if(myprofile.getTime1()==0||correct_ans>=myprofile.getCorrect1()){
            if(correct_ans==myprofile.getCorrect1()){
                if(myprofile.getTime1()>(static_cast<short int>(duration.count())))
                    myprofile.setTime1(static_cast<short int>(duration.count()));
            }
            else{
                myprofile.setCorrect1(correct_ans);
                myprofile.setTime1(static_cast<short int>(duration.count()));
            }
        }
    }
}
bool Words:: flashcard(Profile& myprofile) const {
    bool result = true;
    short int loop = 0;
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
    auto start = std::chrono::high_resolution_clock::now();
    while(!engWord.empty() && !banWord.empty()){
        clearScreen();
        display_card(engWord,banWord,curr_eng,curr_ban);    // doesn't need now
        cin >> input;

        if(input=="A"||input=="a"){
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
                enterPress();
                break;
            }
        }
       
        else{
            cout << "Invalid input please enter e/E or b/B or s\n";
            enterPress();
        }
        if(curr_eng>engWord.size()-1||curr_ban>engWord.size()-1){
            curr_eng = 0;
            curr_ban = 0;
            loop++;
        }
        if(loop>1) {
            cout << "No loop left\n";
            enterPress();
            return false;
        }
    }
    if(result){ 
        clearScreen();
        cout << "congrats you won!\n";
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        if(myprofile.getTime2()==0 || myprofile.getTime2()>=(static_cast<short int>(duration.count()))){
            if(myprofile.getTime2()==(static_cast<short int>(duration.count()))){
                if(myprofile.getLoop2()>loop)
                    myprofile.setLoop2(loop);
            }
            else {
                myprofile.setTime2(static_cast<short int>(duration.count()));
                myprofile.setLoop2(loop);
            }
        }
        enterPress();
    }
    return result;
}
bool Words::flashcard3(Profile& myprofile) const {
    bool result = true;
    vector<Word> templist(wordList);  
    string input;
    fisherYatesShuffle(templist);
    vector<Word> cards = getUniqueWordlist(templist,5);
    vector<string> engWord,banWord,part_of_speech;
    vector<tri> mappedlist;
    for(const Word& card : cards){
        string curr_engWord = card.getWord();
        string curr_banWord = card.getMeaning();
        string curr_pot = card.getPartOfSpeech();
        engWord.push_back(curr_engWord);
        banWord.push_back(curr_banWord);
        part_of_speech.push_back(curr_pot);

        tri temp(curr_engWord,curr_banWord,curr_pot);
        mappedlist.push_back(temp);
    }
    fisherYatesShuffle(banWord);
    fisherYatesShuffle(part_of_speech);
    short int curr_eng=0,curr_ban=0,curr_pot=0,ind=0;
    short int loop = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while(!engWord.empty() && !banWord.empty() && !part_of_speech.empty()){
        clearScreen();
        display_card3(engWord,banWord,part_of_speech,curr_eng,curr_ban,curr_pot);
	cout << "\neng : " << mappedlist[curr_eng].a << " ban : " << mappedlist[curr_eng].b << " pot : " << mappedlist[curr_eng].c << "\n";
        cout << "Enter your answer : ";
        cin >> input;
        if(input=="A"||input=="a"){
            // go to next eng string from the eng vector
            curr_eng++;
        }
        else if(input=="C"||input=="c"){
            // go to next ban string from the vector
            curr_ban++;
        }
        else if(input=="B"||input=="b"){
            // go to next pot string from the vector
            curr_pot++;
        }
	
        else if(input=="s"||input=="S"){
            if(mappedlist[curr_eng].b==banWord[curr_ban] && mappedlist[curr_eng].c==part_of_speech[curr_pot]){
                // remove eng and ban from the string vector
                engWord.erase(engWord.begin() + curr_eng);
                banWord.erase(banWord.begin() + curr_ban);
                part_of_speech.erase(part_of_speech.begin() + curr_pot);
                mappedlist.erase(mappedlist.begin() + curr_eng);
                if(curr_eng==engWord.size()) curr_eng--;
                if(curr_ban==banWord.size()) curr_ban--;
                if(curr_pot==part_of_speech.size()) curr_pot--;
            }
            else{ 
                cout << "Wrong ans you lost!\n";
                result = false;
                enterPress();
                break;
            }
        }
        else{
            cout << "Invalid input please enter A/a or B/b or or C/c or s\n";
            enterPress();
        }
        if(curr_eng>engWord.size()-1||curr_ban>engWord.size()-1||curr_pot>part_of_speech.size()-1){
            curr_eng = 0;
            curr_ban = 0;
            curr_pot = 0;
            loop++;
        }
        if(loop>2){
            cout << "No loop left\n";
            enterPress();
            return false;
        }
    }
    if(result){
        cout << "congrats you won!\n";
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        if(myprofile.getTime4()==0 || myprofile.getTime4()>(static_cast<short int>(duration.count()))){
            if(myprofile.getTime4()==(static_cast<short int>(duration.count()))){
                if(myprofile.getLoop4()>loop)
                    myprofile.setLoop4(loop);
            }
            else {
                myprofile.setTime4(static_cast<short int>(duration.count()));
                myprofile.setLoop4(loop);
            }
        }
        enterPress();
    }

    return result;

}
bool Words::isWordList(const string &targetWord) const
{
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
    
    if(target[0]>='A'&&target[0]<='Z') target[0] += 32;

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



bool Words::wordpuzzle(Profile& myprofile) const{
    clearScreen();
    bool result = true;
    Word placed_word = generateRandomWord();
    while(true){
        if(placed_word.getWord().size()<8||placed_word.getWord().size()>2) break;
        placed_word = generateRandomWord();
    }
    string ans = placed_word.getSmallLetter();
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
    display_puzzle(puzzle);
    cout << "The meaning : " << placed_word.getMeaning() << "\n";
    cout << "Find the word in the puzzle(word length should be more than 2)\n\n";
    string input;
    auto start = std::chrono::high_resolution_clock::now();
    cout << "Enter you answer : ";
    cin >> input;
    if(input==ans){
        cout << "Wow! you found the word\n";
        enterPress();
    }
    else if(isWordList(input)){
        vector<vector<char>> vec = convertCharArrayToVector(puzzle);
        if(doesWordExist(vec,input,row,col)){
            cout << "Wow! you found the other word\n";
            enterPress();
        }
        else{
            cout << "Sorry wrong answer with valid word\n";
            result = false;
            enterPress();
        }
    }
    else {
        cout << "Sorry wrong answer\n";
        result = false;
        enterPress();
    }
    if(result){
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        if(myprofile.getTime3()==0 || myprofile.getTime3()>(static_cast<short int>(duration.count()))){
            myprofile.setTime3(static_cast<short int>(duration.count()));
        }
    }
    return result;
}
// word ladder game part

vector<std::pair<std::string, std::string>> Words::readWordPairsFromFile() const {
    std::vector<std::pair<std::string, std::string>> wordPairs;
    std::ifstream file("wordpair.txt");

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word1, word2;

        if (std::getline(iss, word1, ',') && std::getline(iss, word2)) {
            wordPairs.emplace_back(word1, word2);
        } else {
            std::cerr << "Invalid line format in the file: " << line << std::endl;
        }
    }

    file.close();
    return wordPairs;
}

bool Words::isAdjacent(const std::string& word1, const std::string& word2) const {
    int diffCount = 0;
    for (size_t i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i])
            diffCount++;
        if (diffCount > 1)
            return false;
    }
    return diffCount == 1;
}

std::vector<std::string> Words::findPathWords(const std::string& start_word, const std::string& end_word) const {
    std::vector<std::string> path_words;
    std::queue<std::vector<std::string>> q;
    q.push({start_word});

    while (!q.empty()) {
        std::vector<std::string> current_path = q.front();
        q.pop();

        std::string current_word = current_path.back();
        if (current_word == end_word) {
            path_words = current_path;
            break;
        }

        for (const Word& word : wordList) {
            if (isAdjacent(current_word, word.getSmallLetter()) && isWordList(word.getSmallLetter())) {
                std::vector<std::string> new_path = current_path;
                new_path.push_back(word.getSmallLetter());
                q.push(new_path);
            }
        }
    }
    return path_words;
}

bool Words::wordLadder(Profile& myprofile) const {
    //clearScreen();
    //vector<Word> wordlist(wordList);
    string start_word,end_word;
    vector<string> path;
    vector<pair<string,string>> wordPair = readWordPairsFromFile();
    fisherYatesShuffle(wordPair);
    start_word = wordPair[0].first;
    end_word = wordPair[0].second;
    cout << "Start word : " << start_word << "\n";
    cout << "End word : " << end_word << "\n";
    char character;
    short int position;

    path = findPathWords(start_word,end_word);  
    cout << "********Word Ladder********\n";
    cout << "***************************\n";
    cout << "***************************\n\n";
//    cout << "Change " << start_word << " to " << end_word << "\n";
    enterPress();
    auto start = std::chrono::high_resolution_clock::now();
    do {
        clearScreen();
        std::cout << "Current word: " << start_word << "  -->  Target word : " << end_word;
        std::cout << "\n\nEnter character: ";
        std::cin >> character;
        std::cout << "Enter position (1 to " << start_word.length() << "): ";
        std::cin >> position;

        if (position < 1 || position > start_word.length()) {
            std::cout << "Invalid position!\n";
            enterPress();
            continue;
        }

        // Update the word based on user input
        start_word[position - 1] = character;

        // Check if the updated word matches any word in the path
        bool matched = false;
        for (const std::string& path_word : path) {
            if (start_word == path_word) {
                matched = true;
                break;
            }
        }

        if (!matched) {
            std::cout << "Invalid word. You lost!\n";
            enterPress();
            return false;
        }

        if (start_word == end_word) {
            std::cout << "You won!\n";
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
            if(myprofile.getTime5()==0 || myprofile.getTime5()>(static_cast<short int>(duration.count()))){
                myprofile.setTime5(static_cast<short int>(duration.count()));
            }
            enterPress();
            return true;
        }
    } while (true);
    return true;
}
// hangman game part
bool Words::hangman(Profile& myprofile) const {
    vector<Word> temp(wordList);
    vector<Word> selectedWords;
    fisherYatesShuffle(temp);
    selectedWords = getUniqueWordlist(temp,5);
    short int trial = 10;
    //display_hangman();
    cout << "Welcome to hangman.\n";
    sleep(2000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<3;i++){
        string input,dash = "";
        for(int j=0;j<selectedWords[i].getWordLength();j++) dash += std::to_string(1+i);
        while(trial--) {
            bool inValidInput = false;
            clearScreen();
            display_hangman_steps(selectedWords[i],i,dash,trial);
            cout << "Guess the word(use small letters) : ";
            cin >> input;
            if(input.size()>selectedWords[i].getWordLength()){
                cout << "\nInput size is larger than word size.\nTry again.\n";
                inValidInput = true;
            }
            for(char c : input){
                if (!(c >= 'a' && c <= 'z')){
                    cout << "Only use small letters.\n";
                    inValidInput = true;
                }
            }
            if(inValidInput){
                enterPress();
                trial++;
                continue;
            }
            for(int k=0;k<selectedWords[i].getWordLength()&&k<input.size();k++){
                if(selectedWords[i].getSmallLetter()[k]==input[k]){
                    dash[k] = input[k];
                }
            }
            if(selectedWords[i].getSmallLetter()==dash){
                cout << "Guessed the word.\n";
                enterPress();
                trial++;
                break;
            }
        }
        if(trial<1){
            cout << "Sorry no more trial\nYou lose!\n";
            enterPress();
            break;
        }
    }
    if(trial>0){
        clearScreen();
        cout << "Congrats You won!\n";
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        if(myprofile.getTime6()==0 || trial >= myprofile.getTrial6()){
            if(myprofile.getTrial6() == trial){
                if(myprofile.getTime6()>(static_cast<short int>(duration.count())))
                    myprofile.setTime6((static_cast<short int>(duration.count())));
            }
            else {
                myprofile.setTrial6(trial);
                myprofile.setTime6((static_cast<short int>(duration.count())));
            }
        }
        enterPress();
    }
    return true;
}