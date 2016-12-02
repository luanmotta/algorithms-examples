#include <stdio.h>
#include <conio.h>

#define TAM 20

int copiaString(char *st1, char *st2) {
	int i;
	for ( i = 0 ; st2[i] ; i++ )
		st1[i] = st2[i];

	st1[i] = 0; // colocando finalizador na string
}

// função para mostrar as duas formas possiveis de pegar a posicao de um vetor: por posicao e por ponteiro
int printaDuasVezes (char *st) {

	int i;

	// printando da forma 1
	for ( i = 0 ; st[i] ; i++ ) 
		printf("%c", st[i]);
	
	// printando da forma 2
	while (*st) 
		printf("%c", *st++); // o encremento do ponteiro de uma posição do vetor faz com que ele aponte para a próxima posição
	
}

char *retornaPalavra() {
	char *p;
	p = (char *)malloc(sizeof(char) * TAM);
	copiaString(p, "PalavraDaFuncao");
	return p;
}

int main() {

	char *palavra; // palavra a ser feita alocação dinâmica
	
	char palavra2[TAM]; // palavra com alocação estática

	// alocacao dinâmica
	palavra = (char *)malloc(sizeof(char)  * TAM);

	copiaString(palavra, "TesteNinja");

	printaDuasVezes(palavra);

	copiaString(palavra2, retornaPalavra() ); 

	printf("%s", palavra2);
	

	getch();
}