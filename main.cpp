#include <iostream>
#include <limits>
#include "arvore_b.h"

using namespace std;

// FUNCOES SECUNDARIAS
void limpa_tela(){ 
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void limpa_buffer() { 
    cin.clear();               
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void entrada(int ini, int fim, int *opcao){  
    int a;
    cout << "Digite uma opção: ";
    cin >> a;
    while (a < ini || a > fim){
        cout << "Digite nomamente, intervalo aceito [" << ini << ',' << fim << ']' << endl;
        cout << "Digite uma opção: ";
        cin >> a;
    }
    *opcao = a;
}

void visita(int chave) {
    cout << chave << " ";
}

void caso_dinamico() {
    limpa_tela();
    bool continuar = true;
    int opcao, chave;
    
    ArvoreB arvore(3);

    while(continuar){
        limpa_tela();
        cout << "Caso dinamico iniciado com arvore de ordem 3 (qtd de chave maxima por no: 5).\n";
        cout << "Menu:" << endl
                << "1 - Inserir um novo elemento" << endl
                << "2 - Remover um elemento" << endl
                << "3 - Buscar um elemento" << endl
                << "4 - Listar elementos em ordem" << endl
                << "5 - Imprimir estrutura da arvore" << endl
                << "6 - sair" << endl;
        entrada(1,6,&opcao);
        limpa_tela();
        switch (opcao){
             case 1:
                cout << "Digite a chave para inserir: ";
                cin >> chave;
                arvore.inserir(chave);
                cout << "Arvore apos a inserção de " << chave << ":"  << endl;
                arvore.imprimirEstrutura();
                break;
            case 2:
                cout << "Digite a chave para remover: ";
                cin >> chave;
                arvore.remover(chave);
                cout << "Arvore apos a remocao de " << chave << ":" << endl;
                arvore.imprimirEstrutura();
                break;
            case 3:
                cout << "Digite a chave para buscar: ";
                cin >> chave;
                if (arvore.buscar(chave)) cout << "Resultado: Chave " << chave << " encontrada na arvore." << endl;
                else cout << "Resultado: Chave " << chave << " nao encontrada na arvore." << endl;
            
                break;
            case 4:
                cout << "Listando todos os elementos em ordem:\n";
                arvore.listarEmOrdem(visita);
                cout << endl << endl;
                break;
            case 5:
                cout << "\n--- Estrutura da Arvore ---\n";
                arvore.imprimirEstrutura();
                cout << "\n";
                break;
            case 6:
                continuar = false;
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }

        if (continuar) {
            cout << "Aperte enter para voltar.";
            cin.ignore();
            cin.get();
        }

    }
}

void caso_estatico() {
    limpa_tela();
    cout << "--- INICIANDO CASO ESTATICO COM ORDEM 4 ---" << endl;
    ArvoreB arvore(4);

    cout << "\n--- Fase de Insercoes ---\n";
    int chaves_para_inserir[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 5, 15, 25, 35};
    for (int k : chaves_para_inserir) {
        arvore.inserir(k);
    }

    cout << "\n--- Arvore Inicial Completa (Ordem 4) ---\n";
    arvore.imprimirEstrutura();

    cout << "\n--- Removendo a chave 80 (no interno) ---\n";
    arvore.remover(80);
    cout << "\nArvore apos a primeira remocao:\n";
    arvore.imprimirEstrutura();

    cout << "\n--- Removendo chaves ---\n";
    arvore.remover(130);
    arvore.remover(120);
    arvore.remover(110);
    arvore.remover(100); 
    arvore.remover(60); 
    
    cout << "\nArvore apos as remocoes:\n";
    arvore.imprimirEstrutura();
}

int main() {
    int opcao;
    bool continuar = true, voltar;
    while (continuar){
        limpa_tela();
        cout << "1 - Questão 1 (Caso dinâmico)" << endl
             << "2 - Questão 2 (Caso Estático)" << endl
             << "3 - sair" << endl;
        entrada(1,3,&opcao);
        switch (opcao){
            case 1:
                caso_dinamico();
                voltar = false;
                break;
            case 2:
                caso_estatico();
                voltar = true;
                break;
            case 3:
                continuar = false;
                break;
        }   
        if (continuar && voltar) {
            cout << "Aperte enter para voltar.";
            cin.ignore();
            cin.get();
            
        }
    }
}