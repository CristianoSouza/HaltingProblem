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
    int numero_linhas;
    int parametro_entrada;
    int R0, R1, R2, R3, R4, R5, R6, R7, R8, R9;
    char comando[5], operador[8];
    string operador1, operador2;

    
    //while(1){

        scanf("%i", &numero_linhas);
        scanf("%i", &parametro_entrada);

        if( numero_linhas == 0 && parametro_entrada == 0){
            //break;             
        } else {
            R1, R2, R3, R4, R5, R6, R7, R8, R9 = 0;

            for ( int i = 1; i<= numero_linhas; i++) {

                scanf(" %s", &comando);

                cout << "linha: " << comando << endl;

                if (strcmp(comando, "ENDIF") == 0) {
                    cout << "ENDIF" << endl;
                } else{
                    if (strcmp(comando, "CALL") == 0) {
                        //call
                        scanf(" %s\n", &operador);
                        cout << "CALL operador: " << operador << endl;
                    } else {
                        if (strcmp(comando, "RET") == 0) {
                            scanf(" %s\n", &operador);
                            cout << "RET operador: " << operador << endl;
                        } else {
                            
                            scanf(" %s\n", &operador);

                            //SEPARAR OPERADORES POR VRGULA
                            cout << "operador = " << operador << endl;
                            operador1 = "";  
                            operador1 += operador[0];
                            operador1 += operador[1];

                            operador2 = "";  
                            operador2 += operador[3];
                            if (strlen(operador) > 3) {
                                operador2 += operador[4];
                            }

                            cout << "operador1 = " << operador1 << endl;
                            cout << "operador2 = " << operador2 << endl;
                            if (strcmp(comando, "MOV") == 0) {
                                cout << "MOV operador1: " << operador1 << endl;
                                cout << "MOV operador2: " << operador2 << endl;
                            } else {
                                if (strcmp(comando, "ADD") == 0) {
                                    cout << "ADD operador1: " << operador1 << endl;
                                    cout << "ADD operador2: " << operador2 << endl;
                                } else {
                                    if (strcmp(comando, "SUB") == 0) {
                                        cout << "SUB operador1: " << operador1 << endl;
                                        cout << "SUB operador2: " << operador2 << endl;
                                    } else {
                                        if (strcmp(comando, "DIV") == 0) {
                                            cout << "DIV operador1: " << operador1 << endl;
                                            cout << "DIV operador2: " << operador2 << endl;
                                        } else {
                                            if (strcmp(comando, "MOD") == 0) {
                                                cout << "MOD operador1: " << operador1 << endl;
                                                cout << "MOD operador2: " << operador2 << endl;
                                            } else {
                                                if (strcmp(comando, "IFEQ") == 0) {
                                                    cout << "IFEQ operador1: " << operador1 << endl;
                                                    cout << "IFEQ operador2: " << operador2 << endl;
                                                } else {
                                                    if (strcmp(comando, "IFNEQ") == 0) {
                                                        cout << "IFNEQ operador1: " << operador1 << endl;
                                                        cout << "IFNEQ operador2: " << operador2 << endl;
                                                    } else {
                                                        if (strcmp(comando, "IFG") == 0) {
                                                            cout << "IFG operador1: " << operador1 << endl;
                                                            cout << "IFG operador2: " << operador2 << endl;
                                                        } else {
                                                            if (strcmp(comando, "IFL") == 0) {
                                                                cout << "IFL operador1: " << operador1 << endl;
                                                                cout << "IFL operador2: " << operador2 << endl;
                                                            } else {
                                                                if (strcmp(comando, "IFGE") == 0) {
                                                                    cout << "IFGE operador1: " << operador1 << endl;
                                                                    cout << "IFGE operador2: " << operador2 << endl;
                                                                } else {
                                                                    if (strcmp(comando, "IFLE") == 0) {
                                                                        cout << "IFLE operador1: " << operador1 << endl;
                                                                        cout << "IFLE operador2: " << operador2 << endl;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
        iterador++;
    //}
    return 0;
}
