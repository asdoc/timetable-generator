#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class timetable {
	int batch[16][5][3]; /* stores the time table for labs */
	bool lab_status[4][5][3]; /* Stores the lab status (if there is a lab or no) for each of the 4 classes */
	int labs_remaining[16][6]; /* stores the list of labs remaining per batch */
	int labs_class_count[4]; /* stores the number of labs covered for each class */
	int labs_occupied[6][5][4]; /* stores the count of the labs occupied per lab subject */
	int labs_maxlimit[6];		/* maximum count of labs available at a time */
	vector <int> teachers_count[6];	/* stores the teachers load for respective labs */
	vector <string> teachers_name[6]; /* stores the teachers names for respective labs */
	bool teacher_assigned_to_batch[16][5][3]; /* true if a teacher is assigned to the batch */
	int teachers[6][10][5][4]; /* stores time table for teachers as [lab][teacher_number][day][slot] */

	/* initialises variables */
	void init();
	string batch_no_to_str(int batch_number);
	string get_lab_name(int lab_number);
	
	/* function for the assignment of teachers to lab (assumes that labs have been arranged) */
	bool assign_lab_teachers(int batch_number,int lab);
	
	/* randomly changes the position the labs */
	/* TODO dependency on this function can be reduced by taking care of constraints in the find_c functions.
		Complexity can be reduced heavily by doing the same  */
	void randomise();
	
	/* checks if the batche's labs are properly arranged within various constraints */
	bool check_filled();
	
	/* functions for arranging the labs for class SE4 - SE1 */
	bool find_c4(int day, int session);
	bool find_c3(int day, int session);
	bool find_c2(int day, int session);
	bool find_c1(int day, int session);

public:
	/*
		Interface functions start from here
		Call these functions as preferably in the order of declaration
	*/
	
	/*	I/O interface functions */
	string get_batch_lab(int batch_number, int day, int slot);
	int set_teachers_data(int lab_number, vector<int> teachers_count_list, vector<string> teachers_name_list);
	string get_teacher_batch(int lab_number, int teacher_number, int day, int slot);

	/* Generates the timetable,	should be called after the input is specified */
	void execute();
};
