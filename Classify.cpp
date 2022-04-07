#include "Classify.h"
#include "Tweet.h"
#include <vector>
#include "DSString.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "stdlib.h"
#include "Output.h"

using namespace std;

Classify::Classify() {
    //default constructor is sufficient in this case
}

void Classify::runClassifier(vector<DSString>& posWords, vector<DSString>& negWords, char** argv) {
    vector<DSString> rowNumTest;
    vector<DSString> tweetIDTest;
    vector<DSString> userTest;
    vector<DSString> tweetTest;
    //creates a DSVector object for each type of data that must be read in

    vector<int> sentiment;
      //stores the sentiment for every tweet

    int posCounter = 0;
    int negCounter = 0;
    int ovSentiment = 0;

    Output t;
    //must create Output object in order to call compare function later on

    char* buffer = new char[2048];
    char temp1[150];
    char* temp2 = new char[500];
    char* temp3 = new char[500];

    ifstream myFile;
    myFile.open(argv[3]);


    if (myFile.is_open() == false) {
        cout << "Cannot open file test data" << endl;
        //checks to make sure file opens properly
    }

    myFile.getline(buffer, 500, '\n');
    //reads first line of useless info

    int j = 0;

    while (j < 10000) {
        myFile.getline(temp1, 500, ',');
        DSString tempRowNum (temp1);
        rowNumTest.push_back(tempRowNum);
        //delete[] buffer;

        myFile.getline(temp2, 500, ',');
        DSString tempTweetID (temp2);
        tweetIDTest.push_back(tempTweetID);
        //delete[] buffer;

        myFile.getline(temp3, 500, ',');
        //char* temp2;
        //temp2 = strtok(buffer, "#@!$%^&*()_+,./? ");
        DSString tempUser (temp3);
        userTest.push_back(tempUser);
        //delete[] buffer;

        myFile.getline(buffer, 500, '\n');
        if(buffer != nullptr) {
            for(int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);
            }  //makes temp5 all lowercase
        }
        DSString tempTweet (buffer);
        tweetTest.push_back(tempTweet);

        j++;
    }  //reads in file and puts data in respective vectors

    delete[] buffer;

    int i = 0;

    while (i < tweetTest.size()) {
        DSString temp;
        DSString word;
          //stores each individual word
        temp = tweetTest[i];
        posCounter = 0;
        negCounter = 0;

        int z = 0;

        while(z < 7) {
            int y = 0;
            int j = 0;
            while (temp[j] != ' ') {
                j++;
            }  //runs until it hits a space, j becomes new delimeter

            word = temp.substring(y,j);
              //substring gets individual words from the tweet
            j = j+1;
            y = j;

            if (count(posWords.begin(), posWords.end(), word) != 0) {
                posCounter += 1;
            }  //if word if in the posWord vector, posCounter is incremented

            if (count(negWords.begin(), negWords.end(), word) != 0) {
                negCounter += 1;
            }  //if word if in the negWord vector, negCounter is incremented
            z++;
        }

        ovSentiment = posCounter - negCounter;
            //calculates overall sentiment for each tweet

        if (ovSentiment < 0) {
            sentiment.push_back(0);
        }

        else {
            sentiment.push_back(4);
        }  //pushes sentiment into a vector
        i++;
    }

    t.compare(sentiment, argv);
}
