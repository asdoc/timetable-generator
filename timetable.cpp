#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include "timetable.h"
using namespace std;

timetable::timetable() {

	success_var = false;
	
	total_teachers=0;
	for(int i=0;i<16;i++) {
		for(int j=0;j<5;j++) {
			for(int k=0;k<7;k++) {
				batch[i][j][k]=0;
			}
		}
	}
	for(int i=0;i<4;i++) {
		labs_class_count[i]=0;
	}
	for(int i=1;i<=5;i++) {
		for(int j=0;j<5;j++) {
			for(int k=0;k<4;k++) {
				labs_occupied[i][j][k]=0;
			}
		}
	}
	for(int i=0;i<16;i++) {
		labs_remaining[i][0]=1;
		for(int j=1;j<6;j++) {
			labs_remaining[i][j]=j;
		}
	}
	labs_maxlimit[1]=2;
	labs_maxlimit[2]=1;
	labs_maxlimit[3]=2;
	labs_maxlimit[4]=2;
	labs_maxlimit[5]=2;
	
	lecs_maxlimit[6]=4;
	lecs_maxlimit[7]=4;
	lecs_maxlimit[8]=3;
	lecs_maxlimit[9]=3;
	lecs_maxlimit[10]=3;
	lecs_maxlimit[11]=1;
	lecs_maxlimit[12]=1;
	lecs_maxlimit[13]=1;
	lecs_maxlimit[14]=1;

	for(int i=0;i<60;i++) {
		for(int j=0;j<5;j++) {
			for(int k=0;k<8;k++) {
				teachers[i][j][k]=0;
			}
		}
	}
	for(int i=0;i<4;i++) {
		for(int j=0;j<15;j++) {
			lec_class_count[i][j]=0;
		}
	}
}

string timetable::batch_no_to_str(int batch_number) {
	string ans = "Batch";
	if(batch_number>16) ans="Class";
	if(batch_number==0) {
		ans = "       ";
	}
	else if(batch_number<10) {
		ans += "0";
		stringstream s;
		s << batch_number;
		ans += (string(s.str()));
	} else if(batch_number>16){
		ans += "0";
		stringstream s;
		s << (batch_number-16);
		ans += (string(s.str()));		
	} else {
		stringstream s;
		s << batch_number;
		ans += (string(s.str()));		
	}
	return ans;
}

string timetable::get_lab_name(int lab_number) {
	switch(lab_number) {
		case 0:
			return "         ";
		case 1:
			return "DSPSL    ";
		case 2:
			return "DEL      ";
		case 3:
			return "OSAL     ";
		case 4:
			return "SSL      ";
		case 5:
			return "MPAL     ";
		case 6:
			return "DS       ";
		case 7:
			return "DSPS     ";
		case 8:
			return "MPA      ";
		case 9:
			return "OSA      ";
		case 10:
			return "DELD     ";
		case 11:
			return "SS       ";
		case 12:
			return "DSPS PRL ";
		case 13:
			return "OSA PRL  ";
		case 14:
			return "MPA PRL  ";
	}
	return "";
}

void timetable::assign_sat() {
	int add_div;
	for(int i=0;i<4;i++) {
		for(int j=0;j<5;j++) {
			if(i<3) {
				batch[4*i][5][j]=batch[4*i][j][6];
				// TODO update teachers timetable
			}
			else {
				batch[4*i][5][j+1]=batch[4*i][j][0];
				// TODO update teachers timetable
			}
		}
	}
}

bool timetable::assign_lecs1(int lec_number, int teacher_index, int class_no){
	int add_div=0;
	if(class_no==3) add_div=1;
	/*
		Conditions:
		1. The teachers load may be filled
	*/
	if(lec_teachers_count[lec_number][teacher_index]==0) {
		/* if teacher's lectures load is filled */
		if(teacher_index==(lec_teachers_count[lec_number].size()-1)) {
			if(class_no<4) {
				/* no way to arrange all classes */
				return false;
			} else {
				return true;
			}
		} else {
			/* goto next teacher */
			return assign_lecs1(lec_number,teacher_index+1,class_no);
		}
	} else {
		/* teacher can be arranged to class class_no */
		vector <int> tmp_days;
		vector <int> tmp_slots;
		for(int i=0;i<5;i++) {
			for(int j=0;j<7;j++) {
				if(
					(teachers[lec_teachers_index[lec_number][teacher_index]][i][j+add_div]==0) &&
					(batch[4*class_no][i][j]==0)
					){
					tmp_days.push_back(i);
					tmp_slots.push_back(j);
				}
			}
		}
		/*
			iterate through all posible combinations in tmp_days and tmp_slots and arrange the next class for them
		*/
		for(int i=0;i<tmp_days.size();i++) {
			lec_teachers_count[lec_number][teacher_index]-=1;
			lec_class_count[class_no][lec_number]+=1;
		
			batch[4*class_no][tmp_days[i]][tmp_slots[i]]=lec_number;

			teachers[
					lec_teachers_index[lec_number][teacher_index]
				][tmp_days[i]][tmp_slots[i]+add_div] = (class_no+17);
				
			class_lec_teacher[class_no][lec_number] =
				lec_teachers_index[lec_number][teacher_index];
							
			/* end of updation of variables */
		
		
			/* check for the next class */
			if( assign_lecs1(lec_number,teacher_index, class_no+1) ) return true;
			else {
				/* rollback variables */

				lec_teachers_count[lec_number][teacher_index]+=1;
				lec_class_count[class_no][lec_number]-=1;

				batch[4*class_no][tmp_days[i]][tmp_slots[i]]=0;

				teachers[
						lec_teachers_index[lec_number][teacher_index]
					][tmp_days[i]][tmp_slots[i]+add_div] = 0;
					
				class_lec_teacher[class_no][lec_number] = -1 ;
			}
		}
	}
	return false;
}

