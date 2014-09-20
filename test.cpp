#include <iostream>
#include <string>
#include "timetable.h"
#include <vector>
#include <sqlite3.h>
#include <stdio.h>
using namespace std;

int main() {
	vector <int> teachers_count[6];
	vector <string> teachers_name[6];
	
	
	for(int i=1;i<=5;i++) {
		sqlite3 *db;
		sqlite3_stmt * stmt;
		if (sqlite3_open("timetable.db", &db) == SQLITE_OK) {
			char i_buf[1024];
			sprintf(i_buf,"%d",i);
			string i_str(i_buf);
			string select_stmt = "select a.name,b.load from assignment b inner join teacher a on a.teacher_id=b.teacher_id where subject_id="+i_str+";";
			sqlite3_prepare( db, &select_stmt[0] , -1, &stmt, NULL );
			sqlite3_step( stmt );
			while( sqlite3_column_text( stmt, 0 ) ) {
				string t_name = string( (char *)sqlite3_column_text( stmt, 0 ));
				int t_count = atoi((char*)sqlite3_column_text( stmt, 1 ));
				teachers_name[i].push_back(t_name);
				teachers_count[i].push_back( t_count );
				sqlite3_step( stmt );
			}
		} else {
			cout << "Failed to open db\n";
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
	}
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

	se.add_lab_name(1,"A208");
	se.add_lab_name(1,"A209");
	
	se.add_lab_name(2,"C004");
	
	se.add_lab_name(3,"A209");
	se.add_lab_name(3,"A306");
	
	se.add_lab_name(4,"SSL1");
	se.add_lab_name(4,"SSL2");
	
	se.add_lab_name(5,"A202");
	se.add_lab_name(5,"A203");
	
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
			cout<<"Lab "<<j<<": "<<se.get_batch_lab_teacher(i,j)<<": "<<se.get_batch_lab_name(i,j)<<"\n";
		}
	}
	
	for(int i=0;i<4;i++) {
		cout<<"Class "<<i<<"\n";
		for(int j=6;j<15;j++) {
			cout<<"Lecture "<<j<<": "<<se.get_class_lec_teacher(i,j)<<"\n";
		}
	}
	
	for(int i=0;i<4;i++) {
		cout<<"\nClass: "<<i+1<<"\n";
		for(int j=0;j<7;j++) {
			for(int k=0;k<6;k++) {
				cout<<se.get_class_room(i,k,j)<<" ";
			}
			cout<<"\n";
		}
	}
}
