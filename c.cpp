#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>

using std::string;
using std::getline;
using namespace std;

int programa_24(int entrada, int *r9){
	int r0 = entrada;
	cout << entrada << endl;
	int r1= 0, r2= 0, r3= 0;
	if (r0 <= 1) {
		*r9 = r0;
		return 0;
	}
	r1 = r0;
	r1 = r1 - 1;
	programa_24(r1, r9);
	r3 = *r9;
	r2 = r0;
	r2 = r2 - 2;
	programa_24(r2, r9);
	r3 = r3 + *r9;
	*r9 = r3;
	return 0;
}

int programa_25(int entrada){
	//cout << entrada << endl;
	int r0 = entrada;
	int r1= 0, r2= 0, r3= 0, r9;
	if (r0 <= 1) {
		return r0;
	}
	r1 = r0;
	r1 = r1 - 1;
	if (r1 < 0) {
		r1= (r1 % 1000) + 1000;
	}
	r9 = programa_25(r1);
	r3 = r9;
	r2 = r0;
	r2 = r2 - 2;
	if (r2 < 0) {
		r2 = (r2 % 1000) + 1000;
	}
	r9 = programa_25(r2);
	r3 = r3 + r9;
	if (r3 > 999) {
		r3 = r3 % 1000;
	}
	//cout << "Saida: " << r3 << endl;
	return r3;
}



int main() {
	int r9 = 0;
    //cout << "Result: " << programa_24(256, &r9) << endl;
    cout << "Result: " << programa_25(999) << endl;
}