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
	
	teachers_name[1].push_back("pvh");
	teachers_name[1].push_back("ajj");
	teachers_name[1].push_back("n2");
	teachers_name[1].push_back("bdz");
	teachers_name[1].push_back("gvk");
	teachers_name[1].push_back("ard");
	teachers_name[1].push_back("kcw");
	
	teachers_name[2].push_back("pp");
	teachers_name[2].push_back("dms");
	teachers_name[2].push_back("ad");
	teachers_name[2].push_back("new");
	
	teachers_name[3].push_back("pvj");
	teachers_name[3].push_back("vvb");
	teachers_name[3].push_back("rak");
	teachers_name[3].push_back("ars");
	
	teachers_name[4].push_back("pht");
	teachers_name[4].push_back("pc");
	teachers_name[4].push_back("new3");
	teachers_name[4].push_back("ppj");
	teachers_name[4].push_back("ps");
	
	teachers_name[5].push_back("ddk");
	teachers_name[5].push_back("rvb");
	teachers_name[5].push_back("sng");
	teachers_name[5].push_back("ssh");
	
	timetable se;
	cout<<"Setting variables\n";
	
	for(int i=1;i<6;i++) {
		if(!se.set_teachers_lab(i,teachers_count[i],teachers_name[i])) {
			cout<<"Unknown error\n";
			return 1;
		}
	}
	
	vector <int> t1;
	vector <string> t2;

	t1.push_back(1);
	t1.push_back(1);
	t1.push_back(1);
	t1.push_back(1);
	t2.push_back("sss");
	t2.push_back("smg");
	t2.push_back("gvk");
	t2.push_back("bdz");
	se.set_teachers_lec(6,t1,t2);
	
	t1.clear();
	t2.clear();
	t1.push_back(2);
	t1.push_back(1);
	t1.push_back(1);
	t2.push_back("ard");
	t2.push_back("ajj");
	t2.push_back("kcw");
	se.set_teachers_lec(7,t1,t2);
	
	t1.clear();
	t2.clear();
	t1.push_back(2);
	t1.push_back(1);
	t1.push_back(1);
	t2.push_back("sng");
	t2.push_back("ddk");
	t2.push_back("ssh");
	se.set_teachers_lec(8,t1,t2);

	t1.clear();
	t2.clear();
	t1.push_back(2);
	t1.push_back(1);
	t1.push_back(1);
	t2.push_back("rak");
	t2.push_back("ars");
	t2.push_back("vvb");
	se.set_teachers_lec(9,t1,t2);

	t1.clear();
	t2.clear();
	t1.push_back(2);
	t1.push_back(2);
	t2.push_back("dms");
	t2.push_back("pp");
	se.set_teachers_lec(10,t1,t2);

	t1.clear();
	t2.clear();
	t1.push_back(4);
	t2.push_back("ppj");
	se.set_teachers_lec(11,t1,t2);

	t1.clear();
	t2.clear();
	t1.push_back(1);
	t1.push_back(1);
	t1.push_back(1);
	t1.push_back(1);
	t2.push_back("ajj");
	t2.push_back("pvh");
	t2.push_back("new7");
	t2.push_back("bdz");
	se.set_teachers_lec(12,t1,t2);

	t1.clear();
	t2.clear();
	t1.push_back(1);
	t1.push_back(1);
	t1.push_back(1);
	t1.push_back(1);
	t2.push_back("vvb");
	t2.push_back("ars");
	t2.push_back("pvj");
	t2.push_back("rak");
	se.set_teachers_lec(13,t1,t2);

	t1.clear();
	t2.clear();
	t1.push_back(2);
	t1.push_back(1);
	t1.push_back(1);
	t2.push_back("sng");
	t2.push_back("ars");
	t2.push_back("rvb");
	se.set_teachers_lec(14,t1,t2);

	cout<<"Executing\n";
	se.execute();
	
	if(!se.success()) {
		cout<<"An error occured: \n"<<se.get_error_log();
		return 1;
	}
	
	for(int i=0;i<16;i++) {
		cout<<"Class "<<1+(i/4)<<" Batch "<<1+(i%4)<<"\n";
		for(int j=0;j<7;j++) {
			for(int k=0;k<6;k++) {
				cout<<se.get_batch_timetable(i,k,j)<<" ";
			}
			cout<<"\n";
		}
		cout<<"--------------------------------------------------------------------\n";
	}
	
	for(int i=0;i<se.get_total_teachers();i++) {
		cout<<se.get_teacher_name(i)<<": \n";
		for(int j=0;j<9;j++) {
			for(int k=0;k<6;k++) {
				cout<<se.get_teacher_timetable(i,k,j)<<" ";
			}
			cout<<"\n";
		}
		cout<<"-----------------------------------------------------\n";
	}
	
	for(int i=0;i<16;i++) {
		cout<<"Class "<<1+(i/4)<<" Batch "<<1+(i%4)<<"\n";
		for(int j=1;j<6;j++) {
			cout<<"Lab "<<j<<": "<<se.get_batch_lab_teacher(i,j)<<"\n";
		}
	}
	
	for(int i=0;i<4;i++) {
		cout<<"Class "<<i<<"\n";
		for(int j=6;j<15;j++) {
			cout<<"Lecture "<<j<<": "<<se.get_class_lec_teacher(i,j)<<"\n";
		}
	}
}
