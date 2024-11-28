#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// Vari�veis globais
char jogo[3][3];
int l, c;
char jogador1[50] = "Jogador 1", jogador2[50] = "Jogador 2";
int vitoriaX = 0, vitoriaO = 0; // Contadores de vit�rias para cada jogador

// Procedimento para inicializar todas as posi��es da matriz.
void inicializarMatriz () {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            jogo[l][c] = ' ';
    }
}

// Procedimento para imprimir o jogo na tela.
void imprimir () {
     printf("\n\n\t 0   1   2 \n\n");
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            if (c == 0)
                printf("\t");
            printf(" %c ", jogo[l][c]);
            if (c < 2)
                printf("|");
            if (c == 2)
                printf("   %d", l);
        }
        printf("\n");
        if (l < 2)
            printf("\t----------\n");
    }
}

/*
 Fun��o para verificar vit�ria por linha.
 1 - Ganhou
 0 - N�o ganhou ainda
*/
int ganhouPorLinha (int l, char c) {
    if (jogo[l][0] == c && jogo[l][1] == c && jogo[l][2] == c)
        return 1;
    else
        return 0;
}

/*
    Fun��o para verificar vit�ria por linhas
    1 - Ganhou
    0 - N�o ganhou ainda
*/
int ganhouPorLinhas (char c) {
    int ganhou = 0;
    for (l = 0; l < 3; l++) {
        ganhou += ganhouPorLinha(l, c);
    }
    return ganhou;
}
/*
Fun��o para verificar vit�ria em uma coluna.
*/
int ganhouPorColuna (int c, char j) {
    if (jogo[0][c] == j && jogo[1][c] == j && jogo[2][c] == j)
        return 1;
    else
        return 0;
}
/*
Fun��o que verificar vit�ria por colunas
1 - Ganhou
0 - N�o ganhou ainda
*/
int ganhouPorColunas (char j) {
    int ganhou = 0;
    for (c = 0; c < 3; c++) {
        ganhou += ganhouPorColuna(c, j);
    }
    return ganhou;
}

/*
Fun��o para verificar vit�ria por diagonal principal
1 - Vit�ria
0 - N�o ganhou
*/
int ganhouPorDiagPrinc (char c) {
    if (jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c)
        return 1;
    else
        return 0;
}

/*
Fun��o para verificar vit�ria por diagonal secund�ria
1 - Vit�ria
0 - N�o ganhou
*/
int ganhouPorDiagSec (char c) {
    if (jogo[0][2] == c && jogo[1][1] == c && jogo[2][0] == c)
        return 1;
    else
        return 0;
}

/*
Fun��o que diz se uma coordenada � v�lida ou n�o.
1 - � v�lida
0 - N�o � v�lida
*/
int ehValida(int l, int c) {
    if (l >= 0 && l < 3 && c >= 0 && c < 3 && jogo[l][c] == ' ')
        return 1;
    else
        return 0;
}

// Procedimento para ler as coordenadas do usu�rio.
void lerCoordenadas(char j) {
    int linha, coluna;

    printf("Digite a linha e coluna (0, 1, 2): ");
    scanf("%d%d", &linha, &coluna);

    while (ehValida(linha, coluna) == 0) {
        printf("Coordenadas inv�lidas. Digite outra linha e coluna (0, 1, 2): ");
        scanf("%d%d", &linha, &coluna);
    }
    jogo[linha][coluna] = j;
}
// Função que retorna a quantidade de posições vazias.
int quantVazias() {
    int quantidade = 0;

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            if (jogo[l][c] == ' ')
                quantidade++;
    }
    return quantidade;
}



// Procedimento da jogada do computador
void jogadaComputador(char j) {
    srand(time(NULL)); 
    int linha, coluna;

    do {
        linha = rand() % 3;   
        coluna = rand() % 3;  
    } while (!ehValida(linha, coluna)); 

    jogo[linha][coluna] = j;  
}

