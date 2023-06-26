#include "TimeCode.h"

using namespace std;

//Default & Variable Constructor
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    t = ComponentsToSeconds(hr, min, sec);

}

//Copy Constuctor
TimeCode::TimeCode(const TimeCode& tc){    
     t = (tc.t);
}

//SetHours
//NO ROLL OVER 
void TimeCode::SetHours(unsigned int hours){
    t = (t - (GetHours() * 3600) + (hours * 3600));
}

//SetMinutes
void TimeCode::SetMinutes(unsigned int minutes){
    //Check edge cases
    if (minutes >= 60){
        throw invalid_argument("Minutes cannot be greater than 60: " + to_string(minutes));
    }else{
        t = (t - (GetMinutes() * 60) + (minutes * 60));
    }
}

//SetSeconds
void TimeCode::SetSeconds(unsigned int seconds){
    //Check edge cases
    if (seconds >= 60){
        throw invalid_argument("Seconds cannot be greater than 60: " + to_string(seconds));
    }else{
        t = t - GetSeconds() + seconds;
    }
}

//Reset
void TimeCode::reset(){
    t = 0;
}

//GetHours
unsigned int TimeCode::GetHours() const{
    return t / (3600);
}

//GetMinutes
unsigned int TimeCode::GetMinutes() const{
    return (t % 3600) / 60;
}

//GetSeconds
unsigned int TimeCode::GetSeconds() const{
    return ((t % 3600) % 60);
}

//GetComponents
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec){
    hr = GetHours();
    min = GetMinutes();
    sec = GetSeconds();
}

//ComponentsToSeconds
//static
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    return (hr * (3600)) + (min * 60) + sec;
}

//ToString
string TimeCode::ToString() const{
    return to_string(GetHours()) + ":" + to_string(GetMinutes()) + ":" + to_string(GetSeconds());
}

// +
TimeCode TimeCode::operator+(const TimeCode& other) const{
    TimeCode temp;
    temp.t = t + other.t;
    return temp;
}

// -
TimeCode TimeCode::operator-(const TimeCode& other) const{
    TimeCode temp;
    if(t < other.t){
        throw invalid_argument("Cannot have negative time.");
    }else{
        temp.t = t - other.t;
    }
    return temp;
}

// *
TimeCode TimeCode::operator*(double a) const{
    TimeCode temp;
    if (a < 0){
        throw invalid_argument("Cannot have negative value.");
    }else{
        temp.t = t * a;
    }
    return temp;
}

// /
TimeCode TimeCode::operator/(double a) const{
    if (a <= 0){                                                    //Check for 0 case
        throw invalid_argument("Cannot divide by 0 or have negative value.");
    }else{
        TimeCode temp;
        temp.t = t / a;
        return temp;
    }
}
 // ==
bool TimeCode::operator== (const TimeCode& other) const{
    return t == other.t;
}
 // !=
bool TimeCode::operator!= (const TimeCode& other) const{
    return t != other.t;
}

// <
bool TimeCode::operator< (const TimeCode& other) const{
    return t < other.t;
}
// <=
bool TimeCode::operator<= (const TimeCode& other) const{
    return t <= other.t;
}

// >
bool TimeCode::operator> (const TimeCode& other) const{
    return t > other.t;
}

// >=
bool TimeCode::operator>= (const TimeCode& other) const{
    return t >= other.t;
}