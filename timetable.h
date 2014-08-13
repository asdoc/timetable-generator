#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class timetable {
	int batch[16][6][7]; /* stores the time table for labs [batch][day][session]*/
	int labs_remaining[16][6]; /* stores the list of labs remaining per batch [batch][lab]*/
	int labs_class_count[4]; /* stores the number of labs covered for each class [class] */
	int labs_occupied[6][5][4]; /* stores the count of the labs occupied per lab subject [labs][day][session]*/
	int labs_maxlimit[6];		/* maximum count of labs available at a time [labs] */
	vector <int> lab_teachers_count[6];	/* stores the teachers load for respective labs [no][labs] */
	vector <int> lab_teachers_index[6]; /* stores the index of the lab teacher in teachers[][][] */
	vector <int> lec_teachers_count[15]; /* stores the teachers load for lectures */
	vector <int> lec_teachers_index[15]; /* stores the index of the lecture teacher in teachers[][][] */
	int lec_class_count[4][15];
	int lecs_maxlimit[15];
	string teachers_name[60]; /* stores the teachers names [teacher_number] */
	int teachers[60][6][9]; /* stores time table for teachers as [teacher_number][day][session] */
	int total_teachers;		/* total number of teacher */
	
	int batch_lab_teacher[16][6];
	int class_lec_teacher[4][15];
	
	vector <string> lab_name[6];

	string batch_no_to_str(int batch_number);
	string get_lab_name(int lab_number);
	
	/* function for the assignment of teachers to lab (assumes that labs have been arranged) */
	bool assign_lab_teachers(int batch_number,int lab);
	bool assign_lecs4(int lec_number, int class_no);
	bool assign_lecs3(int lec_number, int class_no);
	bool assign_lecs1(int lec_number, int teacher_index, int class_no);
	bool success_var;
	void assign_sat();

	/* randomly changes the position the labs */
	/* TODO this function can be optimised */
	void randomise();
	
	/* checks if the batch's labs are properly arranged within various constraints */
	bool check_filled();
	
	/* functions for arranging the labs for class SE4 - SE1 */
	bool find_c4(int day, int session);
	bool find_c3(int day, int session);
	bool find_c2(int day, int session);
	bool find_c1(int day, int session);

	string output_log;
	string error_log;
public:
	/* initialises variables */
	timetable();

	/*
		Interface functions start from here
		Call these functions as preferably in the order of declaration
	*/
	
	/* input functions, must be called before executing the actual timetable */
	int set_teachers_lab(int lab_number, vector<int> teachers_count_list, vector<string> teachers_name_list);
	int set_teachers_lec(int lec_number, vector<int> teachers_count_list, vector<string> teachers_name_list);
	int add_lab_name(int lab_number,string name);
	
	/* Generates the timetable,	must be called after the input is specified */
	void execute();
	
	
	/* output functions,  must be called after execute() is called */
	string get_batch_timetable(int batch_number, int day, int slot);
	string get_teacher_timetable(int teacher_number, int day, int slot);
	string get_teacher_name(int teacher_number);
	string get_class_room(int class_no,int day,int slot);
	
	/* returns the name of the teacher assigned to batch and lab */
	string get_batch_lab_teacher(int batch,int lab);
	
	/* returns the name of the lab for that particular batch */
	string get_batch_lab_name(int batch,int lab);
	
	/* returns the name of the teacher assigned to class_no and lec_no */
	string get_class_lec_teacher(int class_no, int lec_no);
	
	bool is_lab(int batch_number, int day, int slot);
	
	/* returns true if all labs and lectures are arranged properly */
	bool success();
	
	int get_total_teachers();
	
	string get_output_log();
	string get_error_log();
};
