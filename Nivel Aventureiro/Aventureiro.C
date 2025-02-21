#include <stdio.h>

#define BOARD_SIZE 10   // Tamanho do tabuleiro (10x10)
#define SHIP_SIZE 3     // Tamanho fixo dos navios (3 posições)

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    
    // Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    
    /*-----------------------------------------------------
     * Posicionamento dos Navios
     *-----------------------------------------------------*/
    
    // Navio 1: Horizontal
    int horizRow = 2;    // Linha onde o navio horizontal será posicionado
    int horizCol = 3;    // Coluna inicial do navio horizontal
    // Validação: o navio deve caber horizontalmente no tabuleiro
    if (horizCol + SHIP_SIZE - 1 >= BOARD_SIZE) {
        printf("Erro: Navio horizontal extrapola os limites do tabuleiro.\n");
        return 1;
    }
    // Verifica sobreposição e posiciona o navio horizontal
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (board[horizRow][horizCol + i] == 3) {
            printf("Erro: Sobreposição no navio horizontal na posição (%d, %d).\n", horizRow, horizCol + i);
            return 1;
        }
        board[horizRow][horizCol + i] = 3;
    }
    
    // Navio 2: Vertical
    int vertRow = 5;     // Linha inicial do navio vertical
    int vertCol = 7;     // Coluna onde o navio vertical será posicionado
    // Validação: o navio deve caber verticalmente no tabuleiro
    if (vertRow + SHIP_SIZE - 1 >= BOARD_SIZE) {
        printf("Erro: Navio vertical extrapola os limites do tabuleiro.\n");
        return 1;
    }
    // Verifica sobreposição e posiciona o navio vertical
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (board[vertRow + i][vertCol] == 3) {
            printf("Erro: Sobreposição no navio vertical na posição (%d, %d).\n", vertRow + i, vertCol);
            return 1;
        }
        board[vertRow + i][vertCol] = 3;
    }
    
    // Navio 3: Diagonal crescente (linha e coluna aumentam)
    int diag1Row = 0;    // Linha inicial do navio diagonal (crescente)
    int diag1Col = 0;    // Coluna inicial do navio diagonal (crescente)
    // Validação: verifica se o navio cabe na diagonal crescente
    if (diag1Row + SHIP_SIZE - 1 >= BOARD_SIZE || diag1Col + SHIP_SIZE - 1 >= BOARD_SIZE) {
        printf("Erro: Navio diagonal crescente extrapola os limites do tabuleiro.\n");
        return 1;
    }
    // Posiciona o navio diagonal crescente
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (board[diag1Row + i][diag1Col + i] == 3) {
            printf("Erro: Sobreposição no navio diagonal crescente na posição (%d, %d).\n", diag1Row + i, diag1Col + i);
            return 1;
        }
        board[diag1Row + i][diag1Col + i] = 3;
    }
    
    // Navio 4: Diagonal decrescente (linha aumenta e coluna diminui)
    int diag2Row = 0;    // Linha inicial do navio diagonal (decrescente)
    int diag2Col = 9;    // Coluna inicial do navio diagonal (decrescente)
    // Validação: verifica se o navio cabe na diagonal decrescente
    if (diag2Row + SHIP_SIZE - 1 >= BOARD_SIZE || diag2Col - (SHIP_SIZE - 1) < 0) {
        printf("Erro: Navio diagonal decrescente extrapola os limites do tabuleiro.\n");
        return 1;
    }
    // Posiciona o navio diagonal decrescente
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (board[diag2Row + i][diag2Col - i] == 3) {
            printf("Erro: Sobreposição no navio diagonal decrescente na posição (%d, %d).\n", diag2Row + i, diag2Col - i);
            return 1;
        }
        board[diag2Row + i][diag2Col - i] = 3;
    }
    
    /*-----------------------------------------------------
     * Exibição do Tabuleiro
     *-----------------------------------------------------*/
    
    printf("Tabuleiro de Batalha Naval:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Imprime cada elemento com um espaço para melhor visualização
            printf("%d ", board[i][j]);
        }
        // Pula para a próxima linha após cada linha do tabuleiro
        printf("\n");
    }
    
    return 0;
}