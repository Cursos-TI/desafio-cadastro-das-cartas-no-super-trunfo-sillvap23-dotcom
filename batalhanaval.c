#include <stdio.h>

#define ROWS 10
#define COLS 10

/* Códigos no tabuleiro */
#define AGUA 0
#define NAVIO 3
#define AFETADO 5

/* Tamanhos das matrizes de habilidade (fixos) */
#define SIZE 5   // usamos 5x5 para as três habilidades

/* Função para inicializar o tabuleiro (água) e plantar alguns navios de exemplo */
void inicializa_tabuleiro(int tab[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            tab[r][c] = AGUA;
        }
    }

    /* Exemplo: colocar alguns navios (valor 3) em posições fixas */
    tab[2][3] = NAVIO;
    tab[2][4] = NAVIO;
    tab[5][5] = NAVIO;
    tab[7][2] = NAVIO;
}

/* Imprime o tabuleiro: 0 = água, 3 = navio, 5 = área afetada */
void imprime_tabuleiro(int tab[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            printf("%d ", tab[r][c]);
        }
        printf("\n");
    }
}

/* Constrói uma matriz 5x5 para o CONE (apontando para baixo).
   A origem lógica do cone é o topo central da matriz (linha 0, coluna center).
   A matriz é preenchida com 1 nas células afetadas e 0 nas não afetadas.
   Uso de loops aninhados e condicionais para construir a forma de cone. */
void constroi_cone(int mat[SIZE][SIZE]) {
    int center = SIZE / 2; // coluna central (para 5 => 2)
    // Inicializa com 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = 0;
        }
    }

    /* A ideia do cone: linha 0 tem apenas a coluna center = 1 (topo).
       a cada linha abaixo (i crescente) expandimos 1 célula à esquerda e à direita
       formando um triângulo/ cone orientado para baixo. */
    for (int i = 0; i < SIZE; i++) {             // loop externo - vertical (linhas)
        int half_width = i;                      // quão largo fica o cone nesta linha
        for (int j = 0; j < SIZE; j++) {         // loop interno - horizontal (colunas)
            // Se coluna j estiver dentro do intervalo [center - half_width, center + half_width], marcamos
            if (j >= center - half_width && j <= center + half_width) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }
}

/* Constrói uma matriz 5x5 para a CRUZ.
   Origem no centro da matriz (linha center, coluna center). */
void constroi_cruz(int mat[SIZE][SIZE]) {
    int center = SIZE / 2;
    // inicializa com 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = 0;
        }
    }

    /* Cruz simples: marca toda a linha central e toda a coluna central.
       Utiliza loops aninhados e condicionais. */
    for (int i = 0; i < SIZE; i++) {           // vertical
        for (int j = 0; j < SIZE; j++) {       // horizontal
            if (i == center || j == center) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }
}

/* Constrói uma matriz 5x5 para o "octaedro" (vista frontal -> losango).
   Origem no centro da matriz (linha center, coluna center).
   A forma será um losango centrado. */
void constroi_octaedro(int mat[SIZE][SIZE]) {
    int center = SIZE / 2;
    // inicializa com 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = 0;
        }
    }

    /* Losango: as células cuja distância de Manhattan (|i-center| + |j-center|) <= radius serão 1.
       Para SIZE=5, radius = 2 (porque max distância até canto central é 2). */
    int radius = center; // 2 para SIZE 5
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int dist_manhattan = (i > center ? i - center : center - i) + (j > center ? j - center : center - j);
            if (dist_manhattan <= radius) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }
}

/* Sobrepõe matriz de habilidade ao tabuleiro.
   origin_row, origin_col: ponto de origem no tabuleiro (coordenadas onde a matriz será "centrada" ou "topo-central" colocada).
   align_top_center: se 1, então alinhamos a posição (0, center_col) da matriz com (origin_row, origin_col) no tabuleiro (para o cone).
                     se 0, então alinhamos o centro da matriz com origin (para cruz e octaedro).
   regras:
     - apenas alteramos células que atualmente são AGUA (0) para AFETADO (5)
     - checamos limites do tabuleiro */
