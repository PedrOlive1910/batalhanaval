#include <stdio.h>

#define TABULEIRO_SIZE 10
#define HABILIDADE_SIZE 5

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE]) {
    for (int i = 0; i < TABULEIRO_SIZE; i++) {
        for (int j = 0; j < TABULEIRO_SIZE; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("0 "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf("3 "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf("5 "); // Área afetada pela habilidade
            }
        }
        printf("\n");
    }
}

// Função para gerar a matriz de habilidade cone
void gerarHabilidadeCone(int matriz[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            matriz[i][j] = (i >= j) ? 1 : 0; // Preenche a matriz em forma de cone
        }
    }
}

// Função para gerar a matriz de habilidade cruz
void gerarHabilidadeCruz(int matriz[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            matriz[i][j] = (i == HABILIDADE_SIZE / 2 || j == HABILIDADE_SIZE / 2) ? 1 : 0; // Preenche a matriz em forma de cruz
        }
    }
}

// Função para gerar a matriz de habilidade octaedro
void gerarHabilidadeOctaedro(int matriz[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            matriz[i][j] = (abs(HABILIDADE_SIZE / 2 - i) + abs(HABILIDADE_SIZE / 2 - j) <= HABILIDADE_SIZE / 2) ? 1 : 0; // Preenche a matriz em forma de octaedro
        }
    }
}

// Função para sobrepor a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE], int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE], int linha, int coluna) {
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            if (habilidade[i][j] == 1) {
                int x = linha + i - HABILIDADE_SIZE / 2;
                int y = coluna + j - HABILIDADE_SIZE / 2;
                if (x >= 0 && x < TABULEIRO_SIZE && y >= 0 && y < TABULEIRO_SIZE) {
                    tabuleiro[x][y] = 5; // Marca a área afetada
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE] = {0}; // Inicializa o tabuleiro com água
    // Exemplos de navios
    tabuleiro[2][2] = 3;
    tabuleiro[3][3] = 3;

    int habilidadeCone[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int habilidadeCruz[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int habilidadeOctaedro[HABILIDADE_SIZE][HABILIDADE_SIZE];

    // Gera as matrizes de habilidade
    gerarHabilidadeCone(habilidadeCone);
    gerarHabilidadeCruz(habilidadeCruz);
    gerarHabilidadeOctaedro(habilidadeOctaedro);

    // Aplica as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 0, 2);
    aplicarHabilidade(tabuleiro, habilidadeCruz, 1, 