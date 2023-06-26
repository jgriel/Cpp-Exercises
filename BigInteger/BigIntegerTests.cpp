#include "BigInteger.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(){
    BigInteger bigI = (1234567890);
    assert(bigI.ToString() == "1234567890");
    

    BigInteger bigI2 = (325344567654321);
    assert(bigI2.ToString() == "325344567654321");

    BigInteger bigIS("1234567");
    assert(bigIS.ToString() == "1234567");

    BigInteger bigCop(bigI);
    assert(bigCop.ToString() == "1234567890");

    return 0;
}