bool timetable::assign_lecs3(int lec_number, int class_no){
	int add_div=0;
	if(class_no==3) add_div=1;
	vector <int> tmp_days;
	vector <int> tmp_slots;	
	for(int teacher_index=0;teacher_index<lec_teachers_count[lec_number].size();teacher_index++) {
		if(lec_teachers_count[lec_number][teacher_index]==0) continue;
		tmp_days.clear();
		tmp_slots.clear();
		for(int i=0;i<5;i++) {
			for(int j=0;j<7;j++) {
				if(
					(teachers[lec_teachers_index[lec_number][teacher_index]][i][j+add_div]==0) &&
					(batch[4*class_no][i][j]==0)
					){
					tmp_days.push_back(i);
					tmp_slots.push_back(j);
				}
			}
		}
		/*
			iterate through all posible combinations in tmp_days and tmp_slots and arrange the next class for them
		*/
		for(int i=0;i<tmp_days.size();i++) {
			for(int j=i+1;j<tmp_days.size();j++) {
				if(tmp_days[i]==tmp_days[j]) continue;
				for(int k=j+1;k<tmp_days.size();k++) {
					if(tmp_days[j]==tmp_days[k]) continue;
					/* start of updation of all variables */
					lec_teachers_count[lec_number][teacher_index]-=1;
					lec_class_count[class_no][lec_number]+=1;
					
					batch[4*class_no][tmp_days[i]][tmp_slots[i]]=lec_number;
					batch[4*class_no][tmp_days[j]][tmp_slots[j]]=lec_number;
					batch[4*class_no][tmp_days[k]][tmp_slots[k]]=lec_number;

					teachers[
							lec_teachers_index[lec_number][teacher_index]
						][tmp_days[i]][tmp_slots[i]+add_div] = (class_no+17);
					teachers[
							lec_teachers_index[lec_number][teacher_index]
						][tmp_days[j]][tmp_slots[j]+add_div] = (class_no+17);
					teachers[
							lec_teachers_index[lec_number][teacher_index]
						][tmp_days[k]][tmp_slots[k]+add_div] = (class_no+17);
						
					class_lec_teacher[class_no][lec_number] =
							lec_teachers_index[lec_number][teacher_index];
							
					/* end of updation of variables */
					
					/* check for the next class */
					if(class_no==3) {
						return true;
					}
					if( assign_lecs3(lec_number, class_no+1) ) return true;
					else {
						/* rollback variables */

						lec_teachers_count[lec_number][teacher_index]+=1;
						lec_class_count[class_no][lec_number]-=1;

						batch[4*class_no][tmp_days[i]][tmp_slots[i]]=0;
						batch[4*class_no][tmp_days[j]][tmp_slots[j]]=0;
						batch[4*class_no][tmp_days[k]][tmp_slots[k]]=0;

						teachers[
								lec_teachers_index[lec_number][teacher_index]
							][tmp_days[i]][tmp_slots[i]+add_div] = 0;
						teachers[
								lec_teachers_index[lec_number][teacher_index]
							][tmp_days[j]][tmp_slots[j]+add_div] = 0;
						teachers[
								lec_teachers_index[lec_number][teacher_index]
							][tmp_days[k]][tmp_slots[k]+add_div] = 0;
							
						class_lec_teacher[class_no][lec_number] = -1;
					}
				}
			}
		}
	}
	return false;
}


bool timetable::assign_lecs4(int lec_number, int class_no){
	int add_div=0;
	if(class_no==3) add_div=1;
	vector <int> tmp_days;
	vector <int> tmp_slots;	
	for(int teacher_index=0;teacher_index<lec_teachers_count[lec_number].size();teacher_index++) {
		if(lec_teachers_count[lec_number][teacher_index]==0) continue;
		tmp_days.clear();
		tmp_slots.clear();
		for(int i=0;i<5;i++) {
			for(int j=0;j<7;j++) {
				if(
					(teachers[lec_teachers_index[lec_number][teacher_index]][i][j+add_div]==0) &&
					(batch[4*class_no][i][j]==0)
					){
					tmp_days.push_back(i);
					tmp_slots.push_back(j);
				}
			}
		}
		/*
			iterate through all posible combinations in tmp_days and tmp_slots and arrange the next class for them
		*/
		for(int i=0;i<tmp_days.size();i++) {
			for(int j=i+1;j<tmp_days.size();j++) {
				if(tmp_days[i]==tmp_days[j]) continue;
				for(int k=j+1;k<tmp_days.size();k++) {
					if(tmp_days[j]==tmp_days[k]) continue;
					for(int l=k+1;l<tmp_days.size();l++) {
						if(tmp_days[k]==tmp_days[l]) continue;
						/* start of updation of all variables */
						lec_teachers_count[lec_number][teacher_index]-=1;
						lec_class_count[class_no][lec_number]+=1;
						
						batch[4*class_no][tmp_days[i]][tmp_slots[i]]=lec_number;
						batch[4*class_no][tmp_days[j]][tmp_slots[j]]=lec_number;
						batch[4*class_no][tmp_days[k]][tmp_slots[k]]=lec_number;
						batch[4*class_no][tmp_days[l]][tmp_slots[l]]=lec_number;

						teachers[
								lec_teachers_index[lec_number][teacher_index]
							][tmp_days[i]][tmp_slots[i]+add_div] = (class_no+17);
						teachers[
								lec_teachers_index[lec_number][teacher_index]
							][tmp_days[j]][tmp_slots[j]+add_div] = (class_no+17);
						teachers[
								lec_teachers_index[lec_number][teacher_index]
							][tmp_days[k]][tmp_slots[k]+add_div] = (class_no+17);
						teachers[
								lec_teachers_index[lec_number][teacher_index]
							][tmp_days[l]][tmp_slots[l]+add_div] = (class_no+17);
							
						class_lec_teacher[class_no][lec_number] =
							lec_teachers_index[lec_number][teacher_index];
						
						/* end of updation of variables */
						
						
						/* check for the next class */
						if(class_no==3) {
							return true;
						}
						if( assign_lecs4(lec_number, class_no+1) ) return true;
						else {
							/* rollback variables */

							lec_teachers_count[lec_number][teacher_index]+=1;
							lec_class_count[class_no][lec_number]-=1;

							batch[4*class_no][tmp_days[i]][tmp_slots[i]]=0;
							batch[4*class_no][tmp_days[j]][tmp_slots[j]]=0;
							batch[4*class_no][tmp_days[k]][tmp_slots[k]]=0;
							batch[4*class_no][tmp_days[l]][tmp_slots[l]]=0;

							teachers[
									lec_teachers_index[lec_number][teacher_index]
								][tmp_days[i]][tmp_slots[i]+add_div] = 0;
							teachers[
									lec_teachers_index[lec_number][teacher_index]
								][tmp_days[j]][tmp_slots[j]+add_div] = 0;
							teachers[
									lec_teachers_index[lec_number][teacher_index]
								][tmp_days[k]][tmp_slots[k]+add_div] = 0;
							teachers[
									lec_teachers_index[lec_number][teacher_index]
								][tmp_days[l]][tmp_slots[l]+add_div] = 0;

							class_lec_teacher[class_no][lec_number] = 0;
						}
					}
				}
			}
		}
	}
	return false;
}


