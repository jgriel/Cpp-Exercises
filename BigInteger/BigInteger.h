#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <vector>
#include <iostream>

using namespace std;

class BigInteger {
    public:
        BigInteger(unsigned long long int number);
        BigInteger(string strNum);
        BigInteger(const BigInteger& origObject);
        string ToString() const;
    
    private:
        vector<int> *nums = new vector<int>;
        string vec_to_string(const vector<int> v);
};

#endif