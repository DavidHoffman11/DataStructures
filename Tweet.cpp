#include "Tweet.h"
#include "DSString.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "stdlib.h"
#include "Classify.h"

using namespace std;

Tweet::Tweet() {
    //leave out constructor definition because the default constructor does the job in this case
}

void Tweet::getSentiment(char** argv) {
    vector<int> tweetSentiment;
    vector<DSString> posWords;
    vector<DSString> negWords;

    Tweet t;
     //used to call a function later on

    char* buffer = new char[2048];
    int temp;
    DSString temp1;
    char* temp2;
    DSString temp3;

    ifstream myFile;
    myFile.open(argv[2]);


    if (myFile.is_open() == false) {
        cout << "Cannot open file train target" << endl;
        //checks to make sure file opens properly
    }

    myFile.getline(buffer, 500, '\n');
    //reads in first line of useless info
    int j = 0;

    while (j < 10000) {
        myFile.getline(buffer, 500, ',');

        myFile.getline(buffer, 500, ',');
        temp = atoi(buffer);
        tweetSentiment.push_back(temp);

        myFile.getline(buffer, 500, '\n');
        //because rowNum and tweetID are redundant info, we don't care about this data

        j++;
    }  //reads and stores info from training target file

    delete[] buffer;
    myFile.close();
    //must close file at the end of its usage to avoid memory leaks

    t.readTweet(tweetSentiment, argv);
}


void Tweet::readTweet(vector<int> tweetSentiment, char** argv) {
    vector<DSString> rowNum;
    vector<DSString> tweetID;
    vector<DSString> user;
    vector<DSString> negWords;
    vector<DSString> posWords;
    //creates a DSVector object for each type of data that must be read in
    char temp1[150];
    char* temp2 = new char[500];
    char* temp3 = new char[500];
    char* temp4 = new char[500];
    char* temp5 = new char[500];

    Classify x;
    //must create this object so that I can call the getSentiment function later on
    DSString cleanData;
    int temp;
    char* buffer = new char[2048];

    ifstream myFile;
    myFile.open(argv[1]);


    if (myFile.is_open() == false) {
        cout << "Cannot open file train data" << endl;
        //checks to make sure file opens properly
    }

    myFile.getline(buffer, 500, '\n');
      //reads first line of useless info

    int j = 0;

    while (j < 10000) {
        myFile.getline(temp1, 500, ',');
        DSString tempRowNum (temp1);
        rowNum.push_back(tempRowNum);
        //delete[] buffer;

        myFile.getline(temp2, 500, ',');
        DSString tempTweetID (temp2);
        tweetID.push_back(tempTweetID);
        //delete[] buffer;

        myFile.getline(temp3, 500, ',');
        //char* temp2;
        //temp2 = strtok(buffer, "#@!$%^&*()_+,./? ");
        DSString tempUser (temp3);
        user.push_back(tempUser);
        //delete[] buffer;

        myFile.getline(temp4, 500, '\n');
        temp5 = strtok(temp4, " \n");
        //DSString tempWord (temp5);
        bool check;

        for(int i = 0; i < strlen(temp5); i++) {
            temp5[i] = tolower(temp5[i]);
        }  //makes temp5 all lowercase

        DSString tempTweet (temp5);
        if(tweetSentiment[j] == 0) {
            if(tempTweet.getLength() >= 3) {
                negWords.push_back(tempTweet);
            }
        }
        else{
            if(tempTweet.getLength() >= 3) {
                posWords.push_back(tempTweet);
            }
        }

        while(temp5 != nullptr) {
            temp5 = strtok(nullptr, "!@#$%^&*()-_=+?? \n");
            //DSString tempWord1 (temp5);
            if(temp5 != nullptr) {
                if(strlen(temp5) <= 3){
                    continue;
                }  //jumps to the next word if word has less than 3 letters
            }

            if(tweetSentiment[j] == 0) {
                if(temp5 != nullptr) {
                    for(int i = 0; i < strlen(temp5); i++) {
                        temp5[i] = tolower(temp5[i]);
                    }  //makes temp5 all lowercase
                }

                for(int i = 0; i <= negWords.size(); i++) {
                    if(temp5 == nullptr) {
                        break;
                    }
                    else if(negWords[i] == temp5) {
                        check = true;
                        break;
                    }
                    else {
                        check = false;
                    }
                }  //checks if word is already in vector

                if(check == false) {
                    if(temp5 != nullptr) {
                        DSString tempTweet (temp5);
                        negWords.push_back(tempTweet);
                    }
                }  //adds word to vector if its not in there yet
            }

            else{
                if(temp5 != nullptr) {
                    for(int i = 0; i < strlen(temp5); i++) {
                        temp5[i] = tolower(temp5[i]);
                    }  //makes temp5 all lowercase
                }

                for(int i = 0; i <= posWords.size(); i++) {
                    if(temp5 == nullptr) {
                        break;
                    }
                    else if(posWords[i] == temp5) {
                        check = true;
                        break;
                    }
                    else {
                        check = false;
                    }
                }  //checks if word is already in vector

                if(check == false) {
                    if(temp5 != nullptr) {
                        DSString tempTweet (temp5);
                        posWords.push_back(tempTweet);
                    }
                }  //adds word to vector if its not in there yet
            }

        }  //breaking up the tweet into individual words and pushing the words into a vector
        j++;
        //continue;
          //returns to top of loop
    }  //reads in file and puts data in respective vectors

    x.runClassifier(posWords, negWords, argv);
    //sends in tweetID and tweet vectors as paramters to getSentiment function

    delete [] buffer;
    myFile.close();
    //must close file at the end of its usage to avoid memory leaks
}
