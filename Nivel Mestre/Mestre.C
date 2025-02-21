#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs()

#define BOARD_SIZE 10    // Tamanho do tabuleiro (10x10)
#define SHIP_SIZE 3      // Tamanho fixo dos navios (3 posições)
#define ABILITY_SIZE 5   // Tamanho das matrizes de habilidade (5x5)

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    int i, j;
    
    /*====================================================
      1. Inicialização do Tabuleiro e Posicionamento dos Navios
    =====================================================*/
    // Inicializa todas as posições do tabuleiro com 0 (água)
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    
    // --- Navio 1: Horizontal ---
    int horizRow = 2;    // Linha fixa para o navio horizontal
    int horizCol = 3;    // Coluna inicial
    if (horizCol + SHIP_SIZE - 1 >= BOARD_SIZE) {
        printf("Erro: Navio horizontal extrapola os limites do tabuleiro.\n");
        return 1;
    }
    for (i = 0; i < SHIP_SIZE; i++) {
        if (board[horizRow][horizCol + i] == 3) {
            printf("Erro: Sobreposição no navio horizontal na posição (%d, %d).\n", horizRow, horizCol + i);
            return 1;
        }
        board[horizRow][horizCol + i] = 3;
    }
    
    // --- Navio 2: Vertical ---
    int vertRow = 5;     // Linha inicial para o navio vertical
    int vertCol = 7;     // Coluna fixa
    if (vertRow + SHIP_SIZE - 1 >= BOARD_SIZE) {
        printf("Erro: Navio vertical extrapola os limites do tabuleiro.\n");
        return 1;
    }
    for (i = 0; i < SHIP_SIZE; i++) {
        if (board[vertRow + i][vertCol] == 3) {
            printf("Erro: Sobreposição no navio vertical na posição (%d, %d).\n", vertRow + i, vertCol);
            return 1;
        }
        board[vertRow + i][vertCol] = 3;
    }
    
    // --- Navio 3: Diagonal Crescente (linha e coluna aumentam) ---
    int diag1Row = 0, diag1Col = 0;
    if (diag1Row + SHIP_SIZE - 1 >= BOARD_SIZE || diag1Col + SHIP_SIZE - 1 >= BOARD_SIZE) {
        printf("Erro: Navio diagonal crescente extrapola os limites do tabuleiro.\n");
        return 1;
    }
    for (i = 0; i < SHIP_SIZE; i++) {
        if (board[diag1Row + i][diag1Col + i] == 3) {
            printf("Erro: Sobreposição no navio diagonal crescente na posição (%d, %d).\n", diag1Row + i, diag1Col + i);
            return 1;
        }
        board[diag1Row + i][diag1Col + i] = 3;
    }
    
    // --- Navio 4: Diagonal Decrescente (linha aumenta e coluna diminui) ---
    int diag2Row = 0, diag2Col = 9;
    if (diag2Row + SHIP_SIZE - 1 >= BOARD_SIZE || diag2Col - (SHIP_SIZE - 1) < 0) {
        printf("Erro: Navio diagonal decrescente extrapola os limites do tabuleiro.\n");
        return 1;
    }
    for (i = 0; i < SHIP_SIZE; i++) {
        if (board[diag2Row + i][diag2Col - i] == 3) {
            printf("Erro: Sobreposição no navio diagonal decrescente na posição (%d, %d).\n", diag2Row + i, diag2Col - i);
            return 1;
        }
        board[diag2Row + i][diag2Col - i] = 3;
    }
    
    /*====================================================
      2. Construção das Matrizes de Habilidade
         Cada matriz é ABILITY_SIZE x ABILITY_SIZE (neste exemplo, 5x5)
         Os valores 1 indicam as áreas afetadas; 0, as não afetadas.
    =====================================================*/
    int cone[ABILITY_SIZE][ABILITY_SIZE];
    int cruz[ABILITY_SIZE][ABILITY_SIZE];
    int octaedro[ABILITY_SIZE][ABILITY_SIZE];
    
    // Inicializa todas as matrizes com 0
    for (i = 0; i < ABILITY_SIZE; i++) {
        for (j = 0; j < ABILITY_SIZE; j++) {
            cone[i][j] = 0;
            cruz[i][j] = 0;
            octaedro[i][j] = 0;
        }
    }
    
    int center = ABILITY_SIZE / 2; // Centro da matriz (para 5x5, center = 2)
    
    // --- Matriz Cone ---
    // Forma de cone apontando para baixo: o topo (linha 0) tem apenas a célula central,
    // a linha 1 tem três células (central ±1) e a linha 2 tem todas as 5 células.
    // As linhas 3 e 4 permanecem 0.
    for (i = 0; i < ABILITY_SIZE; i++) {
        for (j = 0; j < ABILITY_SIZE; j++) {
            if (i < 3) { // Utiliza apenas as três primeiras linhas para o cone
                if (j >= center - i && j <= center + i) {
                    cone[i][j] = 1;
                }
            }
        }
    }
    
    // --- Matriz Cruz ---
    // Marca as células da linha central e da coluna central.
    for (i = 0; i < ABILITY_SIZE; i++) {
        for (j = 0; j < ABILITY_SIZE; j++) {
            if (i == center || j == center) {
                cruz[i][j] = 1;
            }
        }
    }
    
    // --- Matriz Octaedro (vista frontal de um octaedro / losango) ---
    // Utiliza a soma das distâncias (em módulo) do centro para definir o losango.
    for (i = 0; i < ABILITY_SIZE; i++) {
        for (j = 0; j < ABILITY_SIZE; j++) {
            if ((abs(i - center) + abs(j - center)) <= center) {
                octaedro[i][j] = 1;
            }
        }
    }
    
    /*====================================================
      3. Sobreposição das Habilidades no Tabuleiro
         Cada habilidade possui um ponto de origem no tabuleiro,
         que será o centro da área de efeito.
         Se a célula do tabuleiro estiver em área de efeito (valor 1 na matriz da habilidade)
         e não contiver um navio (valor 3), ela é marcada com 5.
    =====================================================*/
    
    // Define os pontos de origem (centro da matriz de habilidade) no tabuleiro
    // Para que a matriz seja corretamente centrada, a posição do canto superior esquerdo
    // da área a sobrepor será: (origem - center)
    int coneOriginRow = 4, coneOriginCol = 4;    // Exemplo para o Cone
    int cruzOriginRow  = 7, cruzOriginCol  = 2;    // Exemplo para a Cruz
    int octOriginRow   = 3, octOriginCol   = 7;    // Exemplo para o Octaedro
    
    // Função de sobreposição (para cada habilidade, usa o mesmo procedimento)
    // Overlay da matriz Cone
    for (i = 0; i < ABILITY_SIZE; i++) {
        for (j = 0; j < ABILITY_SIZE; j++) {
            int boardRow = coneOriginRow - center + i;
            int boardCol = coneOriginCol - center + j;
            if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                if (cone[i][j] == 1 && board[boardRow][boardCol] != 3) {
                    board[boardRow][boardCol] = 5;
                }
            }
        }
    }
    
    // Overlay da matriz Cruz
    for (i = 0; i < ABILITY_SIZE; i++) {
        for (j = 0; j < ABILITY_SIZE; j++) {
            int boardRow = cruzOriginRow - center + i;
            int boardCol = cruzOriginCol - center + j;
            if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                if (cruz[i][j] == 1 && board[boardRow][boardCol] != 3) {
                    board[boardRow][boardCol] = 5;
                }
            }
        }
    }
    
    // Overlay da matriz Octaedro
    for (i = 0; i < ABILITY_SIZE; i++) {
        for (j = 0; j < ABILITY_SIZE; j++) {
            int boardRow = octOriginRow - center + i;
            int boardCol = octOriginCol - center + j;
            if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                if (octaedro[i][j] == 1 && board[boardRow][boardCol] != 3) {
                    board[boardRow][boardCol] = 5;
                }
            }
        }
    }
    
    /*====================================================
      4. Exibição do Tabuleiro
         - Água: 0
         - Navio: 3
         - Área de efeito (habilidade): 5
    =====================================================*/
    printf("Tabuleiro com Navios e Áreas de Efeito:\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}