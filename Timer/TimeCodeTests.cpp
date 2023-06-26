#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"

//Default Constructor
void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	cout << "Testing ToString()" << endl;
	cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}

//Component Constructor 
void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	
	//Default 
	TimeCode tc = TimeCode(0, 0, 0);
	cout << "Testing ToString()" << endl;
	cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	//Sanity Test
	TimeCode tc2 = TimeCode(12, 42, 33);
	cout << "tc2: " << tc2.ToString() << endl;
	assert(tc2.ToString() == "12:42:33");

	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	cout << "PASSED!" << endl << endl;
}

//Copy Constructor
void TestCopyConstructor(){
	cout << "Testing Copy Constructor" << endl;
	TimeCode tc1 = TimeCode(12, 43, 22);
	TimeCode tc2 = TimeCode(tc1);
	assert(tc1.ToString() == tc2.ToString());

	cout << "PASSED!" << endl << endl;

}

//Set Hours
void TestSetHours(){
	cout << "Testing Set Hours" << endl;
	
	//Sanity
	TimeCode tc1 = TimeCode(1, 54, 13);
	tc1.SetHours(24);
	assert(tc1.GetHours() == 24);

	//Lowest Possible
	TimeCode tc2 = TimeCode(324, 59, 35);
	tc2.SetHours(0);
	assert(tc2.GetHours() == 0);

	cout << "PASSED!" << endl << endl;
}

//Set Minutes
void TestSetMinutes(){
	cout << "Testing Set Minutes" << endl;
	
	//Highest Possible
	TimeCode tc1 = TimeCode(12, 34, 13);
	tc1.SetMinutes(59);
	assert(tc1.GetMinutes() == 59);

	//Overflow
	TimeCode tc2 = TimeCode(12, 12, 42);
	try{
		tc2.SetMinutes(62);
	}catch(invalid_argument& e){

	}

	cout << "PASSED!" << endl << endl;
}

//Set Seconds
void TestSetSeconds(){
	cout << "Testing Set Seconds" << endl;
	
	//Highest Possible
	TimeCode tc1 = TimeCode(12, 53, 43);
	tc1.SetSeconds(59);
	assert(tc1.GetSeconds() == 59);

	//Overflow
	TimeCode tc2 = TimeCode(12, 12, 42);
	try{
		tc2.SetSeconds(62);
	}catch(invalid_argument& e){

	}

	cout << "PASSED!" << endl << endl;
}

//Reset
void TestReset(){
	cout << "Testing Reset" << endl;
	TimeCode tc1 = TimeCode(12, 3, 3);
	tc1.reset();
	assert(tc1.ToString() == "0:0:0");

	cout << "PASSED!" << endl << endl;

}

//Get Hours
void TestGetHours(){
	cout << "Testing Get Hours" << endl;
	
	//Lowest
	TimeCode tc1 = TimeCode(0, 2, 4);
	unsigned int tmp = tc1.GetHours();
	assert(tmp == 0);

	//High Sanity
	TimeCode tc2 = TimeCode(23456, 2, 3);
	unsigned int tmp2 = tc2.GetHours();
	assert(tmp2 == 23456);

	cout << "PASSED!" << endl << endl;
}

//Get Minutes
void TestGetMinutes(){
	cout << "Testing Get Minutes" << endl;
	
	//Lowest
	TimeCode tc1 = TimeCode(21, 0, 4);
	unsigned int tmp = tc1.GetMinutes();
	assert(tmp == 0);

	//Highest
	TimeCode tc2 = TimeCode(12, 59, 3);
	unsigned int tmp2 = tc2.GetMinutes();
	assert(tmp2 == 59);

	//Overflow
	TimeCode tc3 = TimeCode(12, 601, 3);
	unsigned int tmp3 = tc3.GetMinutes();
	assert(tmp3 == 1);

	cout << "PASSED!" << endl << endl;
}

