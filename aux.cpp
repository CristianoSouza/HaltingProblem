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

//funcao para descobrir a linha de fim de um IF
int procuraENDIF( vector<string> vetor_comandos, int linha) {
    while( vetor_comandos[linha].compare("ENDIF") != 0) {
        linha++;
    }
    return linha;
}

//funcao para percorrer vetor de comandos verificando se existe algum CALL antes do primeiro RET
//não considera os CALLs dentro de IFs
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


int programa(vector<string> comandos, vector<string> operadores1, vector<string> operadores2, int entrada, int *loop, int cache[1000]){
    //cria estrura dos registradores
    map <string, int> registradores;
    int entrada_proxima_chamada;

    //inicializa o registrador R0 com a entrada passada por parametro
    registradores["R0"] = entrada;
    //inicializa os demais registradores com 0
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

    //se ja foi detectado um loop infinito entao retorna 
    if (*loop == 1) {
        return 0;
    } else {
        //caso contrario executa o programa
        //loop para percorrer o vetor de comandos
        for ( int i = 0; i< comandos.size(); i++) {
            
            string operador1 = operadores1[i];
            string operador2 = operadores2[i];

            //compara o comando com "CALL"
            if (comandos[i].compare("CALL") == 0) {
                //verifica se operador é registrador ou valor 
                if (operador1[0] == 'R') {
                    entrada_proxima_chamada = registradores[operador1];
                } else {
                    entrada_proxima_chamada =  atoi (operador1.c_str() );
                }
                //verifica se ja existe uma resposta armazenada em cache para esse subproblema
                if(cache[entrada_proxima_chamada] != 0) {
                    //caso ja existe resposta, a saida sera a resposta armazenada na cache
                    valor_saida = cache[entrada_proxima_chamada];
                } else {
                    //caso contrario, realiza-se a execução do subproblema
                    valor_saida = programa(comandos, operadores1, operadores2, entrada_proxima_chamada, loop, cache);
                    //saida obtida com a execucao do subproblema é armazenada na cache
                    cache[entrada_proxima_chamada] = valor_saida;
                }
                //atribui o valor de saida para o registrador R9
                registradores["R9"] = valor_saida;
            } else {
                //compara o comando com "RET"
                if (comandos[i].compare("RET") == 0){
                    int saida;
                    //verifica se operador é registrador ou valor 
                    if (operador1[0] == 'R') {
                        saida = registradores[operador1];
                    } else {
                        saida =  atoi (operador1.c_str() );
                    }
                    //retorna o valor
                    return saida;
                } else {
                    //compara o comando com "MOV"
                    if (comandos[i].compare("MOV") == 0) {
                        //verifica se operador2 é registrador ou valor 
                        if (operador2[0] == 'R') {
                            registradores[operador1] = registradores[operador2];
                        } else {
                            registradores[operador1] = atoi (operador2.c_str() );
                        }
                    } else {
                        //compara o comando com "ADD"
                        if (comandos[i].compare("ADD") == 0) {
                            //verifica se operador2 é registrador ou valor 
                            if (operador2[0] == 'R') {
                                registradores[operador1] = registradores[operador1] + registradores[operador2];
                            } else {
                                registradores[operador1] = registradores[operador1] + atoi (operador2.c_str() );
                            }

                            //verificação para limitar os valores entre 0 e 999
                            if (registradores[operador1] > 999){
                                registradores[operador1] = registradores[operador1] % 1000;
                            }
                        } else {
                            //compara o comando com "SUB"
                            if (comandos[i].compare("SUB") == 0) {
                                //verifica se operador2 é registrador ou valor 
                                if (operador2[0] == 'R') {
                                    registradores[operador1] = registradores[operador1] - registradores[operador2];
                                } else {
                                    registradores[operador1] = registradores[operador1] - atoi (operador2.c_str() );
                                }

                                //verificação para limitar os valores entre 0 e 999
                                if (registradores[operador1] < 0){
                                    registradores[operador1] = (registradores[operador1] % 1000) + 1000;
                                }
                            } else {
                                //compara o comando com "MUL"
                                if (comandos[i].compare("MUL") == 0) {
                                    //verifica se operador2 é registrador ou valor 
                                    if (operador2[0] == 'R') {
                                        registradores[operador1] = registradores[operador1] * registradores[operador2];
                                    } else {
                                        registradores[operador1] = registradores[operador1] * atoi (operador2.c_str() );
                                    }
                                    //verificação para limitar os valores entre 0 e 999
                                    if (registradores[operador1] > 999){
                                        registradores[operador1] = registradores[operador1] % 1000;
                                    }
                                } else {
                                    //compara o comando com "DIV"
                                    if (comandos[i].compare("DIV") == 0) {
                                        //verifica se operador2 é registrador ou valor 
                                        if (operador2[0] == 'R') {
                                            //verifica se valor do operador2 é diferente de zero
                                            if (registradores[operador2] != 0 ) {
                                                registradores[operador1] = registradores[operador1] / registradores[operador2];
                                            } else {
                                                //caso contrario atribui 0 ao registrador correspondente ao operador1
                                                registradores[operador1] = 0;
                                            }
                                        } else {
                                            //verifica se valor do operador2 é diferente de zero
                                            if (atoi (operador2.c_str()) != 0) {
                                                registradores[operador1] = registradores[operador1] / atoi (operador2.c_str() );
                                            } else {
                                                //caso contrario atribui 0 ao registrador correspondente ao operador1
                                                registradores[operador1] = 0;
                                            }
                                        }
                                    } else {
                                        //compara o comando com "MOD"
                                        if (comandos[i].compare("MOD") == 0) {
                                            //verifica se operador2 é registrador ou valor 
                                            if (operador2[0] == 'R') {
                                                //verifica se valor do operador2 é diferente de zero
                                                if (registradores[operador2] != 0 ) {
                                                    registradores[operador1] = registradores[operador1] % registradores[operador2];
                                                } else {
                                                    //caso contrario atribui 0 ao registrador correspondente ao operador1
                                                    registradores[operador1] = 0;
                                                }
                                            } else {
                                                //verifica se valor do operador2 é diferente de zero
                                                if (atoi (operador2.c_str()) != 0) {
                                                    registradores[operador1] = registradores[operador1] % atoi (operador2.c_str() );
                                                } else {
                                                    //caso contrario atribui 0 ao registrador correspondente ao operador1
                                                    registradores[operador1] = 0;
                                                }
                                            }
                                        } else {
                                            int valor1, valor2, linha; 

                                            //para os demais comandos,armazena os valores dos operadores 1 e 2 em valor1 e valor2
                                            //verifica se operador1 é registrador ou valor 
                                            if (operador1[0] == 'R'){
                                                valor1 = registradores[operador1];
                                            } else {
                                                valor1 = atoi (operador1.c_str() );
                                            }
                                            //verifica se operador2 é registrador ou valor 
                                            if (operador2[0] == 'R'){
                                                valor2 = registradores[operador2];
                                            } else {
                                                valor2 = atoi (operador2.c_str() );
                                            }

                                            //compara o comando com "IFEQ"
                                            if (comandos[i].compare("IFEQ") == 0) {
                                                
                                                //se valores forem diferentes pula pra linha seguinte ao ENDIF
                                                if (valor1 != valor2){
                                                    i = procuraENDIF(comandos, i);
                                                } else {
                                                    linha = i;
                                                    while( comandos[linha].compare("ENDIF") != 0) {
                                                        //procura CALL dentro do IFEQ que passa como parametro o mesmo valor usado na comparação do IFEQ
                                                        if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                            //detectou loop infinito 
                                                            *loop = 1;
                                                            return 0;
                                                        }
                                                        linha++;
                                                     }
                                                }                       
                                            } else {
                                                //compara o comando com "IFNEQ"
                                                if (comandos[i].compare("IFNEQ") == 0) {
                                                    //se valores forem iguais pula pra linha seguinte ao ENDIF
                                                    if (valor1 == valor2){
                                                        i = procuraENDIF(comandos, i);
                                                    } else {
                                                        linha = i;
                                                        while( comandos[linha].compare("ENDIF") != 0) {
                                                            //procura CALL dentro do IFNEQ que passa como parametro o mesmo valor usado na comparação do IFNEQ
                                                            if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                //detectou loop infinito 
                                                                *loop = 1;
                                                                return 0;
                                                            }
                                                            linha++;

                                                        }
                                                    }    
                                                } else {
                                                    //compara o comando com "IFG"
                                                    if (comandos[i].compare("IFG") == 0) {
                                                        //se o valor1 for menor ou igual ao valor2, pula pra linha seguinte ao ENDIF
                                                        if (valor1 <= valor2){
                                                            i = procuraENDIF(comandos, i);
                                                        } else {
                                                            linha = i;
                                                            while( comandos[linha].compare("ENDIF") != 0) {
                                                                //procura CALL dentro do IFG que passa como parametro o mesmo valor usado na comparação do IFG
                                                                if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                    //detectou loop infinito 
                                                                    *loop = 1;
                                                                    return 0;
                                                                }
                                                                linha++;

                                                            }
                                                        }    
                                                    } else {
                                                        //compara o comando com "IFL"
                                                        if (comandos[i].compare("IFL") == 0) {
                                                            //se o valor1 for maior ou igual ao valor2, pula pra linha seguinte ao ENDIF
                                                            if (valor1 >= valor2){
                                                                i = procuraENDIF(comandos, i);
                                                            } else {
                                                                linha = i;
                                                                while( comandos[linha].compare("ENDIF") != 0) {
                                                                    //procura CALL dentro do IFL que passa como parametro o mesmo valor usado na comparação do IFL
                                                                    if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                        //detectou loop infinito 
                                                                        *loop = 1;
                                                                        return 0;
                                                                    }
                                                                    linha++;

                                                                }
                                                            }    
                                                        } else {
                                                            //compara o comando com "IFGE"
                                                            if (comandos[i].compare("IFGE") == 0) {
                                                                //se o valor1 for menor ao valor2, pula pra linha seguinte ao ENDIF
                                                                if (valor1 < valor2){
                                                                    i = procuraENDIF(comandos, i);
                                                                } else {
                                                                    linha = i;
                                                                    while( comandos[linha].compare("ENDIF") != 0) {
                                                                        //procura CALL dentro do IFGE que passa como parametro o mesmo valor usado na comparação do IFGE
                                                                        if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                            //detectou loop infinito 
                                                                            *loop = 1;
                                                                            return 0;
                                                                        }
                                                                        linha++;

                                                                    }
                                                                }    
                                                            } else {
                                                                //compara o comando com "IFLE"
                                                                if (comandos[i].compare("IFLE") == 0) {
                                                                    //se o valor1 for maior ou igual ao valor2, pula pra linha seguinte ao ENDIF
                                                                    if (valor1 > valor2){
                                                                        i = procuraENDIF(comandos, i);
                                                                    } else {
                                                                        linha = i;
                                                                        while( comandos[linha].compare("ENDIF") != 0) {
                                                                            //procura CALL dentro do IFLE que passa como parametro o mesmo valor usado na comparação do IFLE
                                                                            if ((comandos[linha].compare("CALL") == 0) && (operador1.compare(operadores1[linha]) == 0) ){
                                                                                //detectou loop infinito 
                                                                                *loop = 1;
                                                                                return 0;
                                                                            }
                                                                            linha++;

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
    }
}



int main() {

    int iterador= 1;
    int numero_linhas;
    int parametro_entrada;
    char comando[5], operador[8];
    string operador1, operador2;
    
    while(1){
        //ler numero de linhas e parametro de entrada do caso de teste
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
                comandos.push_back(comando);

                //caso nao seja o comando ENDIF, sera lido os operadores
                if (strcmp(comando, "ENDIF") != 0) {
                    scanf(" %s", &operador);
                    
                    int tamanho_operador = strlen(operador);

                    //caso o terceiro caracter nao for "," significa q comando só tem um operador
                    if(operador[2] != ',') {
                        operador1 = "";
                        int i = 0; 
                        while( i < tamanho_operador){
                            operador1 += operador[i];
                            i++;
                        }
                        operadores1.push_back(operador1);
                        operadores2.push_back("*");
                    } else {
                        //caso contrario le dois operadores
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
                        operadores1.push_back(operador1);
                        operadores2.push_back(operador2);
                    }
                } else {
                    operadores1.push_back("*");
                    operadores2.push_back("*");
                }
            }

            //funcao para verificar se existe um CALL antes do primeiro RET
            if (procura_CALL_antes_RET(comandos) == 1) {
                cout << "*" << endl;
            } else {
                //inicializa a flag utilizada para marcar se o algoritmo estra em loop infinito ((loop = 1 = loop infinito), (loop = 0 = algoritmo para))
                int loop = 0;
                int cache[1000];

                //loop para inicializar a tabela cache com zeros
                for(int j= 0; j <= 999; j++) {
                    cache[j] = 0;
                }
                //realiza a chamada principal ao programa, passando a entrada informada na primeira linha como parametro
                int result = programa(comandos, operadores1, operadores2, parametro_entrada, &loop, cache);
                if ( loop == 1){
                    cout << "*" << endl;
                } else {
                    cout << result << endl;
                
                }
            }
        }
        iterador++;
    }
    return 0;
}
