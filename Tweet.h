#ifndef TWEET_H
#define TWEET_H
#include "DSString.h"
#include <vector>

using namespace std;

class Tweet {
public:
    Tweet();
    void getSentiment(char**);
      //reads in training target file and stores info
    void readTweet(vector<int>, char**);
    //reads in tweets
    DSString clean(DSString&);
    //removes unimportant words such as and or the
};

#endif // TWEET_H
