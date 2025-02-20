#include <iostream>
#include <string>
using namespace std;

#include "TimeCode.h"

//constructor function
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    //In case I want to prohibit that
    // if(min>60||sec>60){
    //     throw invalid_argument("out of range of minutes or seconds not allowed");
    // }

    t=ComponentsToSeconds(hr,min,sec);
    //Test:
    //cout<<"input:"<<hr<<" "<<min<<" "<<sec<<" output:"<<t<<endl;
}

void TimeCode::SetHours(unsigned int hours){
    //get old hours of time and reset it before set new one. Same for others
    int old_hour=GetHours();
    t-=ComponentsToSeconds(old_hour,0,0);

    t+=ComponentsToSeconds(hours,0,0);
}

void TimeCode::SetMinutes(unsigned int minutes){
    if(minutes>60){
        throw invalid_argument("out of range of minutes not allowed");
    }

    int old_min=GetMinutes();
    t-=ComponentsToSeconds(0,old_min,0);
    t+=ComponentsToSeconds(0,minutes,0);
}
void TimeCode::SetSeconds(unsigned int seconds){
    if(seconds>60){
        throw invalid_argument("out of range of seconds not allowed");
    }

    int old_sec=GetSeconds();
    t-=ComponentsToSeconds(0,0,old_sec);
    t+=ComponentsToSeconds(0,0,seconds);
}

void TimeCode::reset(){
    t=0;
}

//get hours or others by GetComponents();
unsigned int TimeCode::GetHours() const{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    return hr;
}
unsigned int TimeCode::GetMinutes() const{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    return min;
}
unsigned int TimeCode::GetSeconds() const{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    return sec;
}

//two core functions
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min,unsigned int& sec) const{
    hr=t/3600;
    min=(t%3600)/60;
    sec=(t%3600)%60;
}
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned int sec){
    return 3600*hr+60*min+sec;
}

string TimeCode::ToString() const{
    //Test:
    //cout<<"Tostring_t: "<<t<<endl;
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    string outcome="";
    //use to_string to transfer int to string: https://stackoverflow.com/questions/5590381/how-to-convert-int-to-string-in-c
    //I think I can import string module. It is not math, right? 
    outcome+=to_string(hr);
    outcome+=":";
    outcome+=to_string(min);
    outcome+=":";
    outcome+=to_string(sec);
    return outcome;
}

//reload Operators
TimeCode TimeCode::operator+(const TimeCode& other) const{
    TimeCode ot;
    ot.t=t+other.t;
    return ot;
}
TimeCode TimeCode::operator-(const TimeCode& other) const{
    TimeCode ot;
    if(t<other.t){
        throw invalid_argument("Negative outcome of subtraction not allowed");
    }
    ot.t=t-other.t;
    return ot;
}
TimeCode TimeCode::operator*(double a) const{
    TimeCode ot;
    ot.t=t*a;
    return ot;
}
TimeCode TimeCode::operator/(double a) const{
    TimeCode ot;
    ot.t=t/a;
    return ot;
}

bool TimeCode::operator==(const TimeCode& other) const{
    return t==other.t;
}
bool TimeCode::operator!=(const TimeCode& other) const{
    return t!=other.t;
}

bool TimeCode::operator<(const TimeCode& other) const{
    return t<other.t;
}
bool TimeCode::operator>(const TimeCode& other) const{
    return t>other.t;
}

bool TimeCode::operator<=(const TimeCode& other) const{
    return !(t>other.t);
}
bool TimeCode::operator>=(const TimeCode& other) const{
    return !(t<other.t);
}