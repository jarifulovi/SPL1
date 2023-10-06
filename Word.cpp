#include "Words.h"
using namespace std;

Word::Word(const string& w, const string& m, const string& pos)
    : word(w), meaning(m), partOfSpeech(pos) {}

string Word::getWord() const {
    return word;
}

string Word::getMeaning() const {
    return meaning;
}

string Word::getPartOfSpeech() const {
    return partOfSpeech;
}
string Word::getSmallLetter() const {
    string smallLetter = word;
    if(word[0]>= 'A'&& word[0]<= 'Z'){
        smallLetter[0] += 32;  // change the first char big letter to small one
    }
    return smallLetter;
}