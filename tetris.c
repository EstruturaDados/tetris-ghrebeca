// TETRIS STACK - NÍVEL MESTRE
// Gerencia fila de peças futuras e pilha de reserva.
// Funcionalidades: jogar peça, reservar, usar reservada, trocar peça atual,
// troca múltipla e exibição do estado.
// Peças: tipo ('I', 'O', 'T', 'L') + ID único.

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
    Peca pecas[MAX_PECAS]; // Array de peças na fila
    int inicio;            // Índice do início da fila
    int fim;               // Índice do fim da fila
    int total;             // Total de peças atualmente na fila
} Fila;

// Estrutura da pilha de peças reservadas
typedef struct {
    Peca pecasReservadas[MAX_RESERVA]; // Array de peças na pilha
    int topo;                          // Índice do topo da pilha
} Pilha;

// ======================== FUNÇÕES DE FILA ========================

// Inicializa a fila, definindo índices e total como 0
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia (total == capacidade máxima)
int filaCheia(Fila *f) {
    return f->total == MAX_PECAS;
}

// Verifica se a fila está vazia (total == 0)
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Gera uma nova peça aleatória com um ID único
Peca gerarPeca(int idAtual) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // Escolhe aleatoriamente entre os tipos
    nova.id = idAtual;
    return nova;
}

// Insere uma nova peça no final da fila (enqueue)
void inserirPeca(Fila *f, int *idAtual) {
    if (filaCheia(f)) return; // Não insere se estiver cheia

    Peca nova = gerarPeca((*idAtual)++);
    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX_PECAS; // Atualiza índice circular
    f->total++;
}

// Remove a peça da frente da fila (dequeue)
Peca removerPeca(Fila *f) {
    if (filaVazia(f)) {
        Peca vazia = {' ', -1};  // Retorna peça inválida se vazia
        return vazia;
    }

    Peca removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PECAS; // Atualiza índice circular
    f->total--;
    return removida;
}

// ======================== FUNÇÕES DE PILHA ========================

// Inicializa a pilha, definindo topo como -1 (vazia)
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está cheia (topo == capacidade máxima - 1)
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_RESERVA - 1;
}

// Verifica se a pilha está vazia (topo == -1)
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Adiciona uma peça na pilha (push)
void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) return; // Não insere se estiver cheia
    
    p->pecasReservadas[++p->topo] = nova; // Incrementa topo e insere
    printf("Peça [%c %d] movida para a reserva.\n", nova.nome, nova.id);
}

// Remove a peça do topo (pop)
void usarPecaReservada(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Não há peças reservadas no momento!\n");
        return;
    }
    Peca usada = p->pecasReservadas[p->topo--]; // Remove topo
    printf("Peça reservada [%c %d] usada!\n", usada.nome, usada.id);
}

// ======================== OPERAÇÕES DE JOGO ========================

// Jogar uma peça: remove da fila e adiciona nova no final
void jogarPeca(Fila *f, int *idAtual) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca jogada = removerPeca(f);
    printf("Peça [%c %d] jogada!\n", jogada.nome, jogada.id);

    inserirPeca(f, idAtual); // Mantém fila cheia
}

// Reservar uma peça: remove da fila e adiciona na pilha
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
    push(p, reservada); // Adiciona na pilha de reserva
    inserirPeca(f, idAtual); // Mantém fila cheia
}

// Troca a peça da frente da fila com o topo da pilha
void trocarPecaAtual(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peça para trocar.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Nenhuma peça para trocar.\n");
        return;
    }

    int indiceFila = f->inicio; // Frente da fila
    int indicePilha = p->topo;  // Topo da pilha

    Peca temp = f->pecas[indiceFila];
    f->pecas[indiceFila] = p->pecasReservadas[indicePilha];
    p->pecasReservadas[indicePilha] = temp;

    printf("Trocadas as peças da frente da fila e do topo da pilha!\n");
    printf("Nova peça atual: [%c %d]\n", f->pecas[indiceFila].nome, f->pecas[indiceFila].id);
}

// Troca múltipla: as 3 primeiras da fila com as 3 da pilha
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo + 1 < 3) {
        printf("Não há peças suficientes para realizar a troca múltipla.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (f->inicio + i) % MAX_PECAS;
        int idxPilha = p->topo - i;

        Peca temp = f->pecas[idxFila];
        f->pecas[idxFila] = p->pecasReservadas[idxPilha];
        p->pecasReservadas[idxPilha] = temp;
    }

    printf("Troca múltipla realizada com sucesso!\n");
}

// Exibe o estado atual da fila e da pilha
void exibirEstadoAtual(Fila *f, Pilha *p) {
    printf("\n----- ESTADO ATUAL -----\n");

    printf("\nFila de Peças (frente → fim): ");
    if (filaVazia(f)) {
        printf("(vazia)");
    } else {
        int idx = f->inicio;
        for (int i = 0; i < f->total; i++) {
            printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
            idx = (idx + 1) % MAX_PECAS; // Percorre circularmente
        }
    }
    printf("\n");

    printf("Pilha de Reserva (topo → base): ");
    if (pilhaVazia(p)) {
        printf("(vazia)");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pecasReservadas[i].nome, p->pecasReservadas[i].id);
        }
    }
    printf("\n\n-------------------------\n");
}

// ======================== MAIN ========================

int main() {
    Fila f;
    Pilha p;
    int idAtual = 0; // Contador de IDs das peças
    int opcao;

    srand(time(NULL)); // Inicializa gerador de números aleatórios
    inicializarFila(&f);
    inicializarPilha(&p);

    // Preenche a fila inicial com peças
    for (int i = 0; i < MAX_PECAS; i++)
        inserirPeca(&f, &idAtual);

    exibirEstadoAtual(&f, &p);

    // Menu principal
    do {
        printf("\n========= MENU TETRIS STACK =========\n");
        printf("1. Jogar uma peça\n");
        printf("2. Reservar uma peça\n");
        printf("3. Usar uma peça reservada\n");
        printf("4. Exibir o estado atual\n");
        printf("5. Trocar peça atual\n");
        printf("6. Troca múltipla\n");
        printf("0. Sair\n");
        printf("====================================\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&f, &idAtual);
                exibirEstadoAtual(&f, &p);
                break;
            case 2:
                reservarPeca(&f, &p, &idAtual);
                exibirEstadoAtual(&f, &p);
                break;
            case 3:
                usarPecaReservada(&p);
                exibirEstadoAtual(&f, &p);
                break;
            case 4:
                exibirEstadoAtual(&f, &p);
                break;
            case 5:
                trocarPecaAtual(&f, &p);
                exibirEstadoAtual(&f, &p);
                break;
            case 6:
                trocaMultipla(&f, &p);
                exibirEstadoAtual(&f, &p);
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