bool timetable::assign_lab_teachers(int batch_number,int lab) {
	int add_div=1;
	if(batch_number<12) add_div=0;
	if(batch_number==16) {
		for(int j=0;j<lab_teachers_count[lab].size();j++) {
			if(lab_teachers_count[lab][j]!=0) return false;
		}
		return true;
	}
	
	vector <int> day_store;
	vector <int> slot_store;
	for(int i=0;i<5;i++) {
		for(int j=0;j<3;j++) {
			if(batch[batch_number][i][2*j+add_div]==lab) {
				day_store.push_back(i);
				slot_store.push_back(j);
			}
		}
	}
	for(int j=0;j<lab_teachers_count[lab].size();j++) {
		bool possible = true;
		for(int k=0;k<day_store.size();k++) {
			if(teachers[lab_teachers_index[lab][j]][day_store[k]][2*(slot_store[k]+add_div)]!=0) possible = false;
			if(lab_teachers_count[lab][j]==0) possible=false;
		}
		if(possible) {
			lab_teachers_count[lab][j]-=1;
			batch_lab_teacher[batch_number][lab]=lab_teachers_index[lab][j];
			for(int k=0;k<day_store.size();k++) {
				teachers[lab_teachers_index[lab][j]][day_store[k]][2*(slot_store[k]+add_div)]=batch_number+1;
				teachers[lab_teachers_index[lab][j]][day_store[k]][(2*(slot_store[k]+add_div))+1]=batch_number+1;
			}
			if(assign_lab_teachers(batch_number+1,lab)) return true;
			else {
				batch_lab_teacher[batch_number][lab]=-1;
				lab_teachers_count[lab][j]+=1;
				for(int k=0;k<day_store.size();k++) {
					teachers[lab_teachers_index[lab][j]][day_store[k]][2*(slot_store[k]+add_div)]=0;
					teachers[lab_teachers_index[lab][j]][day_store[k]][(2*(slot_store[k]+add_div))+1]=0;
					continue;
				}
			}
		}
	}
	for(int j=0;j<lab_teachers_count[lab].size();j++) {
		if(lab_teachers_count[lab][j]!=0) return false;
	}
	return true;
}

void timetable::randomise() {
	int x1,x2,y1,y2;
    srand ( time(NULL) );
	for(int i=0;i<6;i++) {
		
		bool ok_var=false;
		
		for(int i=0;i<5;i++) {
			for(int j=1;j<3;j++) {
				if( 
					(batch[0][i][j*2]==0)&&
					(batch[4][i][j*2]==0)&&
					(batch[8][i][j*2]==0)&&
					(batch[12][i][(2*(j-1))+1]==0) 
					) {
					
					vector <int> days;
					for(int k=0;k<5;k++) {
						if( batch[0][k][0]!=0 || batch[4][k][0]!=0 || batch[8][k][0]!=0) {
							days.push_back(k);
						}
					}
					int day_to_change = days[( rand() % days.size() )];
					
					for(int k=0;k<12;k++) {
						batch[k][i][2*j]=batch[k][day_to_change][0];
						batch[k][i][2*j+1]=batch[k][day_to_change][1];
						batch[k][day_to_change][0]=0;
						batch[k][day_to_change][1]=0;
					}
					
				}
			}
		}		
		
		/* randomise the practical sessions common to all the batches */
		x1 = (rand()%2) + 1;
		y1 = rand()%5;
		x2 = (rand()%2) + 1;
		y2 = rand()%5;
		for(int j=0;j<16;j++) {
			if(j<12) {
				int temp = batch[j][y1][x1*2];
				batch[j][y1][x1*2]=batch[j][y2][x2*2];
				batch[j][y2][x2*2]=temp;
				batch[j][y1][x1*2+1]=batch[j][y2][x2*2+1];
				batch[j][y2][x2*2+1]=temp;
			}else {
				int temp = batch[j][y1][2*(x1-1)+1];
				batch[j][y1][2*(x1-1)+1]=batch[j][y2][2*(x2-1)+1];
				batch[j][y2][2*(x2-1)+1]=temp;
				batch[j][y1][(2*(x1-1))+1+1]=batch[j][y2][(2*(x2-1))+1+1];
				batch[j][y2][(2*(x2-1))+1+1]=temp;
			}
		}
	}
}

