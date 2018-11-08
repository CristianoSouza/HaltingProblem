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

int procuraENDIF( vector<string> vetor_comandos, int linha) {
    
    while( vetor_comandos[linha].compare("ENDIF") != 0) {
        linha++;
    }
    return linha;
}

int procura_CALL_antes_RET(vector<string> vetor_comandos){
    int linha = 0;
    int espera = -1;
    while( vetor_comandos[linha].compare("RET") != 0) {
        if (vetor_comandos[linha][0] == 'I' ){
            espera = procuraENDIF(vetor_comandos, linha);
        } else {
            if (linha > espera) {
                if( vetor_comandos[linha].compare("CALL") == 0 ) {
                    return 1;
                }
            }
        }
        linha++;
    }
    return 0;
}

/*int procura_CALL_antes_RET(vector<string> vetor_comandos){
    int linha = 0;
    int espera = -1;
    while( vetor_comandos[linha].compare("RET") != 0) {

        if( vetor_comandos[linha].compare("CALL") == 0 ) {
            return 1;
        }
        linha++;
    }
    return 0;
}*/

int verifica_RET_dentro_IF (vector<string> vetor_comandos, int linha) {
    while( vetor_comandos[linha].compare("ENDIF") != 0) {
        if (vetor_comandos[linha].compare("RET") == 0){
            return 1;
        }
    }
    return 0;
}



