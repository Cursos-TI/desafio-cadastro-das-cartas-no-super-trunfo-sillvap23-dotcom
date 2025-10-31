#include <stdio.h>

// ---------- TORRE (recursiva) ----------
void moverTorre(int casas) {
    if (casas == 0) return; // condição de parada
    printf("Direita\n");
    moverTorre(casas - 1); // chamada recursiva
}

// ---------- BISPO (recursiva + loops aninhados) ----------
void moverBispo(int casas) {
    if (casas == 0) return; // condição de parada
    for (int i = 0; i < casas; i++) {         // movimento vertical
        for (int j = 0; j < casas; j++) {     // movimento horizontal
            printf("Diagonal Superior Direita\n");
        }
    }
    moverBispo(casas - 1); // chamada recursiva
}

// ---------- RAINHA (recursiva) ----------
void moverRainha(int casas) {
    if (casas == 0) return; // condição de parada
    printf("Cima\n");
    moverRainha(casas - 1); // chamada recursiva
}

// ---------- CAVALO (loops aninhados complexos) ----------
void moverCavalo(int movimentos) {
    int movVertical = 2; // duas casas para cima
    int movHorizontal = 1; // uma casa para a direita

    for (int i = 0; i < movimentos; i++) {  // controle de repetições
        for (int j = 0; j < movVertical + movHorizontal; j++) {
            if (j < movVertical) {
                printf("Cima\n");
                continue; // pula para o próximo sem sair do loop
            }
            if (j == movVertical) {
                printf("Direita\n");
                break; // encerra o loop interno
            }
        }
    }
}

int main() {
    int casasTorre = 3;
    int casasBispo = 2;
    int casasRainha = 4;
    int movimentosCavalo = 3;

    printf("=== Movimentacao da TORRE ===\n");
    moverTorre(casasTorre);

    printf("\n=== Movimentacao do BISPO ===\n");
    moverBispo(casasBispo);

    printf("\n=== Movimentacao da RAINHA ===\n");
    moverRainha(casasRainha);

    printf("\n=== Movimentacao do CAVALO ===\n");
    moverCavalo(movimentosCavalo);

    return 0;
}