bool timetable::check_filled() {
	bool to_ret = true;
	int tmpi=0;
	for(int i=0;i<5;i++) {
		for(int j=1;j<3;j++) {
			bool tmp = false;
			for(int k=0;k<12;k+=4) {
				if(batch[k][i][j*2]!=0) tmp = true;
			}
			if(batch[12][i][(2*(j-1))+1]!=0) tmp = true;
			if(!tmp) tmpi+=1;
			to_ret = to_ret & tmp;
		}
	}
	if(!to_ret) return false;
	/*
		Check if the generated time table for labs follow certain guidelines like:
		1. There should not be three labs in a day.
		2. There should not be two labs of a particular subject on the same day.
	*/
	for(int i=0;i<16;i++) {
		for(int j=0;j<5;j++) {
			int count_labs_per_day = 0;
			for(int k=0;k<3;k++) {
				if(batch[i][j][2*k]!=0) count_labs_per_day += 1;
			}
			if(count_labs_per_day==3) return false;
		}
	}
	
	for(int i=0;i<16;i++) {
		for(int j=0;j<5;j++) {
			if( (batch[i][j][0]==batch[i][j][2]) && batch[i][j][0]!=0 ) return false;
			if( (batch[i][j][2]==batch[i][j][4]) && batch[i][j][2]!=0 ) return false;
			if( (batch[i][j][4]==batch[i][j][0]) && batch[i][j][4]!=0 ) return false;
		}
	}
	
	return true;
}

bool timetable::find_c4(int day, int session) {
	/* 
		function for class c4
		should handle 12 to 15 batches
	*/
	int add_div=1;
	if(labs_class_count[3]==6) {
		/* checks whether atleast one lab has practical at a point of time */
		//return check_filled();
		return true;
	}
	for(int i=0;i<6;i++) {
		if(labs_remaining[12][i]==0) continue;
		if(labs_occupied[labs_remaining[12][i]][day][session+1]==labs_maxlimit[labs_remaining[12][i]]) {
			/* labs are full for that slot */
			continue;
		}
		for(int j=0;j<6;j++) {
			if(labs_remaining[13][j]==0) continue;
			if(labs_occupied[labs_remaining[13][j]][day][session+1]==labs_maxlimit[labs_remaining[13][j]]) {
				/* labs are full for that slot */
				continue;
			}
			for(int k=0;k<6;k++) {
				if(labs_remaining[14][k]==0) continue;
				if(labs_occupied[labs_remaining[14][k]][day][session+1]==labs_maxlimit[labs_remaining[14][k]]) {
					/* labs are full for that slot */
					continue;
				}
				for(int l=0;l<6;l++) {
					if(labs_remaining[15][l]==0) continue;
					if(labs_occupied[labs_remaining[15][l]][day][session+1]==labs_maxlimit[labs_remaining[15][l]]) {
						/* labs are full for that slot */
						continue;
					}
					/* The Combination of labs and batches is possible */
					
					
					/* updation of all variables starts here */
					batch[12][day][(2*session)+add_div]=labs_remaining[12][i];
					batch[13][day][(2*session)+add_div]=labs_remaining[13][j];
					batch[14][day][(2*session)+add_div]=labs_remaining[14][k];
					batch[15][day][(2*session)+add_div]=labs_remaining[15][l];
					
					batch[12][day][(2*session)+1+add_div]=labs_remaining[12][i];
					batch[13][day][(2*session)+1+add_div]=labs_remaining[13][j];
					batch[14][day][(2*session)+1+add_div]=labs_remaining[14][k];
					batch[15][day][(2*session)+1+add_div]=labs_remaining[15][l];

					labs_occupied[labs_remaining[12][i]][day][session+1] += 1;
					labs_occupied[labs_remaining[13][j]][day][session+1] += 1;
					labs_occupied[labs_remaining[14][k]][day][session+1] += 1;
					labs_occupied[labs_remaining[15][l]][day][session+1] += 1;
					
					if( (labs_occupied[labs_remaining[12][i]][day][session+1] > labs_maxlimit[labs_remaining[12][i]]) ||
						(labs_occupied[labs_remaining[13][j]][day][session+1] > labs_maxlimit[labs_remaining[13][j]]) ||
						(labs_occupied[labs_remaining[14][k]][day][session+1] > labs_maxlimit[labs_remaining[14][k]]) ||
						(labs_occupied[labs_remaining[15][l]][day][session+1] > labs_maxlimit[labs_remaining[15][l]])
						) {
						batch[12][day][(2*session)+add_div]=0;
						batch[13][day][(2*session)+add_div]=0;
						batch[14][day][(2*session)+add_div]=0;
						batch[15][day][(2*session)+add_div]=0;
						
						batch[12][day][(2*session)+1+add_div]=0;
						batch[13][day][(2*session)+1+add_div]=0;
						batch[14][day][(2*session)+1+add_div]=0;
						batch[15][day][(2*session)+1+add_div]=0;

						labs_occupied[labs_remaining[12][i]][day][session+1] -= 1;
						labs_occupied[labs_remaining[13][j]][day][session+1] -= 1;
						labs_occupied[labs_remaining[14][k]][day][session+1] -= 1;
						labs_occupied[labs_remaining[15][l]][day][session+1] -= 1;
						
						continue;

					}
					
					labs_remaining[12][i]=0;
					labs_remaining[13][j]=0;
					labs_remaining[14][k]=0;
					labs_remaining[15][l]=0;
					
					labs_class_count[3] += 1;
					/* updatation of all variables end */
					
					
					if(day==4 && session==2) {
						break;
					}else {
						bool possible=false;
						if(session==2)
							possible = find_c4(day+1,0);
						else
							possible = find_c4(day,session+1);
						if(possible)
							return true;
						else {
							batch[12][day][(2*session)+add_div]=0;
							batch[13][day][(2*session)+add_div]=0;
							batch[14][day][(2*session)+add_div]=0;
							batch[15][day][(2*session)+add_div]=0;
							
							batch[12][day][(2*session)+1+add_div]=0;
							batch[13][day][(2*session)+1+add_div]=0;
							batch[14][day][(2*session)+1+add_div]=0;
							batch[15][day][(2*session)+1+add_div]=0;

							/* revert labs_remaining array */
							labs_remaining[12][i]=i;
							labs_remaining[13][j]=j;
							labs_remaining[14][k]=k;
							labs_remaining[15][l]=l;
							if(i==0) labs_remaining[12][i]=1;
							if(j==0) labs_remaining[13][j]=1;
							if(k==0) labs_remaining[14][k]=1;
							if(l==0) labs_remaining[15][l]=1;
							
							labs_class_count[3] += 1;
							
							/* revert labs_occupied count */
							labs_occupied[labs_remaining[12][i]][day][session+1] -= 1;
							labs_occupied[labs_remaining[13][j]][day][session+1] -= 1;
							labs_occupied[labs_remaining[14][k]][day][session+1] -= 1;
							labs_occupied[labs_remaining[15][l]][day][session+1] -= 1;
							
							continue;
						}
					}
				}
			}
		}
	}
	bool possible;
	if(session==2 && day==4) return false;
	else if(session==2)
		possible = find_c4(day+1,0);
	else
		possible = find_c4(day,session+1);
}