//Get Seconds
void TestGetSeconds(){
	cout << "Testing Get Seconds" << endl;
	
	//Lowest
	TimeCode tc1 = TimeCode(21, 23, 0);
	unsigned int tmp = tc1.GetSeconds();
	assert(tmp == 0);

	//Highest
	TimeCode tc2 = TimeCode(12, 1, 59);
	unsigned int tmp2 = tc2.GetSeconds();
	assert(tmp2 == 59);

	//Overflow
	TimeCode tc3 = TimeCode(12, 601, 121);
	unsigned int tmp3 = tc3.GetSeconds();
	assert(tmp3 == 1);

	cout << "PASSED!" << endl << endl;
}

//Get Components
void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	//Default
	TimeCode tc1 = TimeCode(0, 0, 0);
	tc1.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);

	//Regular values
	TimeCode tc2 = TimeCode(5, 2, 18);
	tc2.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);

	//Overflow
	TimeCode tc3 = TimeCode(12, 61, 61);
	tc3.GetComponents(h, m, s);
	assert(h == 13 && m == 2 && s == 1);	
	
	cout << "PASSED!" << endl << endl;
}

//Components To Seconds
void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t1 = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t1 == 11862);
	
	// Lowest/Default
	long long unsigned int t2 = TimeCode::ComponentsToSeconds(0, 0, 0);
	assert(t2 == 0);
	
	//High Sanity
	long long unsigned int t3 = TimeCode::ComponentsToSeconds(24, 59, 59);
	assert(t3 == 89999);

	cout << "PASSED!" << endl << endl;
}

//Addition
void TestAdd(){
	cout << "Testing Add" << endl;

	//Sanity
	TimeCode tc1 = TimeCode(3, 20, 20);
	TimeCode tc2 = TimeCode(5, 30, 30);
	TimeCode tc3 = tc1 + tc2;
	cout << tc3.ToString() << endl;
	assert(tc3.ToString() == "8:50:50");

	//Regrouping
	TimeCode tc4 = TimeCode(5, 40, 40);
	TimeCode tc5 = TimeCode(5, 30, 30);
	TimeCode tc6 = tc4 + tc5;
	cout << tc6.ToString() << endl;
	assert(tc6.ToString() == "11:11:10");

	cout << "PASSED!" << endl << endl;
}

//Subtraction
void TestSubtract(){
	cout << "Testing Subtract" << endl;
	
	//Regrouping
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	cout << tc3.ToString() << endl;
	assert(tc3.ToString() == "0:10:0");
	
	//Sanity
	TimeCode tc4 = TimeCode(12, 59, 59);
	TimeCode tc5 = TimeCode(11, 58, 58);
	TimeCode tc6 = tc4 - tc5;
	cout << tc6.ToString() << endl;
	assert(tc6.ToString() == "1:1:1");

	cout << "PASSED!" << endl << endl;
}

//Multiplication
void TestMult(){
	cout << "Testing Multiplication" << endl;
	
	//Zero
	TimeCode tc1 = TimeCode(1, 1, 1);
	TimeCode tc2 = tc1 * 0;
	cout << tc2.ToString() << endl;
	assert(tc2.ToString() == "0:0:0");

	//Sanity
	TimeCode tc3 = TimeCode(3, 30, 0);
	TimeCode tc4 = tc3 * 2;
	cout << tc4.ToString() << endl;
	assert(tc4.ToString() == "7:0:0");

	cout << "PASSED!" << endl << endl;
}

//Division
void TestDivision(){
	cout << "Testing Division" << endl;

	//Zero
	TimeCode tc1 = TimeCode(21, 40, 53);
	try{
		TimeCode tc2 = tc1 / 0;
	}catch(invalid_argument& e){

	}

	//Sanity
	TimeCode tc3 = TimeCode(20, 30, 10);
	TimeCode tc4 = tc3 / 2;
	cout << tc4.ToString() << endl;
	assert(tc4.ToString() == "10:15:5");

	cout << "PASSED!" << endl << endl;
}

