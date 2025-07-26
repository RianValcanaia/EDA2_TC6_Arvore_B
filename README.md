<div align="center" id="topo">

<img src="https://media.giphy.com/media/iIqmM5tTjmpOB9mpbn/giphy.gif" width="200px" alt="Gif animado"/>

# <code><strong> Implementação de Árvore B</strong></code>

<em>Trabalho da disciplina de Estrutura de Dados sobre a implementação de uma Árvore B.</em>

[![C++ Usage](https://img.shields.io/badge/C%2B%2B-100%25-blue?style=for-the-badge&logo=c%2B%2B)]()
[![Status](https://img.shields.io/badge/Status-Concluído-green?style=for-the-badge)]()
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Visite%20meu%20perfil-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/rian-carlos-valcanaia-b2b487168/)

</div>


## Índice

- [📌 Objetivos](#-objetivos)
- [📥 Entradas do sistema](#-entradas-do-sistema)
- [🧱 Estruturas de Dados](#-estruturas-de-dados)
- [🧰 Funcionalidades](#-funcionalidades)
- [📊 Exemplo de Execução](#-exemplo-de-execução)
- [📂 Como executar](#-como-executar)
- [👨‍🏫 Envolvidos](#-envolvidos)
- [📅 Curso](#-curso)
- [📄 Código-fonte](#-código-fonte)

## 📌 Objetivos
* Criar um programa para gerar e manipular uma Árvore B.
* Implementar as funcionalidades de inserção, remoção, busca e listagem ordenada de chaves.
* Desenvolver um caso de teste estático para demonstrar a criação da árvore e pelo menos duas remoções, exibindo a estrutura da árvore antes e após cada remoção.

[⬆ Voltar ao topo](#topo)

## 📥 Entradas do sistema
* O programa é controlado via um menu interativo no terminal.
* O usuário fornece números inteiros (chaves) para as operações de inserção, remoção e busca no modo dinâmico.

[⬆ Voltar ao topo](#topo)

## 🧱 Estruturas de Dados
### 🔸 `ArvoreB`
A classe principal que encapsula todos os métodos e atributos da Árvore B, incluindo a raiz, a ordem e as operações fundamentais.
```cpp
class ArvoreB {
public:
    ArvoreB(int ordem);
    ~ArvoreB();

    // Métodos
    bool buscar(int k);
    void inserir(int k);
    void remover(int k);
    void imprimirEstrutura();
    void listarEmOrdem(std::function<void(int)> visita);

private:
    struct No { ... };
    No* raiz;
    int t; // Ordem da árvore

    // Métodos
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
```

### 🔸 `No`
A estrutura que representa um nó da árvore.
```cpp
struct No {
    int total;
    bool folha;
    std::vector<int> chaves;
    std::vector<No*> filhos;
    No* pai;
};
```

[⬆ Voltar ao topo](#topo)

## 🧰 Funcionalidades

### 🔹 Funções Principais
* `inserir()`: Insere uma nova chave na árvore, realizando splits quando necessário.
* `remover()`: Remove uma chave da árvore, realizando fusões ou empréstimos para manter as propriedades da árvore.
* `buscar()`: Verifica se uma chave existe na árvore.
* `listarEmOrdem()`: Imprime todas as chaves da árvore de forma ordenada.
* `imprimirEstrutura()`: Exibe a estrutura completa da árvore, nível por nível.
* `caso_dinamico()`: Inicia o modo interativo, onde o usuário pode testar as funcionalidades livremente.
* `caso_estatico()`: Executa uma demonstração pré-programada de inserções e remoções.

### 🔸 Funções Secundárias
* `limpa_tela()`, `limpa_buffer()`, `entrada()`: Funções de utilidade para a interface do console.
* `dividirFilho()`, `inserirNaoCheio()`: Funções auxiliares para a operação de inserção.
* `removerDeFolha()`, `removerDeNaoFolha()`, `fundir()`, `preencher()`, `emprestarDoAnterior()`, `emprestarDoProximo()`: Funções auxiliares para a operação de remoção.

[⬆ Voltar ao topo](#topo)

## 📊 Exemplo de Execução
1.  O usuário executa o programa e visualiza um menu com duas opções principais: "Caso dinâmico" e "Caso Estático".
2.  Selecionando a **Opção 1 (Caso dinâmico)**, o usuário entra em um sub-menu onde pode inserir, remover, buscar e listar chaves em uma árvore de ordem 3. O estado da árvore é exibido após cada modificação.
3.  Selecionando a **Opção 2 (Caso Estático)**, o programa executa um script: cria uma árvore de ordem 4, insere 18 chaves, exibe a árvore, realiza uma série de remoções e exibe o estado final da árvore.

[⬆ Voltar ao topo](#topo)

## 📂 Como executar
Para compilar e executar o projeto, utilize os seguintes comandos no terminal:
```bash
g++ main.cpp arvore_b.cpp -o trabalho && ./trabalho
```

[⬆ Voltar ao topo](#topo)

## 👨‍🏫 Envolvidos
* **Professor**: André Tavares da Silva
* **Estudantes**:
  * [Rian Valcanaia](https://github.com/RianValcanaia)

[⬆ Voltar ao topo](#topo)

## 📅 Curso

* **Universidade**: Universidade do Estado de Santa Catarina (UDESC)
* **Disciplina**: Estrutura de Dados 2
* **Semestre**: 4º

[⬆ Voltar ao topo](#topo)

## 📄 Código-fonte

🔗 [https://github.com/RianValcanaia/EDA2_TC6_Arvore_B](https://github.com/RianValcanaia/EDA2_TC6_Arvore_B)

[⬆ Voltar ao topo](#topo)
