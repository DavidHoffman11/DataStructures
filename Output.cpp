#include "Output.h"
#include <fstream>
#include <iostream>
#include "DSString.h"
#include <vector>
#include "Classify.h"
#include <iomanip>
//need to include in order to use setprecision() function

using namespace std;

Output::Output() {
    //default constructor is all we need in this case
}

void Output::compare(vector<int>& ovSentiment, char** argv) {
    vector<int> cSentiment;
    vector<char> isCorrect;
    vector<long long int> tweetID;

    char* buffer = new char[2048];
    int temp;
    long long int temp1;

    ifstream myFile;
    myFile.open(argv[4]);
      //opening file


    if (myFile.is_open() == false) {
        cout << "Cannot open file test-target" << endl;
        //checks to make sure file opens properly
    }

    myFile.getline(buffer, 500, '\n');
    //reads first line of useless info

    while (myFile.eof() != true) {
        myFile.getline(buffer, 500, ',');

        myFile.getline(buffer, 500, ',');
        temp = atoi(buffer);
        cSentiment.push_back(temp);

        myFile.getline(buffer, 500, '\n');
        temp1 = atoll(buffer);
        tweetID.push_back(temp1);

        //because rowNum and tweetID are redundant info, we don't care about this data
    }

    delete[] buffer;
      //must delete dynamically allocated memory

    for (int i = 0; i < ovSentiment.size(); i++) {
        if (cSentiment[i] == ovSentiment[i]) {
            isCorrect.push_back('c');
        }  //if the outputed sentiment is the same as the real sentiment then isCorrect = c

        else {
            isCorrect.push_back('i');
        }  //if the outputed sentiment isn't the same as the real sentiment then isCorrect = i
    }

    myFile.close();

    printOutput(isCorrect, tweetID, argv);
}

void Output::printOutput(vector<char> isCorrect, vector<long long int> tweetID, char** argv) {
    double accuracy = 0;
    double numCorrect = 0;
    ofstream myFile;

    myFile.open(argv[5]);

    if (myFile.is_open() == false) {
        cout << "Cannot open file output.txt" << endl;
        //checks to make sure file opens properly
    }

    for (int i = 0; i < isCorrect.size(); i++) {
        if (isCorrect[i] == 'c') {
            numCorrect += 1;
        }
    }  //calculates the number of correctly accertained sentiments and stores that value in the variable numCorrect

    double temp = static_cast<double>(isCorrect.size());
      //must cast to a double in order to perform accurate math
    accuracy = numCorrect / temp;

    myFile << fixed << setprecision(3) << accuracy << endl;
    cout << fixed << setprecision(3) << accuracy << endl;

    for (int i = 0; i < isCorrect.size(); i++) {
        if (isCorrect[i] == 'c') {
            myFile << tweetID[i] << "," << isCorrect[i] << endl;
            cout << tweetID[i] << "," << isCorrect[i] << endl;
        }
    }  //sends all of the correct sentiments with their corresponding tweet IDs to the output file

    for (int i = 0; i < isCorrect.size(); i++) {
        if (isCorrect[i] == 'i') {
            myFile << tweetID[i] << "," << isCorrect[i] << endl;
            cout << tweetID[i] << "," << isCorrect[i] << endl;
        }
    }  //sends all of the incorrect sentiments with their corresponding tweet IDs to the output file after all the correct ones have been imported

    myFile.close();
}
