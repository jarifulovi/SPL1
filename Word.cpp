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