//Equals
void TestEquals(){
	cout << "Testing Equals" << endl;
	
	//Equals
	TimeCode tc1 = TimeCode(2, 4, 4);
	TimeCode tc2 = TimeCode(2, 4, 4);
	bool tmp1 = tc1 == tc2;
	assert(tmp1 == true);

	//Not Equals
	TimeCode tc3 = TimeCode(3, 4, 6);
	bool tmp2 = tc3 == tc1;
	assert(tmp2 == false);

	cout << "PASSED!" << endl << endl;	
}

//Not Equals
void TestNotEquals(){
	cout << "Testing Not Equals" << endl;
	
	//Equals
	TimeCode tc1 = TimeCode(2, 4, 4);
	TimeCode tc2 = TimeCode(2, 4, 4);
	bool tmp1 = tc1 != tc2;
	assert(tmp1 == false);

	//Not Equals
	TimeCode tc3 = TimeCode(3, 4, 6);
	bool tmp2 = tc3 != tc1;
	assert(tmp2 == true);

	cout << "PASSED!" << endl << endl;	
}

//Less Than
void TestLess(){
	cout << "Testing Less Than" << endl;

	//Greater Than
	TimeCode tc1 = TimeCode(2, 4, 4);
	TimeCode tc2 = TimeCode(1, 1, 1);
	bool tmp1 = tc1 < tc2;
	assert(tmp1 == false);

	//Less Than
	TimeCode tc3 = TimeCode(5, 5, 5);
	bool tmp2 = tc1 < tc3;
	assert(tmp2 == true);

	cout << "PASSED!" << endl << endl;
}

//Less Equals
void TestLessEquals(){
	cout << "Testing Less Equals" << endl;

	//Greater Than
	TimeCode tc1 = TimeCode(2, 4, 4);
	TimeCode tc2 = TimeCode(1, 1, 1);
	bool tmp1 = tc1 <= tc2;
	assert(tmp1 == false);

	//Less Than
	TimeCode tc3 = TimeCode(5, 5, 5);
	bool tmp2 = tc1 <= tc3;
	assert(tmp2 == true);

	//Equal To
	TimeCode tc4 = TimeCode(2, 4, 4);
	bool tmp3 = tc1 <= tc4;
	assert(tmp3 == true);

	cout << "PASSED!" << endl << endl;
} 

//Greater Than
void TestGreater(){
	cout << "Testing Greater Than" << endl;

	//Greater Than
	TimeCode tc1 = TimeCode(2, 4, 4);
	TimeCode tc2 = TimeCode(1, 1, 1);
	bool tmp1 = tc1 > tc2;
	assert(tmp1 == true);

	//Less Than
	TimeCode tc3 = TimeCode(5, 5, 5);
	bool tmp2 = tc1 > tc3;
	assert(tmp2 == false);

	cout << "PASSED!" << endl << endl;
}

//Greater Equals
void TestGreaterEquals(){
	cout << "Testing Greater Equals" << endl;

	//Greater Than
	TimeCode tc1 = TimeCode(2, 4, 4);
	TimeCode tc2 = TimeCode(1, 1, 1);
	bool tmp1 = tc1 >= tc2;
	assert(tmp1 == true);

	//Less Than
	TimeCode tc3 = TimeCode(5, 5, 5);
	bool tmp2 = tc1 >= tc3;
	assert(tmp2 == false);

	//Equal To
	TimeCode tc4 = TimeCode(2, 4, 4);
	bool tmp3 = tc1 >= tc4;
	assert(tmp3 == true);

	cout << "PASSED!" << endl << endl;
}

int main(){
	
	//Run Tests
	TestDefaultConstructor();
	TestComponentConstructor();
	TestCopyConstructor();
	TestSetHours();
	TestSetMinutes();
	TestSetSeconds();
	TestReset();
	TestGetHours();
	TestGetMinutes();
	TestGetSeconds();
	TestGetComponents();
	TestComponentsToSeconds();
	TestAdd();
	TestSubtract();
	TestMult();
	TestDivision();
	TestEquals();
	TestNotEquals();
	TestLess();
	TestLessEquals();
	TestGreater();
	TestGreaterEquals();

	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
