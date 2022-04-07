#include "DSString.h"
#include <iostream>
#include <cstring>

using namespace std;

DSString::DSString() {
    data = nullptr;
}

DSString::DSString(const char* x) {
    this->length = strlen(x);
    this->data = new char[length+1];
    for(int i = 0; i < length; i++) {
        this->data[i] = x[i];
    }  //must take in data character by character
    data[length] = '\0';
      //adding a null terminator to the end of dsstring
}

DSString::DSString(const DSString& x) {
    this->length = strlen(x.data);
    this->data = new char[length+1];
    for(int i = 0; i < length; i++) {
        this->data[i] = x.data[i];
    }  //must take in data character by character
    data[length] = '\0';
    //adding a null terminator to the end of dsstring
}

DSString::~DSString() {
    if (data != nullptr) {
        delete[] data;
    }
    if (substr != nullptr) {
        delete[] substr;
    }
}

DSString DSString::operator= (const char* word) {

    if (data != nullptr) {
        delete[] data;
    }  //must ensure that data is empty before inputing a value

    data = new char [strlen(word-1)];

    strcpy(data, word);

    return data;
}

DSString DSString::operator= (const DSString& word) {
    length = strlen(word.data);

    this->data = new char[length + 1];
    strcpy(this->data,word.data);
    //copies string into a new string

    return *this;
}

DSString DSString::operator+ (const DSString& word) {

    DSString result;

    length = strlen(data) + strlen(word.data);

    result.data = new char[length+1];

    for(int i = 0; i < strlen(data); i++) {
        result.data[i] = data[i];
    }

    for(int j = strlen(word.data), i = 0; j < length; j++, i++) {

        this->data[j] = word.data[i];
    }

    return result;
}

DSString DSString::operator+= (const DSString& word) {


    length = strlen(data) + strlen(word.data);

    this->data = new char[length+1];


    for(int j = strlen(data), i = 0; j <= length; j++, i++) {

        this->data[j] = word.data[i];
    }  //concatenates string

    return data;
}

bool DSString::operator== (const char* word) {

    bool isSame = false;
    int wordlen;

    for (int i = 0; word[i] != '\0'; i++) {
        wordlen++;
    }

    if (length != wordlen) {
        return isSame;
    }  //returns false if the lengths are different

    for (int i = 0; i < wordlen + 1; i++) {
        if (data[i] == word[i]) {
            isSame = true;
        }  //checks if each element is the same

        else {
            isSame = false;
            return isSame;
        }  //if there are differing elements, returns false
    }

    return isSame;
}

bool DSString::operator== (const DSString& word) const {

    bool isSame = false;

    if (length != strlen(word.data)) {
        return isSame;
    }

    for (int i = 0; i < strlen(word.data) + 1; i++) {
        if (data[i] == word.data[i]) {
            isSame = true;
        }  //checks if eqch element of word is equal to the corresponding element in data

        else {
            isSame = false;
            return isSame;
        }

    }

    return isSame;
}

bool DSString::operator< (const char* word) const{

    bool isgreat;

    int wordlen;

    for (int i = 0; word[i] != '\0'; i++) {
        wordlen++;
    }

    for (int i = 0; i < length, i < wordlen; i++) {
        if (data[i] < word[i]) {
            isgreat = true;
        }  //checks to see if a string is longer than another string

        else if (data[i] == word[i]) {
            isgreat = false;
        }  //outputs false if the strings are the same length

        else {
            isgreat = false;
            return isgreat;
        }
    }

    return isgreat;
}

bool DSString::operator< (const DSString& word) const{

    bool isgreat;

    for (int i = 0; i < length, i < strlen(word.data); i++) {
        if (data[i] < word.data[i]) {
            isgreat = true;
        }  //checks to see if a string is longer than another string

        else if (data[i] == word.data[i]) {
            isgreat = false;
        }  //outputs false if strings are the same length

        else {
            isgreat = false;
            return isgreat;
        }
    }

    return isgreat;
}

bool DSString::operator> (const char* word) const{

    bool isgreat;

    int wordlen;

    for (int i = 0; word[i] != '\0'; i++) {
        wordlen++;
    }

    for (int i = 0; i < length, i < wordlen; i++) {
        if (data[i] < word[i]) {
            isgreat = false;
        }  //checks to see if a string is longer than another string

        else if (data[i] == word[i]) {
            isgreat = true;
        }  //outputs false if the strings are the same length

        else {
            isgreat = true;
            return isgreat;
        }
    }

    return isgreat;
}

bool DSString::operator> (const DSString& word) const{

    bool isgreat;

    for (int i = 0; i < length, i < strlen(word.data); i++) {
        if (data[i] < word.data[i]) {
            isgreat = false;
        }  //checks to see if a string is longer than another string

        else if (data[i] == word.data[i]) {
            isgreat = true;
        }  //outputs false if strings are the same length

        else {
            isgreat = true;
            return isgreat;
        }
    }

    return isgreat;
}

char& DSString::operator[] (const int x) {

    return data[x];
}  //returns a specific index of the DSString

int DSString::size() {

    return strlen(this->data);
}

int DSString::getLength() {
    return this->length;
}

DSString DSString::substring (int a, int b) {

    length = b-a;

    for (int i = a, j = 0; i < b + 1; i++, j++) {
        substr[j] = data[i];
    }  //creates substring
    substr[length] = '\0';
      //adds null terminator to the end of the substring
    return substr;
}

char* DSString::c_str() {

    char* word;
    word = data;

    return word;
}

std::ostream& operator<< (std::ostream& a, const DSString& b) {

    a << b.data;

    return a;
}
