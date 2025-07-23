#include "arvore_b.h"
#include <iostream>
#include <algorithm>

using namespace std;

// --- Construtor do Nó ---
ArvoreB::No::No(int ordem, bool ehFolha) {
    this->total = 0;
    this->folha = ehFolha;
    this->pai = nullptr;
    // Maximo de chaves e 2*t - 1, e de filhos e 2*t
    this->chaves.resize(2 * ordem - 1);
    this->filhos.resize(2 * ordem);
}

// --- Encontra o indice da chave ou onde ela deveria estar ---
int ArvoreB::No::encontrarIndice(int k) {
    int idx = 0;
    // O lower_bound seria mais eficiente, mas o loop e mais claro aqui.
    while (idx < total && chaves[idx] < k) {
        idx++;
    }
    return idx;
}

// --- Construtor e Destrutor da Arvore ---
ArvoreB::ArvoreB(int ordem) {
    this->t = ordem;
    raiz = new No(t, true);
}

ArvoreB::~ArvoreB() {
    destruirRecursivo(raiz);
}

void ArvoreB::destruirRecursivo(No* no) {
    if (no == nullptr) return;
    if (!no->folha) {
        for (int i = 0; i <= no->total; i++) {
            destruirRecursivo(no->filhos[i]);
        }
    }
    delete no;
}

// --- INSERCAO (LOGICA CORRIGIDA) ---
void ArvoreB::inserir(int k) {
    cout << "Adicionando " << k << endl;
    No* r = raiz;
    // Se a raiz estiver cheia, a arvore cresce em altura
    if (r->total == 2 * t - 1) {
        No* s = new No(t, false);
        raiz = s;
        s->filhos[0] = r;
        r->pai = s;
        dividirFilho(s, 0);
        inserirNaoCheio(s, k);
    } else {
        inserirNaoCheio(r, k);
    }
}

// Insere a chave em um no que nao esta cheio
void ArvoreB::inserirNaoCheio(No* no, int k) {
    int i = no->total - 1;
    if (no->folha) {
        // Encontra a posicao e move as chaves maiores para a direita
        while (i >= 0 && no->chaves[i] > k) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = k;
        no->total++;
    } else {
        // Encontra o filho que recebera a chave
        while (i >= 0 && no->chaves[i] > k) {
            i--;
        }
        i++;
        // Se o filho estiver cheio, divide-o
        if (no->filhos[i]->total == 2 * t - 1) {
            dividirFilho(no, i);
            if (k > no->chaves[i]) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i], k);
    }
}

// Divide o filho 'y' (em no->filhos[i]) do no 'no'
void ArvoreB::dividirFilho(No* pai, int i) {
    No* y = pai->filhos[i]; // O no a ser dividido (cheio)
    No* z = new No(t, y->folha); // O novo no (irmao direito de y)
    z->pai = pai;
    z->total = t - 1;

    // Copia as ultimas (t-1) chaves de y para z
    for (int j = 0; j < t - 1; j++) {
        z->chaves[j] = y->chaves[j + t];
    }

    // Copia os ultimos t filhos de y para z
    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            z->filhos[j] = y->filhos[j + t];
            if(z->filhos[j] != nullptr) z->filhos[j]->pai = z;
        }
    }

    // Reduz o numero de chaves em y
    y->total = t - 1;

    // Abre espaco no pai para o novo filho
    for (int j = pai->total; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = z;

    // Abre espaco no pai para a chave promovida
    for (int j = pai->total - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    
    // Promove a chave do meio de y para o pai
    pai->chaves[i] = y->chaves[t - 1];
    pai->total++;
}

// --- BUSCA ---
bool ArvoreB::buscar(int k) {
    return buscarNo(raiz, k) != nullptr;
}

ArvoreB::No* ArvoreB::buscarNo(No* no, int k) {
    int i = no->encontrarIndice(k);
    if (i < no->total && no->chaves[i] == k) {
        return no;
    }
    if (no->folha) {
        return nullptr;
    }
    return buscarNo(no->filhos[i], k);
}

// --- REMOCAO (sem alteracoes significativas, mas funciona com a insercao correta) ---
void ArvoreB::remover(int k) {
    if (!raiz) {
        cout << "A arvore esta vazia" << endl;
        return;
    }
    removerRecursivo(raiz, k);

    if (raiz->total == 0 && !raiz->folha) {
        No* temp = raiz;
        raiz = raiz->filhos[0];
        if(raiz) raiz->pai = nullptr;
        delete temp;
    }
}

void ArvoreB::removerRecursivo(No* no, int k) {
    int idx = no->encontrarIndice(k);

    if (idx < no->total && no->chaves[idx] == k) {
        if (no->folha) {
            removerDeFolha(no, idx);
        } else {
            removerDeNaoFolha(no, idx);
        }
    } else {
        if (no->folha) {
            cout << "Chave " << k << " nao encontrada na arvore." << endl;
            return;
        }
        bool flag = (idx == no->total);
        if (no->filhos[idx]->total < t) {
            preencher(no, idx);
        }
        if (flag && idx > no->total) {
            removerRecursivo(no->filhos[idx - 1], k);
        } else {
            removerRecursivo(no->filhos[idx], k);
        }
    }
}

void ArvoreB::removerDeFolha(No* no, int idx) {
    int chave_removida = no->chaves[idx]; 
    cout << "Removendo " << chave_removida << " (de no folha)" << endl;
    for (int i = idx + 1; i < no->total; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }
    no->total--;
}

void ArvoreB::removerDeNaoFolha(No* no, int idx) {
    cout << "Removendo " << no->chaves[idx] << " (de no interno)" << endl;
    int k = no->chaves[idx];
    if (no->filhos[idx]->total >= t) {
        int pred = getAntecessor(no, idx);
        no->chaves[idx] = pred;
        removerRecursivo(no->filhos[idx], pred);
    } else if (no->filhos[idx + 1]->total >= t) {
        int succ = getSucessor(no, idx);
        no->chaves[idx] = succ;
        removerRecursivo(no->filhos[idx + 1], succ);
    } else {
        fundir(no, idx);
        removerRecursivo(no->filhos[idx], k);
    }
}

int ArvoreB::getAntecessor(No* no, int idx) {
    No* cur = no->filhos[idx];
    while (!cur->folha) {
        cur = cur->filhos[cur->total];
    }
    return cur->chaves[cur->total - 1];
}

int ArvoreB::getSucessor(No* no, int idx) {
    No* cur = no->filhos[idx + 1];
    while (!cur->folha) {
        cur = cur->filhos[0];
    }
    return cur->chaves[0];
}

void ArvoreB::preencher(No* no, int idx) {
    if (idx != 0 && no->filhos[idx - 1]->total >= t) {
        emprestarDoAnterior(no, idx);
    } else if (idx != no->total && no->filhos[idx + 1]->total >= t) {
        emprestarDoProximo(no, idx);
    } else {
        if (idx != no->total) {
            fundir(no, idx);
        } else {
            fundir(no, idx - 1);
        }
    }
}

void ArvoreB::emprestarDoAnterior(No* no, int idx) {
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx - 1];

    for (int i = filho->total - 1; i >= 0; --i) {
        filho->chaves[i + 1] = filho->chaves[i];
    }
    if (!filho->folha) {
        for (int i = filho->total; i >= 0; --i) {
            filho->filhos[i + 1] = filho->filhos[i];
        }
    }
    filho->chaves[0] = no->chaves[idx - 1];

    if (!filho->folha) {
        filho->filhos[0] = irmao->filhos[irmao->total];
        if(filho->filhos[0]) filho->filhos[0]->pai = filho;
    }
    no->chaves[idx - 1] = irmao->chaves[irmao->total - 1];

    filho->total++;
    irmao->total--;
}