bool timetable::find_c3(int day, int session) {
	/* 
		function for class c3
		should handle 8 to 11 batches
	*/
	if(labs_class_count[2]==6) {
		if(find_c4(0,0)) {
			return true;
		}else {
			return false;
		}
	}
	for(int i=0;i<6;i++) {
		if(labs_remaining[8][i]==0) continue;
		if(labs_occupied[labs_remaining[8][i]][day][session]==labs_maxlimit[labs_remaining[8][i]]) {
			/* labs are full for that slot */
			continue;
		}
		for(int j=0;j<6;j++) {
			if(labs_remaining[9][j]==0) continue;
			if(labs_occupied[labs_remaining[9][j]][day][session]==labs_maxlimit[labs_remaining[9][j]]) {
				/* labs are full for that slot */
				continue;
			}
			for(int k=0;k<6;k++) {
				if(labs_remaining[10][k]==0) continue;
				if(labs_occupied[labs_remaining[10][k]][day][session]==labs_maxlimit[labs_remaining[10][k]]) {
					/* labs are full for that slot */
					continue;
				}
				for(int l=0;l<6;l++) {
					if(labs_remaining[11][l]==0) continue;
					if(labs_occupied[labs_remaining[11][l]][day][session]==labs_maxlimit[labs_remaining[11][l]]) {
						/* labs are full for that slot */
						continue;
					}
					/* The Combination of labs and batches is possible */
					
					
					/* updation of all variables starts here */
					batch[8][day][2*session]=labs_remaining[8][i];
					batch[9][day][2*session]=labs_remaining[9][j];
					batch[10][day][2*session]=labs_remaining[10][k];
					batch[11][day][2*session]=labs_remaining[11][l];
					
					batch[8][day][2*session+1]=labs_remaining[8][i];
					batch[9][day][2*session+1]=labs_remaining[9][j];
					batch[10][day][2*session+1]=labs_remaining[10][k];
					batch[11][day][2*session+1]=labs_remaining[11][l];

					labs_occupied[labs_remaining[8][i]][day][session] += 1;
					labs_occupied[labs_remaining[9][j]][day][session] += 1;
					labs_occupied[labs_remaining[10][k]][day][session] += 1;
					labs_occupied[labs_remaining[11][l]][day][session] += 1;
					
					if( (labs_occupied[labs_remaining[8][i]][day][session] > labs_maxlimit[labs_remaining[8][i]]) ||
						(labs_occupied[labs_remaining[9][j]][day][session] > labs_maxlimit[labs_remaining[9][j]]) ||
						(labs_occupied[labs_remaining[10][k]][day][session] > labs_maxlimit[labs_remaining[10][k]]) ||
						(labs_occupied[labs_remaining[11][l]][day][session] > labs_maxlimit[labs_remaining[11][l]])
						) {
						batch[8][day][2*session]=0;
						batch[9][day][2*session]=0;
						batch[10][day][2*session]=0;
						batch[11][day][2*session]=0;
						
						batch[8][day][2*session+1]=0;
						batch[9][day][2*session+1]=0;
						batch[10][day][2*session+1]=0;
						batch[11][day][2*session+1]=0;

						labs_occupied[labs_remaining[8][i]][day][session] -= 1;
						labs_occupied[labs_remaining[9][j]][day][session] -= 1;
						labs_occupied[labs_remaining[10][k]][day][session] -= 1;
						labs_occupied[labs_remaining[11][l]][day][session] -= 1;
						
						continue;

					}
					
					labs_remaining[8][i]=0;
					labs_remaining[9][j]=0;
					labs_remaining[10][k]=0;
					labs_remaining[11][l]=0;
					
					labs_class_count[2] += 1;
					/* updatation of all variables end */
					
					
					if(day==4 && session==2) {
						break;
					}else {
						bool possible=false;
						if(session==2)
							possible = find_c3(day+1,0);
						else
							possible = find_c3(day,session+1);
						if(possible)
							return true;
						else {
							batch[8][day][2*session]=0;
							batch[9][day][2*session]=0;
							batch[10][day][2*session]=0;
							batch[11][day][2*session]=0;
							
							batch[8][day][2*session+1]=0;
							batch[9][day][2*session+1]=0;
							batch[10][day][2*session+1]=0;
							batch[11][day][2*session+1]=0;

							/* revert labs_reaining array */
							labs_remaining[8][i]=i;
							labs_remaining[9][j]=j;
							labs_remaining[10][k]=k;
							labs_remaining[11][l]=l;
							if(i==0) labs_remaining[8][i]=1;
							if(j==0) labs_remaining[9][j]=1;
							if(k==0) labs_remaining[10][k]=1;
							if(l==0) labs_remaining[11][l]=1;
							
							labs_class_count[2] += 1;
							
							/* revert labs_occupied count */
							labs_occupied[labs_remaining[8][i]][day][session] -= 1;
							labs_occupied[labs_remaining[9][j]][day][session] -= 1;
							labs_occupied[labs_remaining[10][k]][day][session] -= 1;
							labs_occupied[labs_remaining[11][l]][day][session] -= 1;
							
							continue;
						}
					}
				}
			}
		}
	}
	bool possible;
	if(session==2 && day==4) return false;
	else if(session==2)
		possible = find_c3(day+1,0);
	else
		possible = find_c3(day,session+1);
}

