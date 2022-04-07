#ifndef CLASSIFY_H
#define CLASSIFY_H
#include <vector>
#include "DSString.h"

using namespace std;

class Classify
{
public:
    Classify();
    void getSentiment(vector<DSString>&);
    //analyzes train target and uses it to figure out positive/negative words
    void runClassifier(vector<DSString>&, vector<DSString>&, char**);
    //reads in test file and classifies sentiment of tweets
};

#endif // CLASSIFY_H
