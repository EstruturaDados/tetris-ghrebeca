#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PECAS 5     // Número máximo de peças na fila (fila circular)
#define MAX_RESERVA 3   // Capacidade máxima da pilha de reserva

// ======================== ESTRUTURAS ========================

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único da peça
} Peca;

// Estrutura da fila circular de peças futuras
typedef struct {
    Peca pecas[MAX_PECAS];
    int inicio; 
    int fim;
    int total;
} Fila;

// Estrutura da pilha de peças reservadas
typedef struct {
    Peca pecasReservadas[MAX_RESERVA];
    int topo;
} Pilha;

// ======================== FUNÇÕES DE FILA ========================

// Inicializa a fila
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

// Gera uma nova peça aleatória
Peca gerarPeca(int idAtual) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = idAtual;
    return nova;
}

// Insere uma nova peça no final da fila (enqueue)
void inserirPeca(Fila *f, int *idAtual) {
    if (filaCheia(f)) return;

    Peca nova = gerarPeca((*idAtual)++);
    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX_PECAS;
    f->total++;
}

// Remove a peça da frente da fila (dequeue)
Peca removerPeca(Fila *f) {
    Peca removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PECAS;
    f->total--;
    return removida;
}

// Exibe o estado atual da fila
void mostrarFila(Fila *f) {
    printf("\nFila de Peças (frente → fim): ");
    if (filaVazia(f)) {
        printf("(vazia)");
    } else {
        int idx = f->inicio;
        for (int i = 0; i < f->total; i++) {
            printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
            idx = (idx + 1) % MAX_PECAS;
        }
    }
    printf("\n");
}

// ======================== FUNÇÕES DE PILHA ========================

// Inicializa a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Verifica se está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_RESERVA - 1;
}

// Verifica se está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Adiciona uma peça na pilha (push)
void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    p->pecasReservadas[++p->topo] = nova;
    printf("Peça [%c %d] movida para a reserva.\n", nova.nome, nova.id);
}

// Remove a peça do topo (pop)
void usarPecaReservada(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Não há peças reservadas no momento!\n");
        return;
    }
    Peca usada = p->pecasReservadas[p->topo--];
    printf("Peça reservada [%c %d] usada!\n", usada.nome, usada.id);
}

// Mostra o estado atual da pilha
void mostrarPilha(Pilha *p) {
    printf("Pilha de Reserva (topo → base): ");
    if (pilhaVazia(p)) {
        printf("(vazia)");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pecasReservadas[i].nome, p->pecasReservadas[i].id);
        }
    }
    printf("\n");
}

// ======================== OPERAÇÕES DE JOGO ========================

// Jogar uma peça (remove da fila e repõe outra)
void jogarPeca(Fila *f, int *idAtual) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca jogada = removerPeca(f);
    printf("Peça [%c %d] jogada!\n", jogada.nome, jogada.id);

    // Gera nova peça automaticamente para o final da fila
    inserirPeca(f, idAtual);
}

// Reservar uma peça (fila → pilha)
void reservarPeca(Fila *f, Pilha *p, int *idAtual) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não há peça para reservar.\n");
        return;
    }
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }

    Peca reservada = removerPeca(f);
    push(p, reservada);

    // Mantém a fila cheia
    inserirPeca(f, idAtual);
}

// ======================== MAIN ========================

int main() {
    Fila f;
    Pilha p;
    int idAtual = 0;
    int opcao;

    srand(time(NULL));
    inicializarFila(&f);
    inicializarPilha(&p);

    // Preenche a fila inicial
    for (int i = 0; i < MAX_PECAS; i++)
        inserirPeca(&f, &idAtual);

    // Menu principal
    do {
        printf("\n========= MENU TETRIS STACK =========\n");
        printf("1. Jogar peça (remover da frente)\n");
        printf("2. Reservar peça (fila → pilha)\n");
        printf("3. Usar peça reservada (remover do topo)\n");
        printf("0. Sair\n");
        printf("====================================\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&f, &idAtual);
                break;
            case 2:
                reservarPeca(&f, &p, &idAtual);
                break;
            case 3:
                usarPecaReservada(&p);
                break;
            case 0:
                printf("\nEncerrando o jogo. Até mais!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

        // Mostrar estado atual após cada ação
        printf("\n----- ESTADO ATUAL -----\n");
        mostrarFila(&f);
        mostrarPilha(&p);
        printf("-------------------------\n");

    } while (opcao != 0);

    return 0;
}