bool timetable::find_c2(int day, int session) {
	/* 
		function for class c2
		should handle 4 to 7 batches
	*/
	if(labs_class_count[1]==6) {
		if(find_c3(0,0)) {
			return true;
		}else {
			return false;
		}
	}
	for(int i=0;i<6;i++) {
		if(labs_remaining[4][i]==0) continue;
		if(labs_occupied[labs_remaining[4][i]][day][session]==labs_maxlimit[labs_remaining[4][i]]) {
			/* labs are full for that slot */
			continue;
		}
		for(int j=0;j<6;j++) {
			if(labs_remaining[5][j]==0) continue;
			if(labs_occupied[labs_remaining[5][j]][day][session]==labs_maxlimit[labs_remaining[5][j]]) {
				/* labs are full for that slot */
				continue;
			}
			for(int k=0;k<6;k++) {
				if(labs_remaining[6][k]==0) continue;
				if(labs_occupied[labs_remaining[6][k]][day][session]==labs_maxlimit[labs_remaining[6][k]]) {
					/* labs are full for that slot */
					continue;
				}
				for(int l=0;l<6;l++) {
					if(labs_remaining[7][l]==0) continue;
					if(labs_occupied[labs_remaining[7][l]][day][session]==labs_maxlimit[labs_remaining[7][l]]) {
						/* labs are full for that slot */
						continue;
					}
					/* The Combination of labs and batches is possible */
					
					
					/* updation of all variables starts here */
					batch[4][day][2*session]=labs_remaining[4][i];
					batch[5][day][2*session]=labs_remaining[5][j];
					batch[6][day][2*session]=labs_remaining[6][k];
					batch[7][day][2*session]=labs_remaining[7][l];

					batch[4][day][2*session+1]=labs_remaining[4][i];
					batch[5][day][2*session+1]=labs_remaining[5][j];
					batch[6][day][2*session+1]=labs_remaining[6][k];
					batch[7][day][2*session+1]=labs_remaining[7][l];

					labs_occupied[labs_remaining[4][i]][day][session] += 1;
					labs_occupied[labs_remaining[5][j]][day][session] += 1;
					labs_occupied[labs_remaining[6][k]][day][session] += 1;
					labs_occupied[labs_remaining[7][l]][day][session] += 1;
					
					if( (labs_occupied[labs_remaining[4][i]][day][session] > labs_maxlimit[labs_remaining[4][i]]) ||
						(labs_occupied[labs_remaining[5][j]][day][session] > labs_maxlimit[labs_remaining[5][j]]) ||
						(labs_occupied[labs_remaining[6][k]][day][session] > labs_maxlimit[labs_remaining[6][k]]) ||
						(labs_occupied[labs_remaining[7][l]][day][session] > labs_maxlimit[labs_remaining[7][l]])
						) {
						batch[4][day][2*session]=0;
						batch[5][day][2*session]=0;
						batch[6][day][2*session]=0;
						batch[7][day][2*session]=0;
						
						batch[4][day][2*session+1]=0;
						batch[5][day][2*session+1]=0;
						batch[6][day][2*session+1]=0;
						batch[7][day][2*session+1]=0;

						labs_occupied[labs_remaining[4][i]][day][session] -= 1;
						labs_occupied[labs_remaining[5][j]][day][session] -= 1;
						labs_occupied[labs_remaining[6][k]][day][session] -= 1;
						labs_occupied[labs_remaining[7][l]][day][session] -= 1;
						
						continue;

					}
					
					labs_remaining[4][i]=0;
					labs_remaining[5][j]=0;
					labs_remaining[6][k]=0;
					labs_remaining[7][l]=0;
					
					labs_class_count[1] += 1;
					/* updatation of all variables end */
					
					
					if(day==4 && session==2) {
						break;
					}else {
						bool possible=false;
						if(session==2)
							possible = find_c2(day+1,0);
						else
							possible = find_c2(day,session+1);
						if(possible)
							return true;
						else {
							batch[4][day][2*session]=0;
							batch[5][day][2*session]=0;
							batch[6][day][2*session]=0;
							batch[7][day][2*session]=0;

							batch[4][day][2*session+1]=0;
							batch[5][day][2*session+1]=0;
							batch[6][day][2*session+1]=0;
							batch[7][day][2*session+1]=0;
							
							/* revert labs_reaining array */
							labs_remaining[4][i]=i;
							labs_remaining[5][j]=j;
							labs_remaining[6][k]=k;
							labs_remaining[7][l]=l;
							if(i==0) labs_remaining[4][i]=1;
							if(j==0) labs_remaining[5][j]=1;
							if(k==0) labs_remaining[6][k]=1;
							if(l==0) labs_remaining[7][l]=1;
							
							labs_class_count[1] += 1;
							
							/* revert labs_occupied count */
							labs_occupied[labs_remaining[4][i]][day][session] -= 1;
							labs_occupied[labs_remaining[5][j]][day][session] -= 1;
							labs_occupied[labs_remaining[6][k]][day][session] -= 1;
							labs_occupied[labs_remaining[7][l]][day][session] -= 1;
							
							continue;
						}
					}
				}
			}
		}
	}
	bool possible;
	if(session==2 && day==4) return false;
	else if(session==2)
		possible = find_c2(day+1,0);
	else
		possible = find_c2(day,session+1);
}


