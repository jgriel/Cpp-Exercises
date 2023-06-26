#include <vector>
#include <string>

#include "BigInteger.h"

using namespace std;

BigInteger::BigInteger(unsigned long long int number){
    int size = to_string(number).length();                                  //get size before creating vector             
    for (int i = size - 1; i > -1; i--){                                    //add digits to vector through modularity 
        nums->insert(nums->begin(), number % 10);                           //starting at end of vector to keep order on insertion
        number /= 10;
    }  
}

BigInteger::BigInteger(string strNum){
    int size = strNum.length();
    for (int i = size - 1; i > -1; i--){
        nums->insert(nums->begin(), strNum.at(i) - '0');
    }

}

BigInteger::BigInteger(const BigInteger& origObject){
    for(size_t i = 0; i < origObject.nums->size(); i++){
        nums->push_back(origObject.nums->at(i));
    }
}

string BigInteger::ToString() const{
    string number;
    for (size_t i = 0; i < nums->size(); i++){
        char c = '0' + nums->at(i);
        number.push_back(c);
    }
    return number;
}

string vec_to_string(const vector<int> v){
    string num;                                                         
    for (size_t i = 0; i < v.size(); i++){                              //append to string for every value in vector
        num.append(to_string(v.at(i)));
    }
    return num;
}