int programa(vector<string> comandos, vector<string> operadores1, vector<string> operadores2, int entrada, int *loop, int cache[1000], int *qcalls){
    map <string, int> registradores;
    //cout << "Entrada: " << entrada << endl;
    int entrada_proxima_chamada;
    registradores["R0"] = entrada;
    registradores["R1"] = 0;
    registradores["R2"] = 0;
    registradores["R3"] = 0;
    registradores["R4"] = 0;
    registradores["R5"] = 0;
    registradores["R6"] = 0;
    registradores["R7"] = 0;
    registradores["R8"] = 0;
    registradores["R9"] = 0;
    int valor_saida = 0;


    //cout << registradores["QCALLS"] << endl;
    //cout << "loop>: " << registradores["LOOP"] << endl;
    if (*loop == 1) {
        return 0;
    } else {
        for ( int i = 0; i< comandos.size(); i++) {
            //cout << i << endl;
            //cout << "comandos: " << comandos[i] << endl;
            //cout << "call:  " << *qcalls << endl;
            string operador1 = operadores1[i];
            string operador2 = operadores2[i];
            //cout << "CONT: " << *cont << endl;
            if (comandos[i].compare("CALL") == 0) {
                //cout << "CALL operador1: " << operador1 << endl;
                *qcalls = *qcalls + 1;
                //cout << "Q" << operador1 << ": " << registradores["Q" +operador1] << endl;
                //cout << "QCALLS: " << *qcalls << endl;
                if (*qcalls > 300){
                    //*loop = 1;
                    //return 0;
                }


                if (operador1[0] == 'R') {
                    entrada_proxima_chamada = registradores[operador1];
                } else {
                    entrada_proxima_chamada =  atoi (operador1.c_str() );
                }
                //registradores["R0"] = entrada_proxima_chamada;
                //cout << "R0: " << registradores["R0"] << endl;
                //cout << "quantidade_calls: "<< registradores["QCALLS"]  << endl;
                //cout << "R0 ida: " << registradores["R0"] << endl;
                //cout << "Entrada ida: " << entrada_proxima_chamada << endl;

                if(cache[entrada_proxima_chamada] != 0) {
                    valor_saida = cache[entrada_proxima_chamada];
                    //cout << "cache: " << cache[entrada_proxima_chamada] << endl;
                } else {
                    valor_saida = programa(comandos, operadores1, operadores2, entrada_proxima_chamada, loop, cache, qcalls);
                    cache[entrada_proxima_chamada] = valor_saida;
                }
                
                //cout << "valor saida: " << valor_saida << endl;
                registradores["R9"] = valor_saida;
                
            } else {
                if (comandos[i].compare("RET") == 0){
                    //cout << "RET operador1: " << operador1 << endl;
                    //cout << "atoi:  " << atoi (operador1.c_str() ) << endl;
                    int saida;
                    if (operador1[0] == 'R') {
                        saida = registradores[operador1];
                    } else {
                        //cout << "atoi:  " << atoi (operador1.c_str() ) << endl;
                        saida =  atoi (operador1.c_str() );
                    }
                    
                    
                    registradores["R9"] = saida;
                    //cout << "R9 saida: " << registradores["R9"] << endl;
                    //cout << "saida volta: " << saida << endl;
                    //i = comandos.size();
                    *qcalls = *qcalls - 1;
                    return saida;
                } else {
                    if (comandos[i].compare("MOV") == 0) {
                        //cout << "--------------------" << endl;
                        //cout << "MOV operador1: " << operador1 << endl;
                        //cout << "MOV operador2: " << operador2 << endl;
                        //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                        if (operador2[0] == 'R') {
                            //cout << "REGISTRADOR " << operador2 << ": " << registradores[operador2] << endl;
                            registradores[operador1] = registradores[operador2];
                        } else {
                            registradores[operador1] = atoi (operador2.c_str() );
                        }
                        //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                    } else {
                        if (comandos[i].compare("ADD") == 0) {
                            //cout << "--------------------" << endl;
                            //cout << "ADD operador1: " << operador1 << endl;
                            //cout << "ADD operador2: " << operador2 << endl;
                            //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                            if (operador2[0] == 'R') {
                                //cout << "REGISTRADOR " << operador2 << ": " << registradores[operador2] << endl;
                                registradores[operador1] = registradores[operador1] + registradores[operador2];
                            } else {
                                registradores[operador1] = registradores[operador1] + atoi (operador2.c_str() );
                            }
                            if (registradores[operador1] > 999){
                                registradores[operador1] = registradores[operador1] % 1000;
                            }
                            //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                        } else {
                            if (comandos[i].compare("SUB") == 0) {
                                //cout << "--------------------" << endl;
                                //cout << "SUB operador1: " << operador1 << endl;
                                //cout << "SUB operador2: " << operador2 << endl;
                                //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                if (operador2[0] == 'R') {
                                    //cout << "REGISTRADOR " << operador2 << ": " << registradores[operador2] << endl;
                                    registradores[operador1] = registradores[operador1] - registradores[operador2];
                                } else {
                                    registradores[operador1] = registradores[operador1] - atoi (operador2.c_str() );
                                }
                                if (registradores[operador1] < 0){
                                    registradores[operador1] = (registradores[operador1] % 1000) + 1000;
                                }
                                //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                            } else {
                                if (comandos[i].compare("MUL") == 0) {
                                    //cout << "MUL operador1: " << operador1 << endl;
                                    //cout << "MUL operador2: " << operador2 << endl;
                                    //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                    if (operador2[0] == 'R') {
                                        //cout << "REGISTRADOR " << operador2 << ": " << registradores[operador2] << endl;
                                        registradores[operador1] = registradores[operador1] * registradores[operador2];
                                    } else {
                                        registradores[operador1] = registradores[operador1] * atoi (operador2.c_str() );
                                    }
                                    if (registradores[operador1] > 999){
                                        registradores[operador1] = registradores[operador1] % 1000;
                                    }
                                    //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                } else {
                                    if (comandos[i].compare("DIV") == 0) {
                                        //cout << "DIV operador1: " << operador1 << endl;
                                        //cout << "DIV operador2: " << operador2 << endl;
                                        //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                        if (operador2[0] == 'R') {
                                            if (registradores[operador2] != 0 ) {
                                               //cout << "REGISTRADOR " << operador2 << ": " << registradores[operador2] << endl;
                                                registradores[operador1] = registradores[operador1] / registradores[operador2];
                                            } else {
                                                registradores[operador1] = 0;
                                            }
                                        } else {
                                            if (atoi (operador2.c_str()) != 0) {
                                                registradores[operador1] = registradores[operador1] / atoi (operador2.c_str() );
                                            } else {
                                                registradores[operador1] = 0;
                                            }
                                        }
                                        //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                    } else {
                                        if (comandos[i].compare("MOD") == 0) {
                                            //cout << "MOD operador1: " << operador1 << endl;
                                            //cout << "MOD operador2: " << operador2 << endl;
                                            //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                            if (operador2[0] == 'R') {
                                                //cout << "REGISTRADOR " << operador2 << ": " << registradores[operador2] << endl;
                                                if (registradores[operador2] != 0 ) {
                                                    registradores[operador1] = registradores[operador1] % registradores[operador2];
                                                } else {
                                                    registradores[operador1] = 0;
                                                }
                                            } else {
                                                if (atoi (operador2.c_str()) != 0) {
                                                    registradores[operador1] = registradores[operador1] % atoi (operador2.c_str() );
                                                } else {
                                                    registradores[operador1] = 0;
                                                }
                                            }
                                            //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                        } else {
                                            int valor1; 
                                            int valor2;
                                            int linha; 
                                            if (operador1[0] == 'R'){
                                                valor1 = registradores[operador1];
                                            } else {
                                                valor1 = atoi (operador1.c_str() );
                                            }
                                            if (operador2[0] == 'R'){
                                                valor2 = registradores[operador2];
                                            } else {
                                                valor2 = atoi (operador2.c_str() );
                                            }

                                            if (comandos[i].compare("IFEQ") == 0) {
                                                //cout << "aaaa" << endl;
                                                //cout << "IFEQ operador1: " << operador1 << endl;
                                                //cout << "IFEQ operador2: " << operador2 << endl;
                                                //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                //cout << "REGISTRADOR " << operador2 << ": " << registradores[operador2] << endl;
                                                
                                                if (valor1 != valor2){
                                                    i = procuraENDIF(comandos, i);
                                                } else {
                                                    linha = i;
                                                    while( comandos[linha].compare("ENDIF") != 0) {
                                                        //cout << "Operadores1[linha]: "<< operadores1[linha] << endl; 
                                                        //cout << "operador1: " << operador1 << endl;
                                                        if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                            *loop = 1;
                                                            return 0;
                                                        }
                                                        linha++;

                                                     }
                                                }                       
                                                //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                            } else {
                                                if (comandos[i].compare("IFNEQ") == 0) {
                                                    //cout << "IFNEQ operador1: " << operador1 << endl;
                                                    //cout << "IFNEQ operador2: " << operador2 << endl;
                                                    //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                    if (valor1 == valor2){
                                                        i = procuraENDIF(comandos, i);
                                                    } else {
                                                        linha = i;
                                                        while( comandos[linha].compare("ENDIF") != 0) {
                                                            //cout << "Operadores1[linha]: "<< operadores1[linha] << endl; 
                                                            //cout << "operador1: " << operador1 << endl;
                                                            if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                *loop = 1;
                                                                return 0;
                                                            }
                                                            linha++;

                                                        }
                                                    }    
                                                    //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                } else {
                                                    if (comandos[i].compare("IFG") == 0) {
                                                        //cout << "IFG operador1: " << operador1 << endl;
                                                        //cout << "IFG operador2: " << operador2 << endl;
                                                        //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                        if (valor1 <= valor2){
                                                            i = procuraENDIF(comandos, i);
                                                        } else {
                                                            linha = i;
                                                            while( comandos[linha].compare("ENDIF") != 0) {
                                                                //cout << "Operadores1[linha]: "<< operadores1[linha] << endl; 
                                                                //cout << "operador1: " << operador1 << endl;
                                                                if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                    *loop = 1;
                                                                    return 0;
                                                                }
                                                                linha++;

                                                            }
                                                        }    
                                                        //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                    } else {
                                                        if (comandos[i].compare("IFL") == 0) {
                                                            //cout << "IFL operador1: " << operador1 << endl;
                                                            //cout << "IFL operador2: " << operador2 << endl;
                                                            //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                            if (valor1 >= valor2){
                                                                i = procuraENDIF(comandos, i);
                                                            } else {
                                                                linha = i;
                                                                while( comandos[linha].compare("ENDIF") != 0) {
                                                                    //cout << "Operadores1[linha]: "<< operadores1[linha] << endl; 
                                                                    //cout << "operador1: " << operador1 << endl;
                                                                    if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                        *loop = 1;
                                                                        return 0;
                                                                    }
                                                                    linha++;

                                                                }
                                                            }    
                                                            //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                        } else {
                                                            if (comandos[i].compare("IFGE") == 0) {
                                                                //cout << "IFGE operador1: " << operador1 << endl;
                                                                //cout << "IFGE operador2: " << operador2 << endl;
                                                                //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                                if (valor1 < valor2){
                                                                    i = procuraENDIF(comandos, i);
                                                                } else {
                                                                    linha = i;
                                                                    while( comandos[linha].compare("ENDIF") != 0) {
                                                                        //cout << "Operadores1[linha]: "<< operadores1[linha] << endl; 
                                                                        //cout << "operador1: " << operador1 << endl;
                                                                        if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                            *loop = 1;
                                                                            return 0;
                                                                        }
                                                                        linha++;

                                                                    }
                                                                }    
                                                                //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                            } else {
                                                                if (comandos[i].compare("IFLE") == 0) {
                                                                    //cout << "IFLE operador1: " << operador1 << endl;
                                                                    //cout << "IFLE operador2: " << operador2 << endl;
                                                                    //cout << "valor1: " << valor1 << endl;
                                                                    //cout << "valor2: " << valor2 << endl; 
                                                                    //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
                                                                    if (valor1 > valor2){
                                                                        i = procuraENDIF(comandos, i);
                                                                    } else {
                                                                        linha = i;
                                                                        while( comandos[linha].compare("ENDIF") != 0) {
                                                                            //cout << "Operadores1[linha]: "<< operadores1[linha] << endl; 
                                                                            //cout << "operador1: " << operador1 << endl;
                                                                            if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                                *loop = 1;
                                                                                return 0;
                                                                            }
                                                                            linha++;

                                                                        }
                                                                    }    
                                                                    //cout << "REGISTRADOR " << operador1 << ": " << registradores[operador1] << endl;
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
}