bool timetable::find_c1(int day, int session) {
	/* 
		function for class c1
		should handle first 4 batches
	*/
	if(labs_class_count[0]==6) {
		if(find_c2(0,0)) {
			return true;
		}else {
			return false;
		}
	}
	
	
	for(int i=0;i<6;i++) {
		if(labs_remaining[0][i]==0) continue;
		if(labs_occupied[labs_remaining[0][i]][day][session]==labs_maxlimit[labs_remaining[0][i]]) {
			/* labs are full for that slot */
			continue;
		}
		for(int j=0;j<6;j++) {
			if(labs_remaining[1][j]==0) continue;		
			if(labs_occupied[labs_remaining[1][j]][day][session]==labs_maxlimit[labs_remaining[1][j]]) {
				/* labs are full for that slot */
				continue;
			}
			for(int k=0;k<6;k++) {
				if(labs_remaining[2][k]==0) continue;
				if(labs_occupied[labs_remaining[2][k]][day][session]==labs_maxlimit[labs_remaining[2][k]]) {
					/* labs are full for that slot */
					continue;
				}
				for(int l=0;l<6;l++) {
					if(labs_remaining[3][l]==0) continue;
					if(labs_occupied[labs_remaining[3][l]][day][session]==labs_maxlimit[labs_remaining[3][l]]) {
						/* labs are full for that slot */
						continue;
					}
					/* The Combination of labs and batches is possible */
					
					
					/* updation of all variables starts here */
					batch[0][day][2*session]=labs_remaining[0][i];
					batch[1][day][2*session]=labs_remaining[1][j];
					batch[2][day][2*session]=labs_remaining[2][k];
					batch[3][day][2*session]=labs_remaining[3][l];
					
					batch[0][day][2*session+1]=labs_remaining[0][i];
					batch[1][day][2*session+1]=labs_remaining[1][j];
					batch[2][day][2*session+1]=labs_remaining[2][k];
					batch[3][day][2*session+1]=labs_remaining[3][l];

					labs_occupied[labs_remaining[0][i]][day][session] += 1;
					labs_occupied[labs_remaining[1][j]][day][session] += 1;
					labs_occupied[labs_remaining[2][k]][day][session] += 1;
					labs_occupied[labs_remaining[3][l]][day][session] += 1;
					
					if( (labs_occupied[labs_remaining[0][i]][day][session] > labs_maxlimit[labs_remaining[0][i]]) ||
						(labs_occupied[labs_remaining[1][j]][day][session] > labs_maxlimit[labs_remaining[1][j]]) ||
						(labs_occupied[labs_remaining[2][k]][day][session] > labs_maxlimit[labs_remaining[2][k]]) ||
						(labs_occupied[labs_remaining[3][l]][day][session] > labs_maxlimit[labs_remaining[3][l]])
						) {
						/* reset all variables */
						batch[0][day][2*session]=0;
						batch[1][day][2*session]=0;
						batch[2][day][2*session]=0;
						batch[3][day][2*session]=0;
						
						batch[0][day][2*session+1]=0;
						batch[1][day][2*session+1]=0;
						batch[2][day][2*session+1]=0;
						batch[3][day][2*session+1]=0;

						labs_occupied[labs_remaining[0][i]][day][session] -= 1;
						labs_occupied[labs_remaining[1][j]][day][session] -= 1;
						labs_occupied[labs_remaining[2][k]][day][session] -= 1;
						labs_occupied[labs_remaining[3][l]][day][session] -= 1;
						
						continue;

					}
					
					labs_remaining[0][i]=0;
					labs_remaining[1][j]=0;
					labs_remaining[2][k]=0;
					labs_remaining[3][l]=0;
					
					labs_class_count[0] += 1;
					/* updatation of all variables end */
					
					
					if(day==4 && session==2) {
						break;
					}else {
						bool possible=false;
						if(session==2)
							possible = find_c1(day+1,0);
						else
							possible = find_c1(day,session+1);
						if(possible)
							return true;
						else {
							batch[0][day][2*session]=0;
							batch[1][day][2*session]=0;
							batch[2][day][2*session]=0;
							batch[3][day][2*session]=0;
							
							batch[0][day][2*session+1]=0;
							batch[1][day][2*session+1]=0;
							batch[2][day][2*session+1]=0;
							batch[3][day][2*session+1]=0;

							/* revert labs_reaining array */
							labs_remaining[0][i]=i;
							labs_remaining[1][j]=j;
							labs_remaining[2][k]=k;
							labs_remaining[3][l]=l;
							if(i==0) labs_remaining[0][i]=1;
							if(j==0) labs_remaining[1][j]=1;
							if(k==0) labs_remaining[2][k]=1;
							if(l==0) labs_remaining[3][l]=1;
							
							labs_class_count[0] += 1;
							
							/* revert labs_occupied count */
							labs_occupied[labs_remaining[0][i]][day][session] -= 1;
							labs_occupied[labs_remaining[1][j]][day][session] -= 1;
							labs_occupied[labs_remaining[2][k]][day][session] -= 1;
							labs_occupied[labs_remaining[3][l]][day][session] -= 1;
							
							continue;
						}
					}
				}
			}
		}
	}
	bool possible;
	if(session==2 && day==4) return false;
	else if(session==2)
		possible = find_c1(day+1,0);
	else
		possible = find_c1(day,session+1);
	
}

/* start of interface functions */
string timetable::get_batch_timetable(int batch_number, int day, int slot) {
	/* returns the name of the lab for the batch at a give day and slot */
	if(!is_lab(batch_number, day, slot)) 	return get_lab_name(batch[(batch_number/4)*4][day][slot]);
	else return get_lab_name(batch[batch_number][day][slot]);
}