void sobrepoe_habilidade(int tab[ROWS][COLS], int mat[SIZE][SIZE], int origin_row, int origin_col, int align_top_center) {
    int mat_center = SIZE / 2;

    for (int i = 0; i < SIZE; i++) {           // i = linha na matriz da habilidade
        for (int j = 0; j < SIZE; j++) {       // j = coluna na matriz
            if (mat[i][j] == 0) continue;      // só nos interessam posições afetadas (1)

            int target_row, target_col;

            if (align_top_center) {
                // alinhamento top-center:
                // queremos que (0, mat_center) mapeie para (origin_row, origin_col)
                // logo, deslocamento vertical = origin_row - 0, deslocamento horizontal = origin_col - mat_center
                target_row = origin_row + i;               // origin_row + i (i começa em 0)
                target_col = origin_col + (j - mat_center);
            } else {
                // alinhamento centro:
                // queremos que (mat_center, mat_center) mapeie para (origin_row, origin_col)
                // deslocamento = origin - mat_center
                target_row = origin_row + (i - mat_center);
                target_col = origin_col + (j - mat_center);
            }

            // checar limites do tabuleiro
            if (target_row < 0 || target_row >= ROWS || target_col < 0 || target_col >= COLS) {
                // fora dos limites -> ignorar (condicional exigida)
                continue;
            }

            // se for água, marcamos como afetado; se já for navio (3), mantemos 3.
            if (tab[target_row][target_col] == AGUA) {
                tab[target_row][target_col] = AFETADO;
            } else {
                // se desejarmos, podemos marcar também navios com outro número, mas por enquanto mantemos navios (3).
                // Comentário para explicar: preservamos navios para visualização.
            }
        }
    }
}

/* Função auxiliar para imprimir uma matriz de habilidade (apenas para debug/visualização).
   1 indica afetado, 0 indica não. */
void imprime_matriz(int mat[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tab[ROWS][COLS];
    inicializa_tabuleiro(tab);

    /* Construir as matrizes de habilidade dinamicamente (com loops aninhados e condicionais) */
    int mat_cone[SIZE][SIZE];
    int mat_cruz[SIZE][SIZE];
    int mat_octa[SIZE][SIZE];

    constroi_cone(mat_cone);
    constroi_cruz(mat_cruz);
    constroi_octaedro(mat_octa);

    /* --- Definir pontos de origem no tabuleiro (fixos no código) --- */
    // Para o cone, por decisão de implementação, origin indica a posição do topo do cone (topo-central).
    int origin_cone_row = 0 + 1; // exemplo: topo próximo ao topo do tabuleiro (linha 1)
    int origin_cone_col = 4;     // coluna 4 (0-indexed)

    // Para cruz e octaedro, origin representa o centro da habilidade no tabuleiro
    int origin_cruz_row = 4;
    int origin_cruz_col = 2;

    int origin_octa_row = 6;
    int origin_octa_col = 7;

    /* Exibir matrizes (opcional/debug) */
    printf("Matriz CONE (1 = afetado, 0 = nao):\n");
    imprime_matriz(mat_cone);

    printf("Matriz CRUZ (1 = afetado, 0 = nao):\n");
    imprime_matriz(mat_cruz);

    printf("Matriz OCTAEDRO (1 = afetado, 0 = nao):\n");
    imprime_matriz(mat_octa);

    /* Sobrepor as habilidades ao tabuleiro */
    sobrepoe_habilidade(tab, mat_cone, origin_cone_row, origin_cone_col, 1);  // align_top_center = 1
    sobrepoe_habilidade(tab, mat_cruz, origin_cruz_row, origin_cruz_col, 0);  // center alignment
    sobrepoe_habilidade(tab, mat_octa, origin_octa_row, origin_octa_col, 0);  // center alignment

    /* Imprimir tabuleiro final com áreas afetadas */
    printf("=== TABULEIRO FINAL (0=agua, 3=navio, 5=area afetada) ===\n");
    imprime_tabuleiro(tab);

    return 0;
}
