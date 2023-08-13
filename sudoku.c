#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ERROR_FILE_MSG	"Nao foi possivel abrir o arquivo!\n"
#define INVALID_OPTION	"Opcao invalida! Tente novamente!"

enum boolean {
	falso=0, verd=1
};

/* Prototipos */
FILE* carregar(char quadro[9][9]);
//FILE* carregue_continue_jogo (char quadro[9][9], char *);
void carregue_continue_jogo(char quadro[9][9], char *nome_arquivo);
int determinar_quadrante(int x, int y);
FILE* crie_arquivo_binario(char quadro[9][9]);
int e_valido(const char quadro[9][9], int x, int y, int valor);
int e_valido_na_coluna(const char quadro[9][9], int y, int valor);
int e_valido_no_quadro3x3(const char quadro[9][9], int x, int y, int valor);
int e_valido_na_linha(const char quadro[9][9], int x, int valor);
int existe_campo_vazio(const char quadro[9][9]);
void imprime(const char quadro[9][9]);
void jogar();
void resolver(FILE*, char quadro[9][9]);
void resolver_um_passo(char quadro[9][9]);
void salvar_jogada_bin(FILE* fb, char quadro[9][9]);

/* Funcoes auxiliares */
int fim_x(int quadr);
int fim_y(int quadr);
int le_opcao();
void gen_random(char *s, const int len);
int ini_x(int quadr);
int ini_y(int quadr);
void menu();
void menu_arquivo();


/* -----------------------------------------------------------------------------
 * -----------------------------------------------------------------------------
 * MAIN
 * /////////////////////////////////////////////////////////////////////////////
 */
int main() {

	// inicia o jogo
	jogar();

	return 0;
}