int timetable::set_teachers_lab(int lab_number, vector<int> teachers_count_list, vector<string> teachers_name_list) {
	/* sets the teachers name and load for lab lab_number */
	if( lab_number<1 || lab_number>5 ) {
		return 0;
	}
	lab_teachers_count[lab_number] = teachers_count_list;
	for(int i=0;i<teachers_name_list.size();i++) {
		teachers_name[total_teachers] = teachers_name_list[i];
		lab_teachers_index[lab_number].push_back(total_teachers);
		total_teachers += 1;
	}
	return 1;
}

int timetable::set_teachers_lec(int lec_number, vector <int> teachers_count_list, vector<string> teachers_name_list) {
	/* sets the teachers name and load for lecture lec_number */
	lec_teachers_count[lec_number]=teachers_count_list;
	for(int i=0;i<teachers_name_list.size();i++) {
		int j;
		string tmp_name = teachers_name_list[i];
		for(j=0;j<total_teachers;j++) {
			if(teachers_name[j]==tmp_name) break;
		}
		if(j<total_teachers){
			lec_teachers_index[lec_number].push_back(j);
		}else{
			lec_teachers_index[lec_number].push_back(j);
			teachers_name[total_teachers]=tmp_name;
			total_teachers += 1;
		}
	}
}

int timetable::add_lab_name(int lab_number,string name) {
	if(lab_number>0 && lab_number<6) {
		lab_name[lab_number].push_back(name);
		return 1;
	}
	return 0;
}

string timetable::get_teacher_timetable(int teacher_number, int day, int slot) {
	/* returns the name of the batch assigned to the teacher teacher_number of lab lab_number */
	return batch_no_to_str(teachers[teacher_number][day][slot]);
}
/* end of interface functions */

void timetable::execute() {
	/* Generates the timetable,	should be called after the input is specified */
	find_c1(0,0);
    output_log+="Randomising\n";
	while(!check_filled())
		randomise();
	output_log+="Arranging teachers to labs\n";
	for(int i=1;i<6;i++) assign_lab_teachers(0,i);
	output_log+="Arranging lectures\n";
	success_var=true;
	if(!assign_lecs4(6,0)) {
		error_log+="Could not arrange lec 6\n";
		success_var=false;
	}
	if(!assign_lecs4(7,0)) {
		error_log+="Could not arrange lec 7\n";
		success_var=false;
	}
	if(!assign_lecs3(8,0)) {
		error_log+="Could not arrange lec 8\n";
		success_var=false;
	}
	if(!assign_lecs3(9,0)) {
		error_log+="Could not arrange lec 9\n";
		success_var=false;
	}
	if(!assign_lecs3(10,0)) {
		error_log+="Could not arrange lec 10\n";
		success_var=false;
	}
	if(!assign_lecs1(11,0,0)) {
		error_log+="Could not arrange lec 11\n";
		success_var=false;
	}
	if(!assign_lecs1(12,0,0)) {
		error_log+="Could not arrange lec 12\n";
		success_var=false;
	}
	if(!assign_lecs1(13,0,0)) {
		error_log+="Could not arrange lec 13\n";
		success_var=false;
	}
	if(!assign_lecs1(14,0,0)) {
		error_log+="Could not arrange lec 14\n";
		success_var=false;
	} 	 	
	
	output_log+="Assigning saturday\n";
	assign_sat();

}

string timetable::get_batch_lab_teacher(int batch_no,int lab_no) {
	return teachers_name[batch_lab_teacher[batch_no][lab_no]];
}

string timetable::get_batch_lab_name(int batch_no,int lab_no) {
	/* This function is vulnerable to lab clashes, but will work fine with the current input of lab subjects */
	int index = 0,tmp_day=0,tmp_slot=0;
	int add_div=0;
	if(batch_no>=12) add_div=1;
	for(int i=0;i<5;i++) {
		for(int j=0;j<6;j++) {
			if(batch[batch_no][i][j+add_div]==lab_no) {
				tmp_day=i;
				tmp_slot=j;
				break;
			}
		}
		if(batch[batch_no][tmp_day][tmp_slot+add_div]==lab_no) break;
	}
	for(int i=0;i<12;i++) {
		if((tmp_slot+(2*add_div))>=5) break;
		if(batch_no==i) break;
		if(batch[i][tmp_day][(tmp_slot+(2*add_div))]==lab_no) index += 1;
	}
	for(int i=12;i<batch_no;i++) {
		if(batch[i][tmp_day][tmp_slot+add_div]==lab_no) index += 1;
	}
	return lab_name[lab_no][index];
}

string timetable::get_class_lec_teacher(int class_no,int lec_no) {
	if(class_lec_teacher[class_no][lec_no]<0 || class_lec_teacher[class_no][lec_no]>=total_teachers) {
		return "Error";
	}
	return teachers_name[class_lec_teacher[class_no][lec_no]];
}

int timetable::get_total_teachers() {
	return total_teachers;
}

string timetable::get_teacher_name(int teacher_number) {
	return teachers_name[teacher_number];
}

string timetable::get_class_room(int class_no,int day=0,int slot=0) {
	if(class_no==0) return "A211";
	if(class_no==1) return "A212";
	if(class_no==2) return "A213";
	if(is_lab(class_no*4,day,slot)) return "    ";
	if(slot>=6) return "A211";
	if(batch[0][day][slot+1]<6) return "A211";
	if(batch[4][day][slot+1]<6) return "A212";
	if(batch[8][day][slot+1]<6) return "A213";
	return "othr";
}

bool timetable::is_lab(int batch_number, int day, int slot) {
	if(batch[batch_number][day][slot]>0 and batch[batch_number][day][slot]<6) return true;
	else return false;
}

bool timetable::success() {
	return success_var;
}

string timetable::get_output_log() {
	return output_log;
}

string timetable::get_error_log() {
	return error_log;
}
