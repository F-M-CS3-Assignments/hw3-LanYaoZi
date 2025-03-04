#include <iostream>
#include <fstream>
using namespace std;

#include "TimeCode.h"

TimeCode get_time(string data){
	TimeCode outcome=TimeCode(0,0,0);
	//find position of UTC
	int UTC_index=data.find("UTC",0);
	//cout<<UTC_index<<endl;
	if(UTC_index==-1)//no found
	{
		// cout<<"nofound"<<endl;
		outcome=TimeCode(0, 0, -1);
	}
	else{
		string time=data.substr(UTC_index-6,5);
		//has time or not
		int time_index=time.find(":",0);
		if(time_index==-1){
			outcome=TimeCode(0, 0, -1);
		}else{
			//method of string to int:https://www.geeksforgeeks.org/stdstoi-function-in-cpp/
			int hour=std::stoi(time.substr(0,2));
			int min=std::stoi(time.substr(3,5));
			//cout<<hour<<"X"<<min<<endl;
			outcome=TimeCode(hour, min, 0);
		}
	}
	return outcome;
}


int main(){

	//a comment to show that I do read note#3

	//open file
	ifstream inFS;
	string reader;
	TimeCode total_time=TimeCode(0,0,0);
	int data_nums=0;
	
	// inFS.open("Space_Corrected_short.csv");
	inFS.open("Space_Corrected.csv");

	// open file error
	if (!inFS.is_open()) {
		cout << "Could not open file numFile.txt." << endl;
		return 1; 
	 }

	getline(inFS,reader);
	//read file until end
	 while(!inFS.fail()){
		TimeCode temp=get_time(reader);

		//print every lines
		// cout<<reader<<endl;
		// cout<<temp.ToString()<<endl;

		if(!(temp==TimeCode(0,0,-1))){
			total_time=total_time+temp;
			data_nums+=1;
		}

		//test for count all lines
		// total_time=total_time+temp;
		// data_nums+=1;
		getline(inFS,reader);
	 }
	
	 TimeCode avg_time=total_time/data_nums;
	 cout<<"data_nums: "<<data_nums<<endl;
	 cout<<"average time: "<<avg_time.ToString()<<endl;

	return 0;
}