// Função para jogar contra o computador
void jogarContraComputador() {
    int jogador = 1;
    char j1 = 'X', j2 = 'O';

    do {
        imprimir();
        if (jogador == 1) {
            printf("\nVez de %s (X)\n", jogador1);
            lerCoordenadas(j1);
            jogador = 2;
        } else {
            printf("\nVez do Computador (O)\n");
            jogadaComputador(j2);
            jogador = 1;
        }
    } while (quantVazias() > 0);

    imprimir();
    if (ganhouPorLinhas(j2) || ganhouPorColunas(j2) || ganhouPorDiagPrinc(j2) || ganhouPorDiagSec(j2)) {
        printf("\nParabéns %s! Você venceu!!\n", jogador2);
        vitoriaO++;
    } else if (ganhouPorLinhas(j1) || ganhouPorColunas(j1) || ganhouPorDiagPrinc(j1) || ganhouPorDiagSec(j1)) {
        printf("\nParabéns %s! Você venceu!!\n", jogador1);
        vitoriaX++;
    } else {
        printf("\nQue pena. Deu empate!\n");
    }
}
// Função para jogar com outro jogador
void jogarComOutroJogador() {
    int jogador = 1;
    char j1 = 'X', j2 = 'O';
    int vitoriaAtualX = 0, vitoriaAtualO = 0;

    do {
        imprimir();
        if (jogador == 1) {
            printf("\nVez de %s (X)\n", jogador1);
            lerCoordenadas(j1);  // Jogador 1 faz a jogada
            jogador = 2;          // Muda para a vez do Jogador 2
            vitoriaAtualX += ganhouPorLinhas(j1);
            vitoriaAtualX += ganhouPorColunas(j1);
            vitoriaAtualX += ganhouPorDiagPrinc(j1);
            vitoriaAtualX += ganhouPorDiagSec(j1);
        } else {
            printf("\nVez de %s (O)\n", jogador2);
            lerCoordenadas(j2);  // Jogador 2 faz a jogada
            jogador = 1;          // Muda para a vez do Jogador 1
            vitoriaAtualO += ganhouPorLinhas(j2);
            vitoriaAtualO += ganhouPorColunas(j2);
            vitoriaAtualO += ganhouPorDiagPrinc(j2);
            vitoriaAtualO += ganhouPorDiagSec(j2);
        }
    } while (vitoriaAtualX == 0 && vitoriaAtualO == 0 && quantVazias() > 0);

    imprimir();

    if (vitoriaAtualO == 1) {
        printf("\nParabéns %s. Você venceu!!\n", jogador2);
        vitoriaO++;
    } else if (vitoriaAtualX == 1) {
        printf("\nParabéns %s. Você venceu!!\n", jogador1);
        vitoriaX++;
    } else {
        printf("\nQue pena. Deu empate!\n");
    }
}
// Função para exibir o menu principal
void exibirMenu() {
    printf("\n=== Menu Principal ===\n");
    printf("1. Jogar Vs Player\n");
    printf("2. Jogar Vs Bot\n");
    printf("3. Nome dos Jogadores\n");
    printf("4. Ranking\n");
    printf("5. Créditos Finais\n");
    printf("6. Sair do Jogo\n");
    printf("=======================\n");
}

void alterarNomes() {
    printf("Digite o nome do Jogador 1: ");
    scanf(" %[^\n]", jogador1);
    printf("Digite o nome do Jogador 2: ");
    scanf(" %[^\n]", jogador2);
    printf("Nomes atualizados com sucesso!\n");
}

void mostrarRanking() {
    printf("\n=== Ranking ===\n");
    printf("1. %s - %d vit�rias\n", jogador1, vitoriaX);
    printf("2. %s - %d vit�rias\n", jogador2, vitoriaO);
    printf("=================\n");
}

void mostrarCreditos() {
    printf("\n=== Cr�ditos Finais ===\n");
    printf("Projeto: Jogo da Velha\n");
    printf("Desenvolvido por:\n\n D�bora Bruna\n Jeanny Elizabete\n Luiz Matheus\n Tarcila Rovitt\n Gabriel Ribeiro \n\n");
    printf("=========================\n");
}

// Função principal
int main() {
    int opcao;

    setlocale(LC_ALL, "pt_BR.UTF-8");
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inicializarMatriz();
                jogarComOutroJogador();
                break;
            case 2:
                inicializarMatriz();
                jogarContraComputador();
                break;
            case 3:
                alterarNomes();
                break;
            case 4:
                mostrarRanking();
                break;
            case 5:
                mostrarCreditos();
                break;
            case 6:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
