#include <stdio.h>

#define BOARD_SIZE 10   // Tamanho do tabuleiro (10x10)
#define SHIP_SIZE 3     // Tamanho fixo dos navios (3 posições)

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    
    // Inicializa todas as posições do tabuleiro com 0 (água)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    
    // Definindo as coordenadas iniciais dos navios (valores definidos diretamente no código)
    // Navio Horizontal
    int horizRow = 2;   // Linha de posicionamento do navio horizontal
    int horizCol = 3;   // Coluna inicial do navio horizontal
    // Validação: Verifica se o navio horizontal cabe no tabuleiro
    if (horizCol + SHIP_SIZE > BOARD_SIZE) {
        printf("Erro: navio horizontal extrapola os limites do tabuleiro.\n");
        return 1;
    }
    
    // Navio Vertical
    int vertRow = 5;    // Linha inicial do navio vertical
    int vertCol = 7;    // Coluna de posicionamento do navio vertical
    // Validação: Verifica se o navio vertical cabe no tabuleiro
    if (vertRow + SHIP_SIZE > BOARD_SIZE) {
        printf("Erro: navio vertical extrapola os limites do tabuleiro.\n");
        return 1;
    }
    
    // Posiciona o navio horizontal na matriz (linha fixa, colunas consecutivas)
    for (int i = 0; i < SHIP_SIZE; i++) {
        // Validação simplificada para sobreposição (neste exemplo, não ocorrerá)
        if (board[horizRow][horizCol + i] == 3) {
            printf("Erro: sobreposição de navios na posição (%d, %d).\n", horizRow, horizCol + i);
            return 1;
        }
        board[horizRow][horizCol + i] = 3;
    }
    
    // Posiciona o navio vertical na matriz (coluna fixa, linhas consecutivas)
    for (int i = 0; i < SHIP_SIZE; i++) {
        // Validação para sobreposição
        if (board[vertRow + i][vertCol] == 3) {
            printf("Erro: sobreposição de navios na posição (%d, %d).\n", vertRow + i, vertCol);
            return 1;
        }
        board[vertRow + i][vertCol] = 3;
    }
    
    // Exibe o tabuleiro no console
    printf("Tabuleiro de Batalha Naval:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Imprime cada célula seguida de um espaço para melhor visualização
            printf("%d ", board[i][j]);
        }
        // Quebra de linha após cada linha do tabuleiro
        printf("\n");
    }
    
    return 0;
}