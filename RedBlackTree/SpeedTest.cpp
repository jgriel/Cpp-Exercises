#include <cstdlib>
#include <ctime>
#include <iostream>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << duration << " seconds." << endl;
	for(int x = 0; x < 5; x++){
		int num = rand() % 3700000;
		clock_t start = clock();
		rbt.Remove(num);
		clock_t stop = clock();
		double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
		cout << "Removal of " << num << " took: " << duration << " seconds" << endl;
	}
	for(int x = 0; x < 5; x++){
		int num = rand() % 3700000 + 3700001;
		clock_t start = clock();
		rbt.Insert(num);
		clock_t stop = clock();
		double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
		cout << "Insertion of " << num << " took: " << duration << " seconds" << endl;
	}

	


	return 0;
}