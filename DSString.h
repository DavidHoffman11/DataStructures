#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cstring>

class DSString {
private:
    char* data = new char[500];
    int length;
    char* substr = new char[500];

public:
    DSString();
    //default constructor
    DSString(const char*);
    DSString(const DSString&);
    //copy constructors
    ~DSString();
    //destructor

    DSString operator= (const char*);
    DSString operator= (const DSString&);
    DSString operator+ (const DSString&);
    DSString operator+= (const DSString&);
    bool operator== (const char*);
    bool operator== (const DSString&) const;
    bool operator< (const char*) const;
    bool operator< (const DSString&) const;
    bool operator> (const char*) const;
    bool operator> (const DSString&) const;
    char& operator[] (const int);
    //overloaded operators

    int size();
    int getLength();
    DSString substring(int a, int b);
    char* c_str();

    friend std::ostream& operator<< (std::ostream&, const DSString&);
};

#endif
