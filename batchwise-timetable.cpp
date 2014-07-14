#include <iostream>
#include <string>
using namespace std;

string batch[16][5][3];

bool check() {
	for(int i=0;i<5;i++) {
		for(int j=0;j<3;j++) {
			int count=0;
			for(int k=0;k<4;k++) {
				if(batch[k][i][j]=="") count+=1;
			}
			cout<<"count= "<<count<<"\n";
			if(count!=0 && count!=4) return false;
		}
	}
	for(int i=0;i<5;i++) {
		for(int j=0;j<3;j++) {
			int count=0;
			for(int k=4;k<8;k++) {
				if(batch[k][i][j]=="") count+=1;
			}
			if(count!=0 && count!=4) return false;
		}
	}
	for(int i=0;i<5;i++) {
		for(int j=0;j<3;j++) {
			int count=0;
			for(int k=8;k<12;k++) {
				if(batch[k][i][j]=="") count+=1;
			}
			if(count!=0 && count!=4) return false;
		}
	}
	for(int i=0;i<5;i++) {
		for(int j=0;j<3;j++) {
			int count=0;
			for(int k=12;k<16;k++) {
				if(batch[k][i][j]=="") count+=1;
			}
			if(count!=0 && count!=4) return false;
		}
	}
	return true;

}

bool find_l5(int batch_number) {
	for(int i=0;i<5;i++) {
		for(int p=0;p<3;p++) {
			int count1=0;
			if(batch[batch_number][i][p]!="") continue;
			for(int k=0;k<batch_number;k++) {
				if(batch_number < 12 && k < 12 ) {
					if(batch[k][i][p]=="l5") count1 += 1;
				}
				else if(batch_number >= 12 && k<12 ) {
					if( (p+1)<3 && batch[k][i][p+1]=="l5") count1 += 1;
				}
				else if(batch_number >=12 && k>=12) {
					if(batch[k][i][p]=="l5") count1 += 1;
				}
			}
			if(count1==2) continue;
			else {
				batch[batch_number][i][p]="l5";
				if(batch_number==15) {
					if(check()) {
						return true;
					}
					else {
						batch[batch_number][i][p]="";
						return false;
					}
				}
				if(find_l5(batch_number+1)) return true;
				else {
					batch[batch_number][i][p]="";
				}
			}
		}
	}
}

bool find_l4(int batch_number) {
	for(int i=0;i<5;i++) {
		for(int p=0;p<3;p++) {
			int count1=0;
			if(batch[batch_number][i][p]!="") continue;
			for(int k=0;k<batch_number;k++) {
				if(batch_number < 12 && k < 12 ) {
					if(batch[k][i][p]=="l4") count1 += 1;
				}
				else if(batch_number >= 12 && k<12 ) {
					if( (p+1)<3 && batch[k][i][p+1]=="l4") count1 += 1;
				}
				else if(batch_number >=12 && k>=12) {
					if(batch[k][i][p]=="l4") count1 += 1;
				}
			}
			if(count1==2) continue;
			else {
				batch[batch_number][i][p]="l4";
				if(batch_number==15) {
					if(find_l5(0)) return true;
					else {
						batch[batch_number][i][p]="";
						return false;
					}
				}
				if(find_l4(batch_number+1)) return true;
				else {
					batch[batch_number][i][p]="";
				}
			}
		}
	}
}

bool find_l3(int batch_number) {
	for(int i=0;i<5;i++) {
		for(int p=0;p<3;p++) {
			int count1=0;
			if(batch[batch_number][i][p]!="") continue;
			for(int k=0;k<batch_number;k++) {
				if(batch_number < 12 && k < 12 ) {
					if(batch[k][i][p]=="l3") count1 += 1;
				}
				else if(batch_number >= 12 && k<12 ) {
					if( (p+1)<3 && batch[k][i][p+1]=="l3") count1 += 1;
				}
				else if(batch_number >=12 && k>=12) {
					if(batch[k][i][p]=="l3") count1 += 1;
				}
			}
			if(count1==2) continue;
			else {
				batch[batch_number][i][p]="l3";
				if(batch_number==15) {
					if(find_l4(0)) return true;
					else {
						batch[batch_number][i][p]="";
						return false;
					}
				}
				if(find_l3(batch_number+1)) return true;
				else {
					batch[batch_number][i][p]="";
				}
			}
		}
	}
}

bool find_l2(int batch_number) {
	for(int i=0;i<5;i++) {
		for(int p=0;p<3;p++) {
			int count1=0;
			if(batch[batch_number][i][p]!="") continue;
			for(int k=0;k<batch_number;k++) {
				if(batch_number < 12 && k < 12 ) {
					if(batch[k][i][p]=="l2") count1 += 1;
				}
				else if(batch_number >= 12 && k<12 ) {
					if( (p+1)<3 && batch[k][i][p+1]=="l2") count1 += 1;
				}
				else if(batch_number >=12 && k>=12) {
					if(batch[k][i][p]=="l2") count1 += 1;
				}
			}
			if(count1==1) continue;
			else {
				batch[batch_number][i][p]="l2";
				if(batch_number==15) {
					if(find_l3(0)) return true;
					else {
						batch[batch_number][i][p]="";
						return false;
					}
				}
				if(find_l2(batch_number+1)) return true;
				else {
					batch[batch_number][i][p]="";
				}
			}
		}
	}
}

bool find_l1(int batch_number) {
	for(int i=0;i<5;i++) {
		for(int j=i+1;j<5;j++) {
			for(int p=0;p<3;p++) {
				for(int q=0;q<3;q++) {
					int count1=0, count2=0;
					for(int k=0;k<batch_number;k++) {
						if(batch_number < 12 && k < 12 ) {
							if(batch[k][i][p]=="l1") count1 += 1;
							if(batch[k][j][q]=="l1") count2 += 1;
						}
						else if(batch_number >= 12 && k < 12 ) {
							if( (p+1)<3 && batch[k][i][p+1]=="l1") count1 += 1;
							if( (q+1)<3 && batch[k][j][q+1]=="l1") count2 += 1;
						}
						else if(batch_number >=12 && k>= 12 ) {
							if(batch[k][i][p]=="l1") count1 += 1;
							if(batch[k][j][q]=="l1") count2 += 1;
						}
					}
					if(count1==2 || count2==2) continue;
					else {
						batch[batch_number][i][p]="l1";
						batch[batch_number][j][q]="l1";
						if(batch_number==15) {
							if(find_l2(0)) return true;
							else {
								batch[batch_number][i][p]="";
								batch[batch_number][j][q]="";
								return false;
							}
						}
						if(find_l1(batch_number+1)) return true;
						else {
							batch[batch_number][i][p]="";
							batch[batch_number][j][q]="";
						}
					}
				}
			}
		}
	}
}

int main() {
	find_l1(0);
	for(int i=0;i<16;i++) {
		for(int j=0;j<3;j++) {
			for(int k=0;k<5;k++) {
				if(batch[i][k][j]!="") cout<<batch[i][k][j]<<" ";
				else cout<<".. ";
			}
			cout<<endl;
		} 
		cout<<"\n\n\n\n\n";
	}
}
