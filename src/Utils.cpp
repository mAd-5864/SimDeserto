//
// Created by Pedro on 11/3/2024.
//

#include "../include/Utils.h"

using namespace std;
//Nao sei se era para fazer aqui, mas vou ja fazer aqui
int comandos(){
    string cmd_e_args, cmd;
    int x = 0;

    cout<<"insira comando:\n";
    getline(cin, cmd_e_args);

    //loop para remover espaços no inicio do comando (caso existao)
    for (int i = 0; i < cmd_e_args.length(); ++i) {
        if(cmd_e_args[i] != ' '){
            break;
        }
        x++;
    }
    cmd_e_args = cmd_e_args.substr(x); //Nao podemos fazer isto diretamente dentro do loop porque a string esta a mudar constantemente de tamanho e está a ser comparado o seu tamanho no loop...

    //loop para aceder ao comando
    for (int i = 0; i < cmd_e_args.length(); ++i) {
        if(cmd_e_args[i] == ' '){
            break;
        }
        cmd += cmd_e_args[i];
    }

    if(cmd == "exec"){
        //chamada da função
    }
    else if(cmd == "prox"){
        //chamada da função
    }
    else if(cmd == "comprac"){
        //chamada da função
    }
    else if(cmd == "precos"){
        //chamada da função
    }
    else if(cmd == "cidade"){
        //chamada da função
    }
    else if(cmd == "caravana"){
        //chamada da função
    }
    else if(cmd == "compra"){
        //chamada da função
    }
    else if(cmd == "vende"){
        //chamada da função
    }
    else if(cmd == "move"){
        //chamada da função
    }
    else if(cmd == "auto"){
        //chamada da função
    }
    else if(cmd == "stop"){
        //chamada da função
    }
    else if(cmd == "barbaro"){
        //chamada da função
    }
    else if(cmd == "areia"){
        //chamada da função
    }
    else if(cmd == "moedas"){
        //chamada da função
    }
    else if(cmd == "tripul"){
        //chamada da função
    }
    else if(cmd == "saves"){
        //chamada da função
    }
    else if(cmd == "loads"){
        //chamada da função
    }
    else if(cmd == "lists"){
        //chamada da função
    }
    else if(cmd == "dels"){
        //chamada da função
    }
    else if(cmd == "terminar"){
        //chamada da função
    }
    else{
        cout<<"[ERRO] Comando nao implementado";
    }
}