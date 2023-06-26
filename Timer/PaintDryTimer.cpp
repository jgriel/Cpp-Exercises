
#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;



//Drying Snap Shot
struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

//Get Time Remaining
long long int get_time_remaining(DryingSnapShot dss){
	return dss.timeToDry->GetTimeCodeAsSeconds();			//return seconds of timecode
}

//Get Sphere Surface Area
double get_sphere_sa(double rad){
	return 4 * M_PI * (rad * rad);							//formula for surface area of sphere
}

//Compute Time Code
TimeCode *compute_time_code(double surfaceArea){
	return new TimeCode (0, 0, surfaceArea);				//return new TimeCode with surface area as seconds
}

string drying_snap_shot_to_string(DryingSnapShot dss){		
	int remaining = get_time_remaining(dss) - (time(0) - dss.startTime);		//calculate true real time remaining
	if(remaining <= 0){															//check if drying time has expired
		return "";
	}else{
		TimeCode* tc = compute_time_code(remaining);							//remaining time TimeCode to be printed out
		string line = dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) time remaining: " + tc->ToString();
		delete tc;			//prevent memory leak
		return line;
	}
}

void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	// cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;

	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	char input = 'i';
	string typed;
	double radius;
	vector<DryingSnapShot> times;
	DryingSnapShot dss;

	while (input != 'Q'){
		dss.startTime = time(0);													//get time at beginning

		//print menu and filter input
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
		cin >> typed;
		input = typed.at(0);
		input = toupper(input);

		//Add input
		if(input == 'A'){
			//Get radius
			cout << "radius: ";
			cin >> radius;

			//Compute timeToDry and name, assign values 
			dss.timeToDry = compute_time_code(get_sphere_sa(radius));		
			dss.name = "Batch-" + to_string(rand() % 9999999999 + 1);
			
			//Add to master vector and output dss information
			times.push_back(dss);
			cout << dss.name << " will dry in: " << dss.timeToDry->ToString() << endl;
		
		//View input
		}else if(input == 'V'){
			//Make sure there are dss's to be viewed, otherwise do nothing and continue
			if (times.size() > 0){
				//Check every dss in master vector
				for(size_t i = 0; i < times.size(); i++){
					string tmp = drying_snap_shot_to_string(times.at(i));
					//delete pointers if drying time has expired and remove dss from master vector
					if (tmp == ""){
						delete times.at(i).timeToDry;
						times.erase(times.begin() + i);
				//otherwise display dss information
					}else{	
						cout << tmp << endl;
					}
				}
				cout << times.size() << " item(s) being tracked." << endl;
			}

		//Quit input
		}else if(input == 'Q'){
			//Delete dss's if ones currently exist in master vector, otherwise break out and end program
			if (times.size() > 0){
				//Delete pointers that exist and remove dss from master vector
				for (size_t i = 0; i < times.size(); i++){
					delete times.at(i).timeToDry;
					times.erase(times.begin() + i);
					i--;
				}
			}
			break;

		//Any other input than three cases above is invalid
		}else{
			cout << "Invalid input!" << endl;
		}
	}
	//tests();
	return 0;
}