int main() {

    int iterador= 1;
    int numero_linhas;
    int parametro_entrada;
    char comando[5], operador[8];
    string operador1, operador2;
    
    while(1){
        //cout<< "INSTANCIA " << iterador << endl;
        scanf("%i", &numero_linhas);
        scanf("%i", &parametro_entrada);

        if( numero_linhas == 0 && parametro_entrada == 0){
            break;             
        } else {
            vector<string> comandos;
            vector<string> operadores1;
            vector<string> operadores2;


            //lendo e preenchendo vetores de comandos e operadores 
            for ( int i = 1; i<= numero_linhas; i++) {

                scanf(" %s", &comando);

                //cout << "linha: " << comando << endl;
                comandos.push_back(comando);

                if (strcmp(comando, "ENDIF") != 0) {
                    scanf(" %s", &operador);
                    //cout << "operador = " << operador << endl;
                    int tamanho_operador = strlen(operador);

                    if(operador[2] != ',') {
                        operador1 = "";
                        int i = 0; 
                        while( i < tamanho_operador){
                            operador1 += operador[i];
                            i++;
                        }
                        //cout << "operador1 = " << operador1 << endl;
                        operadores1.push_back(operador1);
                        operadores2.push_back("*");
                    } else {
                        operador1 = "";
                        operador2 = "";
                        int i = 0;  
                        while(operador[i] != ','){
                            operador1 += operador[i];
                            i++;
                        }
                        i++;  
                        while( i < tamanho_operador){
                            operador2 += operador[i];
                            i++;
                        }
                        //cout << "operador1 = " << operador1 << endl;
                        //cout << "operador2 = " << operador2 << endl;
                        operadores1.push_back(operador1);
                        operadores2.push_back(operador2);
                    }
                } else {
                    operadores1.push_back("*");
                    operadores2.push_back("*");
                }
            }

            /*for (int iterador_palavras=0; iterador_palavras < comandos.size(); iterador_palavras++) {
                cout << "comandos: " << comandos[iterador_palavras] << endl;
                cout << "operador1: " << operadores1[iterador_palavras] << endl;
                cout << "operador2: " << operadores2[iterador_palavras] << endl;
            }*/

            if (procura_CALL_antes_RET(comandos) == 1) {
                //cout << iterador << ": " << "*" << endl; 
                cout << "*" << endl;
            } else {

            //inicio do algoritmo
                int cont = 0;
                int loop = 0;
                int qcalls = 0;
                int cache[1000];
                for(int j= 0; j <= 999; j++) {
                    cache[j] = 0;
                }
                //cout << &qcalls << endl;
                int result = programa(comandos, operadores1, operadores2, parametro_entrada, &loop, cache, &qcalls);
                if ( loop == 1){
                    //cout << iterador << ": " << "*" << endl;
                    cout << "*" << endl;
                } else {
                    //cout << iterador << ": " << result << endl;
                    cout << result << endl;
                
                }
            }
        }
        iterador++;
    }
    return 0;
}
