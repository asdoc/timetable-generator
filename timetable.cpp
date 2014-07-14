#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int batch[16][5][3]; /* stores the time table for labs */
bool lab_status[4][5][3]; /* Stores the lab status (if there is a lab or no) for each of the 4 classes */
int labs_remaining[16][6]; /* stores the list of labs remaining per batch */
int labs_class_count[4]; /* stores the number of labs covered for each class */
int labs_occupied[6][5][4]; /* stores the count of the labs occupied per lab subject */
							/* 4 for handling the second shift */
int labs_maxlimit[6];

void init() {
	for(int i=0;i<16;i++) {
		for(int j=0;j<5;j++) {
			for(int k=0;k<3;k++) {
				batch[i][j][k]=0;
			}
		}
	}
	for(int i=0;i<4;i++) {
		for(int j=0;j<5;j++) {
			for(int k=0;k<3;k++) {
				lab_status[i][j][k]=false;
			}
		}
	}
	for(int i=0;i<4;i++) {
		labs_class_count[i]=0;
	}
	for(int i=1;i<=5;i++) {
		for(int j=0;j<5;j++) {
			for(int k=0;k<3;k++) {
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
}

void randomise() {
	int x1,x2,y1,y2;
    srand ( time(NULL) );
	for(int i=0;i<20;i++) {
		/* randomise the first practical sessions for classes 1 to 3 */
		x1 = 1;
		y1 = rand()%5;
		x2 = 1;
		y2 = rand()%5;
		for(int j=0;j<12;j++) {
			int temp = batch[j][y1][x1];
			batch[j][y1][x1]=batch[j][y2][x2];
			batch[j][y2][x2]=temp;
		}
		
		/* randomise the practical sessions common to all the batches */
		x1 = (rand()%2) + 1;
		y1 = rand()%5;
		x2 = (rand()%2) + 1;
		y2 = rand()%5;
		for(int j=0;j<16;j++) {
			if(j<12) {
				int temp = batch[j][y1][x1];
				batch[j][y1][x1]=batch[j][y2][x2];
				batch[j][y2][x2]=temp;
			}
			else {
				int temp = batch[j][y1][x1-1];
				batch[j][y1][x1-1]=batch[j][y2][x2-1];
				batch[j][y2][x2-1]=temp;
			}
		}

		/* randomise the last practical sessions for the 4th division */
		x1 = 2;
		y1 = rand()%5;
		x2 = 2;
		y2 = rand()%5;
		for(int j=12;j<16;j++) {
				int temp = batch[j][y1][x1];
				batch[j][y1][x1]=batch[j][y2][x2];
				batch[j][y2][x2]=temp;
		}
	}
}

bool check_filled() {
	bool to_ret = true;
	for(int i=0;i<5;i++) {
		for(int j=1;j<3;j++) {
			bool tmp = false;
			for(int k=0;k<12;k+=4) {
				if(batch[k][i][j]!=0) tmp = true;
			}
			if(batch[12][i][j-1]!=0) tmp = true;
			to_ret = to_ret & tmp;
		}
	}
	return to_ret;
}

bool find_c4(int day, int session) {
	/* 
		function for class c4
		should handle 12 to 15 batches
	*/
	if(labs_class_count[3]==6) {
		/* checks wether atleast one lab has practical at a point of time */
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
					batch[12][day][session]=labs_remaining[12][i];
					batch[13][day][session]=labs_remaining[13][j];
					batch[14][day][session]=labs_remaining[14][k];
					batch[15][day][session]=labs_remaining[15][l];
					
					lab_status[3][day][session]=true;
					
					labs_occupied[labs_remaining[12][i]][day][session+1] += 1;
					labs_occupied[labs_remaining[13][j]][day][session+1] += 1;
					labs_occupied[labs_remaining[14][k]][day][session+1] += 1;
					labs_occupied[labs_remaining[15][l]][day][session+1] += 1;
					
					if( (labs_occupied[labs_remaining[12][i]][day][session+1] > labs_maxlimit[labs_remaining[12][i]]) ||
						(labs_occupied[labs_remaining[13][j]][day][session+1] > labs_maxlimit[labs_remaining[13][j]]) ||
						(labs_occupied[labs_remaining[14][k]][day][session+1] > labs_maxlimit[labs_remaining[14][k]]) ||
						(labs_occupied[labs_remaining[15][l]][day][session+1] > labs_maxlimit[labs_remaining[15][l]])
						) {
						batch[12][day][session]=0;
						batch[13][day][session]=0;
						batch[14][day][session]=0;
						batch[15][day][session]=0;
						
						lab_status[3][day][session]=false;
						
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
					}
					
					else {
						bool possible=false;
						if(session==2)
							possible = find_c4(day+1,0);
						else
							possible = find_c4(day,session+1);
						if(possible)
							return true;
						else {
							batch[12][day][session]=0;
							batch[13][day][session]=0;
							batch[14][day][session]=0;
							batch[15][day][session]=0;
							
							lab_status[3][day][session]=false;
							
							/* revert labs_reaining array */
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


bool find_c3(int day, int session) {
	/* 
		function for class c3
		should handle 8 to 11 batches
	*/
	if(labs_class_count[2]==6) {
		if(find_c4(0,0)) {
			return true;
		}
		else {
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
					batch[8][day][session]=labs_remaining[8][i];
					batch[9][day][session]=labs_remaining[9][j];
					batch[10][day][session]=labs_remaining[10][k];
					batch[11][day][session]=labs_remaining[11][l];
					
					lab_status[2][day][session]=true;
					
					labs_occupied[labs_remaining[8][i]][day][session] += 1;
					labs_occupied[labs_remaining[9][j]][day][session] += 1;
					labs_occupied[labs_remaining[10][k]][day][session] += 1;
					labs_occupied[labs_remaining[11][l]][day][session] += 1;
					
					if( (labs_occupied[labs_remaining[8][i]][day][session] > labs_maxlimit[labs_remaining[8][i]]) ||
						(labs_occupied[labs_remaining[9][j]][day][session] > labs_maxlimit[labs_remaining[9][j]]) ||
						(labs_occupied[labs_remaining[10][k]][day][session] > labs_maxlimit[labs_remaining[10][k]]) ||
						(labs_occupied[labs_remaining[11][l]][day][session] > labs_maxlimit[labs_remaining[11][l]])
						) {
						batch[8][day][session]=0;
						batch[9][day][session]=0;
						batch[10][day][session]=0;
						batch[11][day][session]=0;
						
						lab_status[2][day][session]=false;
						
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
					}
					
					else {
						bool possible=false;
						if(session==2)
							possible = find_c3(day+1,0);
						else
							possible = find_c3(day,session+1);
						if(possible)
							return true;
						else {
							batch[8][day][session]=0;
							batch[9][day][session]=0;
							batch[10][day][session]=0;
							batch[11][day][session]=0;
							
							lab_status[2][day][session]=false;
							
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

bool find_c2(int day, int session) {
	/* 
		function for class c2
		should handle 4 to 7 batches
	*/
	if(labs_class_count[1]==6) {
		if(find_c3(0,0)) {
			return true;
		}
		else {
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
					batch[4][day][session]=labs_remaining[4][i];
					batch[5][day][session]=labs_remaining[5][j];
					batch[6][day][session]=labs_remaining[6][k];
					batch[7][day][session]=labs_remaining[7][l];
					
					lab_status[1][day][session]=true;
					
					labs_occupied[labs_remaining[4][i]][day][session] += 1;
					labs_occupied[labs_remaining[5][j]][day][session] += 1;
					labs_occupied[labs_remaining[6][k]][day][session] += 1;
					labs_occupied[labs_remaining[7][l]][day][session] += 1;
					
					if( (labs_occupied[labs_remaining[4][i]][day][session] > labs_maxlimit[labs_remaining[4][i]]) ||
						(labs_occupied[labs_remaining[5][j]][day][session] > labs_maxlimit[labs_remaining[5][j]]) ||
						(labs_occupied[labs_remaining[6][k]][day][session] > labs_maxlimit[labs_remaining[6][k]]) ||
						(labs_occupied[labs_remaining[7][l]][day][session] > labs_maxlimit[labs_remaining[7][l]])
						) {
						batch[4][day][session]=0;
						batch[5][day][session]=0;
						batch[6][day][session]=0;
						batch[7][day][session]=0;
						
						lab_status[1][day][session]=false;
						
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
					}
					
					else {
						bool possible=false;
						if(session==2)
							possible = find_c2(day+1,0);
						else
							possible = find_c2(day,session+1);
						if(possible)
							return true;
						else {
							batch[4][day][session]=0;
							batch[5][day][session]=0;
							batch[6][day][session]=0;
							batch[7][day][session]=0;
							
							lab_status[1][day][session]=false;
							
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


bool find_c1(int day, int session) {
	/* 
		function for class c1
		should handle first 4 batches
	*/
	if(labs_class_count[0]==6) {
		if(find_c2(0,0)) {
			return true;
		}
		else {
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
					batch[0][day][session]=labs_remaining[0][i];
					batch[1][day][session]=labs_remaining[1][j];
					batch[2][day][session]=labs_remaining[2][k];
					batch[3][day][session]=labs_remaining[3][l];
					
					lab_status[0][day][session]=true;
					
					labs_occupied[labs_remaining[0][i]][day][session] += 1;
					labs_occupied[labs_remaining[1][j]][day][session] += 1;
					labs_occupied[labs_remaining[2][k]][day][session] += 1;
					labs_occupied[labs_remaining[3][l]][day][session] += 1;
					
					if( (labs_occupied[labs_remaining[0][i]][day][session] > labs_maxlimit[labs_remaining[0][i]]) ||
						(labs_occupied[labs_remaining[1][j]][day][session] > labs_maxlimit[labs_remaining[1][j]]) ||
						(labs_occupied[labs_remaining[2][k]][day][session] > labs_maxlimit[labs_remaining[2][k]]) ||
						(labs_occupied[labs_remaining[3][l]][day][session] > labs_maxlimit[labs_remaining[3][l]])
						) {
						batch[0][day][session]=0;
						batch[1][day][session]=0;
						batch[2][day][session]=0;
						batch[3][day][session]=0;
						
						lab_status[0][day][session]=false;
						
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
					}
					
					else {
						bool possible=false;
						if(session==2)
							possible = find_c1(day+1,0);
						else
							possible = find_c1(day,session+1);
						if(possible)
							return true;
						else {
							batch[0][day][session]=0;
							batch[1][day][session]=0;
							batch[2][day][session]=0;
							batch[3][day][session]=0;
							
							lab_status[0][day][session]=false;
							
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

int main() {
	init();
	find_c1(0,0);
	while(!check_filled())
	 randomise();
	int current_count_for_print=1;
	for(int i=0;i<16;i++) {
		if(i%4==0) {
			cout<<"Class SE"<<current_count_for_print<<"\n\n";
			current_count_for_print+=1;
		}
		for(int j=0;j<3;j++) {
			for(int k=0;k<5;k++) {
				switch(batch[i][k][j]) {
				case 0:
					cout<<".... ";
					break;
				case 1:
					cout<<"DSPS ";
					break;
				case 2:
					cout<<"DELD ";
					break;
				case 3:
					cout<<"OSA  ";
					break;
				case 4:
					cout<<"SSL  ";
					break;
				case 5:
					cout<<"MPA  ";
					break;
				}
			}
			cout<<"\n";
		}
		cout<<"\n";
		if(i%4==3) {
			cout<<"------------------------------------------------\n";
		}
	}
	
	for(int j=1;j<3;j++) {
		for(int i=0;i<5;i++) {
			bool tmp = false;
			for(int k=0;k<12;k+=4) {
				if(batch[k][i][j]!=0) tmp = true;
			}
			if(batch[12][i][j-1]!=0) tmp = true;
			cout<<tmp<<" ";
		}
		cout<<"\n";
	}
	
}
