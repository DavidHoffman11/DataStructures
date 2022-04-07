#ifndef OUTPUT_H
#define OUTPUT_H
#include <vector>

using namespace std;

class Output
{
public:
    Output();
      //default constructor
    void compare(vector<int>&, char**);
    //reads in target file and checks to see what assigned sentiments are actually correct
    void printOutput(vector<char>, vector<long long int>, char**);
    //prints the output..no shit
};

#endif // OUTPUT_H
