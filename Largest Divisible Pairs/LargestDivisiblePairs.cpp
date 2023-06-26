#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

//Vec toString
string vec_to_string(vector<int> v){
    if (v.size() == 0){
        return "[]";
    }
    string output = "[";
    for (size_t i = 0; i < v.size() - 1; i++){
        output.append(to_string(v.at(i)));
        output.push_back(' ');
    }
    output.append(to_string(v.back()));
    output.push_back(']');
    return output;
}

//Largest Divisible Pairs
//Recursion Complexity: There was a for loop with a nested for loop and a recursive call, the nested for loop is n^2 with n = size of 
//input vector, but with the recursive call it becomes n^x with x being all the different possibilities. Final Complexity: O(n^x^2).

//Dynamic Complexity: With dynamic we only have a nested for loop, the outer loop iterates over the whole input vector, and the
//inner loop will eventually iterate over the whole vector also. Final Complexity: O(n^2)
vector<int> largest_divisible_pairs(vector<int> input){
    //edge case 0
    if (input.size() == 0){
        return {};
    }

    sort(input.begin(), input.end());

    vector<int> sizes(input.size(), 1);
    vector<int> idxParent;
    int size;

    //initalize idxParent vector with values [0, 6]
    for (size_t i = 0; i < input.size(); i++){
        idxParent.push_back(i);
    }

    //populate sub-vectors
    for(size_t i = 0; i < input.size(); i++){
        //look at numbers only before current number in input vector
        for (int x = i - 1; x >= 0; x--){
            //check divisibility
            if(input.at(i) % input.at(x) == 0){
                size = 1 + sizes.at(x);
                //see if building a list with this number will result in biggest possible list. If so, make small number its parent
                if(size > sizes.at(i)){
                    sizes.at(i) = size;
                    idxParent.at(i) = x;
                }
            }
        }
    }    

    //get idx of number with greatest potential list size
    int maxidx = -1;
    int max = -1;
    for (size_t i = 0; i < sizes.size(); i++){
        if (sizes.at(i) > max){
            max = sizes.at(i);
            maxidx = i;
        }
    }

    //build answer using parent vector
    vector<int> ans;
    ans.push_back(input.at(maxidx));
    while (maxidx != idxParent.at(maxidx)){
        maxidx = idxParent.at(maxidx);
        ans.push_back(input.at(maxidx));
    }

    return ans;
}


int main(){
    vector<int> test = {2, 3};
    cout << "Input: " << vec_to_string(test) << endl;
    vector<int> answer = largest_divisible_pairs(test);
    cout << "Answer: " << vec_to_string(answer) << endl;
    return 0;
}