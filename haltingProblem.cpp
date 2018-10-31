#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using std::string;
using std::getline;
using namespace std;


int main() {

    int iterador= 1;
    char simbolo_inicial[5];

    scanf("%s", simbolo_inicial);
    while(1){

        iterador++;
        if(scanf("%s", simbolo_inicial) != EOF){
            cout << endl;
        } else {
            break;
        }
    }
    return 0;
}
