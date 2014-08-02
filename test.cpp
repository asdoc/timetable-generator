#include <iostream>
#include <string>
#include "timetable.h"
#include <vector>
using namespace std;

int main() {
	vector <int> teachers_count[6];
	vector <string> teachers_name[6];
	
	teachers_count[1].push_back(3);
	teachers_count[1].push_back(3);
	teachers_count[1].push_back(3);
	teachers_count[1].push_back(3);
	teachers_count[1].push_back(2);
	teachers_count[1].push_back(1);
	teachers_count[1].push_back(1);
	
	teachers_count[2].push_back(6);
	teachers_count[2].push_back(5);
	teachers_count[2].push_back(3);
	teachers_count[2].push_back(2);
	
	teachers_count[3].push_back(6);
	teachers_count[3].push_back(4);
	teachers_count[3].push_back(3);
	teachers_count[3].push_back(3);
	
	teachers_count[4].push_back(6);
	teachers_count[4].push_back(3);
	teachers_count[4].push_back(3);
	teachers_count[4].push_back(2);
	teachers_count[4].push_back(2);
	
	teachers_count[5].push_back(6);
	teachers_count[5].push_back(4);
	teachers_count[5].push_back(4);
	teachers_count[5].push_back(2);
	
	teachers_name[1].push_back("a");
	teachers_name[1].push_back("b");
	teachers_name[1].push_back("c");
	teachers_name[1].push_back("d");
	teachers_name[1].push_back("e");
	teachers_name[1].push_back("f");
	teachers_name[1].push_back("g");
	
	teachers_name[2].push_back("h");
	teachers_name[2].push_back("i");
	teachers_name[2].push_back("j");
	teachers_name[2].push_back("k");
	
	teachers_name[3].push_back("l");
	teachers_name[3].push_back("m");
	teachers_name[3].push_back("n");
	teachers_name[3].push_back("o");
	
	teachers_name[4].push_back("p");
	teachers_name[4].push_back("q");
	teachers_name[4].push_back("r");
	teachers_name[4].push_back("s");
	teachers_name[4].push_back("t");
	
	teachers_name[5].push_back("u");
	teachers_name[5].push_back("v");
	teachers_name[5].push_back("w");
	teachers_name[5].push_back("x");
	
	timetable se;
	for(int i=1;i<6;i++) {
		if(!se.set_teachers_data(i,teachers_count[i],teachers_name[i])) {
			cout<<"Unknown error\n";
			return 1;
		}
	}
	cout<<"Executing...\n";
	se.execute();
	
	for(int i=0;i<16;i++) {
		cout<<"Class "<<1+(i/4)<<" Batch "<<1+(i%4)<<"\n\n";
		for(int j=0;j<6;j++) {
			for(int k=0;k<5;k++) {
				cout<<se.get_batch_lab(i,k,j)<<" ";
			}
			cout<<"\n";
		}
		cout<<"\n";
	}
	
	for(int i=0;i<7;i++) {
		for(int j=0;j<8;j++) {
			for(int k=0;k<5;k++) {
				cout<<se.get_teacher_batch(1,i,k,j)<<" ";
			}
			cout<<"\n";
		}
		cout<<"\n";
	}
}