void ArvoreB::emprestarDoProximo(No* no, int idx) {
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx + 1];

    filho->chaves[filho->total] = no->chaves[idx];

    if (!filho->folha) {
        filho->filhos[filho->total + 1] = irmao->filhos[0];
        if(filho->filhos[filho->total + 1]) filho->filhos[filho->total + 1]->pai = filho;
    }
    no->chaves[idx] = irmao->chaves[0];
    for (int i = 1; i < irmao->total; ++i) {
        irmao->chaves[i - 1] = irmao->chaves[i];
    }
    if (!irmao->folha) {
        for (int i = 1; i <= irmao->total; ++i) {
            irmao->filhos[i - 1] = irmao->filhos[i];
        }
    }
    filho->total++;
    irmao->total--;
}

void ArvoreB::fundir(No* no, int idx) {
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx + 1];

    filho->chaves[t - 1] = no->chaves[idx];

    for (int i = 0; i < irmao->total; ++i) {
        filho->chaves[i + t] = irmao->chaves[i];
    }
    if (!filho->folha) {
        for (int i = 0; i <= irmao->total; ++i) {
            filho->filhos[i + t] = irmao->filhos[i];
             if(filho->filhos[i + t]) filho->filhos[i + t]->pai = filho;
        }
    }

    for (int i = idx + 1; i < no->total; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }
    for (int i = idx + 2; i <= no->total; ++i) {
        no->filhos[i - 1] = no->filhos[i];
    }

    filho->total += irmao->total + 1;
    no->total--;

    delete irmao;
}

// --- IMPRESSAO ---
void ArvoreB::imprimirEstrutura() {
    imprimirRecursivo(raiz, 0);
}

void ArvoreB::imprimirRecursivo(No* no, int nivel) {
    if (no == nullptr) return;
    cout << "Nivel " << nivel << ": ";
    for (int i = 0; i < no->total; i++) {
        cout << no->chaves[i] << " ";
    }
    cout << endl;
    if (!no->folha) {
        for (int i = 0; i <= no->total; i++) {
            imprimirRecursivo(no->filhos[i], nivel + 1);
        }
    }
}

void ArvoreB::listarEmOrdem(function<void(int)> visita) {
    percorrerRecursivo(raiz, visita);
}

void ArvoreB::percorrerRecursivo(No* no, function<void(int)> visita) {
    if (no != nullptr) {
        int i;
        for (i = 0; i < no->total; i++) {
            if (!no->folha) {
                percorrerRecursivo(no->filhos[i], visita);
            }
            visita(no->chaves[i]);
        }
        if (!no->folha) {
            percorrerRecursivo(no->filhos[i], visita);
        }
    }
}