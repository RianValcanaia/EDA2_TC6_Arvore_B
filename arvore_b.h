#pragma once

#include <iostream>
#include <vector>
#include <functional>

class ArvoreB {
public:
    ArvoreB(int ordem);
    ~ArvoreB();

    bool buscar(int k);
    void inserir(int k);
    void remover(int k);

    void imprimirEstrutura();
    void listarEmOrdem(std::function<void(int)> visita);

private:
    struct No {
        int total;
        bool folha;
        std::vector<int> chaves;
        std::vector<No*> filhos;
        No* pai;

        No(int ordem, bool ehFolha);
        int encontrarIndice(int k);
    };

    No* raiz;
    int t; // Ordem da árvore

    void destruirRecursivo(No* no);
    void imprimirRecursivo(No* no, int nivel);
    void percorrerRecursivo(No* no, std::function<void(int)> visita);
    No* buscarNo(No* no, int k);

    void dividirFilho(No* pai, int i);
    void inserirNaoCheio(No* no, int k);

    void removerRecursivo(No* no, int k);
    void removerDeFolha(No* no, int idx);
    void removerDeNaoFolha(No* no, int idx);
    int getAntecessor(No* no, int idx);
    int getSucessor(No* no, int idx);
    void preencher(No* no, int idx);
    void emprestarDoAnterior(No* no, int idx);
    void emprestarDoProximo(No* no, int idx);
    void fundir(No* no, int idx);
};