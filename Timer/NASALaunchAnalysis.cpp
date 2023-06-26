#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "TimeCode.h"

int main(){
    ifstream inFS;
    string currLine;
    string tmp;
    int idx, counter;
    TimeCode time;

    inFS.open("Space_Corrected.csv");                                                       //open file and ensure it opened
    if (!inFS.is_open()){
        return 1;
    }
    while(!inFS.eof()){                                                                     //read until empty
        getline(inFS, currLine);            
        idx = currLine.find("UTC");                                                         //get a line and find idx of "UTC" so we know line has a time
        if (idx != -1){                                                                     //ignore lines that do not have a time
            tmp = currLine.substr(idx - 6, 5);                                              //cut down to just the timecode
            time = time + TimeCode (stoi(tmp.substr(0, 2)), stoi(tmp.substr(3, 2)), 0);     //create timecode by cutting down substring to just hrs and mins
            counter++;                                                                      //keep count
        }
    }
    time = time / counter;                                                                  //get average

    cout << counter << " data points." << endl;                                             //output results
    cout << "AVERAGE: " << time.ToString() << endl;
    return 0;
}