/* -----------------------------------------------------------------------------
 * CARREGAR
 * Inicializa o SUDOKU a partir de um novo jogo ou estado de jogo anterior
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
FILE* carregar(char quadro[9][9]) {
	int opcao;

	menu_arquivo();
	opcao = le_opcao();

	// TODO Função incompleta

	switch(opcao) {

		// carregar novo sudoku
		case 1:
		carregue_carregue_novo_jogo(quadro,"01.txt");
			break;

		// continuar jogo
		case 2:
		carregue_continue_jogo(quadro,"01.txt");
			break;

		// retornar ao menu anterior
		case 9:
		menu();
			break;

		default:
			break;
}
return NULL;
}
/* -----------------------------------------------------------------------------
 * CARREGAR CONTINUAR JOGO
 * Carrega um estado de jogo a partir de um arquivo binário
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void carregue_continue_jogo(char quadro[9][9], char *nome_arquivo) {
	FILE *arquivo = fopen(nome_arquivo, "rb");
	if (arquivo == NULL) {
		printf(ERROR_FILE_MSG);
		return;
	}

	fread(quadro, sizeof(char), 9 * 9, arquivo);

	fclose(arquivo);
	printf("Jogo anterior carregado com sucesso!\n");
}

/* -----------------------------------------------------------------------------
 * CARREGAR NOVO JOGO
 * Carrega um novo jogo do Sudoku a partir de um arquivo de texto
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void carregue_carregue_novo_jogo(char quadro[9][9], char *nome_arquivo) {
	FILE *arquivo = fopen(nome_arquivo, "r");
	if (arquivo == NULL) {
		printf(ERROR_FILE_MSG);
		return;
	}

	int i, j;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (fscanf(arquivo, "%d", &quadro[i][j]) != 1) {
				printf("Erro ao ler o arquivo.\n");
				fclose(arquivo);
				return;
			}
		}
	}

	fclose(arquivo);
	printf("Novo jogo carregado com sucesso!\n");
}

FILE* crie_arquivo_binario(char quadro[9][9]) {
    FILE *arquivo = fopen("01.bin", "wb"); // Substitua pelo nome desejado para o arquivo binário

    if (arquivo == NULL) {
        printf("Não foi possível criar o arquivo binário.\n");
        return NULL;
    }

    // Escreva os dados da matriz quadro no arquivo binário
    fwrite(quadro, sizeof(char), 9 * 9, arquivo);

    fclose(arquivo); // Feche o arquivo após escrever

    printf("Arquivo binário criado com sucesso.\n");

    return fopen("01.bin", "rb"); // Abra o arquivo novamente em modo de leitura binária
}

/* -----------------------------------------------------------------------------
 * DETERMINAR QUADRANTE
 * Dado as posicoes x e y, determina o quadrante do quadro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int determinar_quadrante(int x, int y) {
	if (x < 3 && y < 3)
		return 1;
	else if (x < 3 && y < 6)
		return 2;
	else if (x < 3 && y < 9)
		return 3;
	else if (x < 6 && y < 3)
		return 4;
	else if (x < 6 && y < 6)
		return 5;
	else if (x < 6 && y < 9)
		return 6;
	else if (x < 9 && y < 3)
		return 7;
	else if (x < 9 && y < 6)
		return 8;
	else
		return 9;
}

/* -----------------------------------------------------------------------------
 * E VALIDO
 * Determina se um valor na posicao x e y e valido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int e_valido(const char quadro[9][9], int x, int y, int valor) {

	// verifica as tres condicoes
	if (!e_valido_na_coluna(quadro, y, valor))
		return falso;
	if (!e_valido_na_linha(quadro, x, valor))
		return falso;
	if (!e_valido_no_quadro3x3(quadro, x, y, valor))
		return falso;

	return verd;
}

/* -----------------------------------------------------------------------------
 * E VALIDO NA COLUNA
 * Verifica se um valor na coluna y é válido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
 //IMPLEMNETADA
int e_valido_na_coluna(const char quadro[9][9], int y, int valor) {
    for (int i = 0; i < 9; i++) {
        if (quadro[i][y] == valor) {
            return falso; // O valor já existe na coluna
        }
    }
    return verd; // O valor é válido na coluna
}



/* -----------------------------------------------------------------------------
 * E VALIDO NA LINHA
 * Verifica se um valor na linha x é válido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int e_valido_na_linha(const char quadro[9][9], int x, int valor) {
    for (int j = 0; j < 9; j++) {
        if (quadro[x][j] == valor) {
            return falso; // O valor já existe na linha
        }
    }
    return verd; // O valor é válido na linha
}


/* -----------------------------------------------------------------------------
 * E VALIDO NO QUADRO 3X3
 * Verifica se um valor é válido no quadrante da posição x, y
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int e_valido_no_quadro3x3(const char quadro[9][9], int x, int y, int valor) {
    int ini_x_quad = ini_x(determinar_quadrante(x, y));
    int ini_y_quad = ini_y(determinar_quadrante(x, y));

    for (int i = ini_x_quad; i <= fim_x(determinar_quadrante(x, y)); i++) {
        for (int j = ini_y_quad; j <= fim_y(determinar_quadrante(x, y)); j++) {
            if (quadro[i][j] == valor) {
                return falso; // O valor já existe no quadrante
            }
        }
    }
    return verd; // O valor é válido no quadrante
}




/* -----------------------------------------------------------------------------
 * EXISTE CAMPO VAZIO
 * Verifica se existe um campo nao preenchido
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int existe_campo_vazio(const char quadro[9][9]) {
	int i, j;

	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			if (quadro[i][j] == 0)
				return verd;
		}
	}

	return falso;
}

/* -----------------------------------------------------------------------------
 * IMPRIMIR
 * Imprime o quadro inteiro do sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void imprime(const char quadro[9][9]) {
	int i, j;

//	puts("~~~~~~~~ SUDOKU ~~~~~~~~");
	puts("    1 2 3   4 5 6   7 8 9");
	for (i = 0; i < 9; i++) {
		if (i % 3 == 0)
			puts("  -------------------------");
		for (j = 0; j < 9; j++) {

			if (j == 0)
				printf("%d | ", i+1);
			else if (j % 3 == 0)
				printf("| ");

			if (quadro[i][j] == 0)
				printf("- ");
			else
				printf("%d ", quadro[i][j]);
		}
		puts("|");
	}
	puts("  -------------------------");
}

/* -----------------------------------------------------------------------------
 * JOGAR
 * Realiza toda a logica do jogo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void jogar() {
	int opcao;
	char quadro[9][9] = { {0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	FILE *fb = fopen("01", "r");

	opcao = 0;

	while (opcao != 9) {
		// imprime na tela o quadro atual
		imprime(quadro);

		// apresenta um menu com as opcoes
		menu();
		opcao = le_opcao();

		switch (opcao) {

		// carregar sudoku
		case 1:
			fb = carregar(quadro);

			if (fb == fopen("01", "r")) {
				fb = crie_arquivo_binario(quadro);
			}
			break;

		// preencher quadro com um valor
		case 2: {
			int x, y, valor;

			printf("Entre com a posicao e o valor (linha, coluna, valor): ");
			scanf("%d %d %d", &x, &y, &valor);


			if (e_valido(quadro, x, y, valor)) {
				quadro[x][y] = valor;
				salvar_jogada_bin(fb, quadro);
			}
			else
				puts("Valor ou posicao incorreta! Tente novamente!");
		}
			break;

		// resolver 1 passo
		case 3:
			resolver_um_passo(quadro);
			salvar_jogada_bin(fb, quadro);
			puts("Um passo resolvido!");
			break;

		// resolver o sudoku
		case 4:
			resolver(fb, quadro);
			break;

		case 9:
			puts("Programa finalizado ..");
			break;

		default:
			puts(INVALID_OPTION);
			break;
		}
	}
}

/* -----------------------------------------------------------------------------
 * RESOLVER
 * Resolve o sudoku
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int resolver_sudoku(char quadro[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (quadro[row][col] == 0) {  // Encontrou um campo vazio
                for (int num = 1; num <= 9; num++) {
                    if (e_valido(quadro, row, col, num)) {  // Verifica se o número é válido
                        quadro[row][col] = num;  // Preenche com um número válido
                        if (resolver_sudoku(quadro))  // Tenta resolver o restante do jogo
                            return 1;  // Retorna 1 se o jogo for resolvido
                        quadro[row][col] = 0;  // Se não for possível resolver, desfaz a jogada
                    }
                }
                return 0;  // Retorna 0 se não for possível resolver com o número atual
            }
        }
    }
    return 1;  // Retorna 1 se todas as posições estiverem preenchidas corretamente
}

void resolver(FILE *fb, char quadro[9][9]) {
    if (resolver_sudoku(quadro)) {
        salvar_jogada_bin(fb, quadro);
        printf("Jogo resolvido e jogada salva com sucesso!\n");
    } else {
        printf("Não foi possível resolver o jogo.\n");
    }
}



int contar_campos_vazios(const char quadro[9][9]) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (quadro[i][j] == 0) {
                count++;
            }
        }
    }
    return count;
}


/* -----------------------------------------------------------------------------
 * RESOLVER UM PASSO
 * Preenche apenas um campo vazio
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void resolver_um_passo(char quadro[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (quadro[i][j] == 0) {  // Se o campo estiver vazio
                for (int valor = 1; valor <= 9; valor++) {
                    if (e_valido(quadro, i, j, valor)) {  // Se o valor for válido
                        quadro[i][j] = valor;  // Preencha o campo com o valor
                        return;  // Saia da função após preencher um campo vazio
                    }
                }
            }
        }
    }
}


/* -----------------------------------------------------------------------------
 * SALVAR JOGADA BINARIO
 * Salva o estado atual do quadro no arquivo binario
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void salvar_jogada_bin(FILE *fb, char quadro[9][9]) {
	if (fb == NULL) {
		printf("Erro: arquivo binário não aberto.\n");
		return;
	}

	// Volte para o início do arquivo
	rewind(fb);

	// Escreva os dados da matriz quadro no arquivo binário
	fwrite(quadro, sizeof(char), 9 * 9, fb);

	printf("Jogada salva com sucesso!\n");
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 							FUNCOES AUXILIARES
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/* -----------------------------------------------------------------------------
 * FIM X
 * Indice final da linha para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int fim_x(int quadr) {
	switch(quadr) {
		case 1:
		case 2:
		case 3:
			return 2;

		case 4:
		case 5:
		case 6:
			return 5;

		default:
			return 8;
	}
}

/* -----------------------------------------------------------------------------
 * FIM Y
 * Indice final da coluna para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int fim_y(int quadr) {
	switch(quadr) {
		case 1:
		case 4:
		case 7:
			return 2;

		case 2:
		case 5:
		case 8:
			return 5;

		default:
			return 8;
	}
}

/* -----------------------------------------------------------------------------
 * GEN_RANDOM
 * Gera uma cadeira de caracteres randomica de tamanho len
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void gen_random(char *s, const int len) {
	srand(time(NULL));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
	int i;

    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

/* -----------------------------------------------------------------------------
 * INI X
 * Indice inicial da linha para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ini_x(int quadr) {
	switch(quadr) {
		case 1:
		case 2:
		case 3:
			return 0;

		case 4:
		case 5:
		case 6:
			return 3;

		default:
			return 6;
	}
}

/* -----------------------------------------------------------------------------
 * INI Y
 * Indice inicial da coluna para o quadrante recebido como parametro
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int ini_y(int quadr) {
	switch(quadr) {
		case 1:
		case 4:
		case 7:
			return 0;

		case 2:
		case 5:
		case 8:
			return 3;

		default:
			return 6;
	}
}

/* -----------------------------------------------------------------------------
 * LE OPCAO
 * Imprime a mensagem a faz a leitura da opcao
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int le_opcao () {
	int opcao;

	printf("Opcao: ");
	scanf("%d", &opcao);

	return opcao;
}

/* -----------------------------------------------------------------------------
 * MENU
 * Imprime o menu de opcoes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu() {
	puts("\n~~~~~~~~ SUDOKU ~~~~~~~~");
	puts("[1] - Carregar jogo");
	puts("[2] - Jogar");
	puts("[3] - Resolver um passo");
	puts("[4] - Resolver");
	puts("[9] - Finalizar");
	puts("--------");
}

/* -----------------------------------------------------------------------------
 * MENU ARQUIVO
 * Imprime o menu de opcoes do arquivo
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void menu_arquivo() {
	puts("\n~~~~~ MENU ARQUIVO ~~~~~");
	puts("[1] - Novo jogo");
	puts("[2] - Continuar jogo");
	puts("[9] - Retornar ao menu anterior");
	puts("--------");
}
