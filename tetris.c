#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PECAS 5  // Número máximo de peças na fila

// ======================== ESTRUTURAS ========================

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

// Estrutura da fila circular de peças
typedef struct {
    Peca pecas[MAX_PECAS]; // Array que armazena as peças
    int inicio;            // Índice do primeiro elemento da fila
    int fim;               // Índice do último elemento da fila
    int total;             // Quantidade atual de peças na fila
} Fila;

// ======================== FUNÇÕES ========================

// Inicializa a fila de peças
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX_PECAS;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Gera uma nova peça com tipo aleatório e ID sequencial
Peca gerarPeca(Fila *f) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4; // escolhe aleatoriamente o tipo

    Peca nova;

    // Calcula o ID da nova peça
    if (f->total == 0)
        nova.id = 0;
    else {
        int ultimo = (f->fim - 1 + MAX_PECAS) % MAX_PECAS;
        nova.id = f->pecas[ultimo].id + 1;
    }

    nova.nome = tipos[indice];
    return nova;
}

// Insere uma nova peça no final da fila (enqueue)
void inserirPeca(Fila *f) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir mais peças.\n");
        return;
    }

    Peca nova = gerarPeca(f);
    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX_PECAS;
    f->total++;

    printf("Peça [%c %d] inserida na fila.\n", nova.nome, nova.id);
}

// Remove a peça da frente da fila (dequeue)
void removerPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PECAS;
    f->total--;

    printf("Peça [%c %d] jogada!\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila de peças vazia.\n");
        return;
    }

    printf("\nFila de Peças (total: %d/%d):\n", f->total, MAX_PECAS);
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_PECAS) {
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n");
}

// ======================== MAIN ========================
int main() {
    Fila f;
    inicializarFila(&f);
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < MAX_PECAS; i++) {
        inserirPeca(&f);
    }

    int opcao;

    // Loop principal do menu
    do {
        printf("\n========= MENU TETRIS STACK =========\n");
        printf("1. Jogar peça (remover da frente)\n");
        printf("2. Inserir nova peça (no final)\n");
        printf("3. Mostrar fila de peças\n");
        printf("0. Sair\n");
        printf("====================================\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                removerPeca(&f);
                mostrarFila(&f);
                break;
            case 2:
                inserirPeca(&f);
                mostrarFila(&f);
                break;
            case 3:
                mostrarFila(&f);
                break;
            case 0:
                printf("\nEncerrando o jogo. Até mais!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
