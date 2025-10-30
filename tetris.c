#include <stdio.h>

// Desafio Tetris Stack - Nível Novato
// Sistema de controle de peças.

#define MAX_PECAS 5  // Número máximo de peças

// ======================== ESTRUTURA ========================

// Define cada peça do jogo
typedef struct {
    char nome[];
    int id;
} Peca;

// Define a lista circular de peças do jogo
typedef struct {
    Peca pecas[MAX_PECAS];
    int inicio;
    int fim;
    int total;
} Fila;

// ======================== FUNÇÕES ========================

// Inicializar fila de peças
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Exibir a fila de peças
void mostrarFila(Fila *f) {
    if (total == 0) {
        printf("\nNão há peças na fila!\n");
        return;
    }

    printf("\n--- PEÇAS NA FILA ---\n");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n");
    printf("---------------------------------------------------------------------------\n");

}

// Verifica se a fila está cheia
void filaCheia(Fila *f) {
    return f->total == MAX_PECAS;
}

// Verifica se a fila está vazia
void filaVazia(Fila *f) {
    return f->total == 0;
}

// Gerar nova peça
void gerarPeca(Fila *f, Peca e) {
    
}

// Remove a peça da frente da fila (dequeue)
void removerPeca(Fila *f) {

    Elemento vazio = {-1};                      // Valor padrão caso a fila esteja vazia
    if (filaVazia(f))                           // Evita remoção se estiver vazia
        printf("Fila vazia. Não é possível remover.\n");
        return vazio;
    Peca e = f->pecas[f->inicio];               // Armazena a peça a ser removida
    f->inicio = (f->inicio + 1) % MAX_PECAS;    // Atualiza circularmente o índice
    f->total--;                                 // Decrementa a contagem de elementos
    return e;                                   // Retorna a peça removida
}

// Inserir nova peça ao final da fila (enqueue)
void inserirPeca(Fila *f, Peca e) {

    if (filaCheia(f))                   // Evita inserção se estiver cheia
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    f->pecas[f->fim] = e;               // Insere no final
    f->fim = (f->fim + 1) % MAX_PECAS;  // Atualiza circularmente o índice
    f->total++;                         // Incrementa a contagem de elementos
}
// ======================== MAIN ========================
int main() {
    Fila f;
    inicializarFila(&f);  // Inicializa a fila
 
    // Insere as peças padrão na fila
    Fila f = {
        .pecas = {
            {"T", 1},
            {"O", 2},
            {"L", 3},
            {"I", 4},
            {"I", 5}
        },
        .total = 5
    };
    mostrarFila(&f);  // Mostra a fila após inserção inicial

    int opcao;

    printf("\n===========================================\n");
    printf("         TETRIS STACK (NÍVEL NOVATO)         \n");
    printf("\n===========================================\n");

    do {
        printf("\nPeças na lista: %d/20", totalPecas);
        printf("\n========= MENU DE AÇÕES =========\n");
        printf("1. Jogar Peça\n2. Inserir Nova Peça\n3. Visualizar Fila\n0. Sair\n");
        printf("=================================\nEscolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1: removerPeca(); mostrarFila(); break;
            case 2: inserirPeca(); mostrarFila(); break;
            case 3: mostrarFila(); break;
            case 0: printf("\nSaindo do jogo...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

