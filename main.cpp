#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Tweet.h"
#include "catch.hpp"

using namespace std;

int main(int argc, char **argv) {
    //catch tests run if there are no command line args
    if(argc == 1) {
        cout << "Running Catch Tests" << endl;
        //Catch::Session().run();
    }

    Tweet x;
    //must create a Tweet object in order to call Tweet member function readTweet

    x.getSentiment(argv);
    //argv parameter represents an array that stores each seperate command line arg

    return 0;
}