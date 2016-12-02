#include <stdio.h>
#include <stdlib.h> 

int tamString(char *o) {// função responsável por contar o tamanho de uma String
    int i;
    for (i = 0; o[i]; i++);
    return (i);
}

void verificaArquivos(int argc){// Função para validar se a aplicação recebeu arquivo. 
	if(argc >= 2){
		printf("#OK [Arquivos enviados] : \n");
	} else {
		printf("#ERRO [Nao foi enviado arquivos]"); 
		exit(0);
	}
}

int validaTxt(char *nome){ // Função responsável por validar se o arquivo é texto ou não
    int t = tamString(nome);
    t = t - 4; 
    if ((nome[t]=='.')&&(nome[t+1]=='t')&&(nome[t+2]=='x')&&(nome[t+3]=='t')) {
        return(1);
    }
    else {
        return(0);
    }
}

int countMaiuscula(FILE *f){ // Função responsável por avaliar a quantidade de letras maiusculas dentro do arquivo
    int count = 0, t = 0;
    char let;
    t = fseek(f, 0, SEEK_SET);
    for(let = fgetc(f);!feof(f);let=fgetc(f)){
        if((let>='A')&&(let<='Z')) {
            count++;
        }
    }
    return(count);
}

int countMinusculo(FILE *f){ // Função responsável por avaliar a quantidade de letras minusculas dentro do arquivo
    int count = 0, t = 0;
    char let;
    t = fseek(f, 0, SEEK_SET);
    for(let = fgetc(f);!feof(f);let=fgetc(f)){
        if((let>='a')&&(let<='z')) {
            count++;
        }
    }
    return(count);
}

void verificaUnder(FILE *f,char *nome){ // Função responsável por verificar se o nome do arquivo começa com _
    int t;
    char let;
    if(nome[0] == '_') {
	    t=fseek(f, -1, SEEK_SET);// Vai para o inicio do arquivo
	    for(let = fgetc(f);!feof(f);let=fgetc(f)){
	        if ((let >= 'a')&&(let<='z')){
	            let=let-32;
	            fseek(f, 0, SEEK_CUR);
	            fprintf(f,"%c", let);
	        }
	    }
    }
}

void relGeral(int totalNaoTxt, int countBytesNaoTxt, int totalMinusculo, int totalMaiusculo, int countTotalBytes){
	printf("\n\n>> [Relatorio Geral - T25] <<\n"); 
	printf("\n>> Quantos arquivos nao eram TXT: %i", totalNaoTxt); 
	printf("\n>> Total de bytes dos arquivos que nao eram TXT: %i", countBytesNaoTxt);
	printf("\n>> Total de letras minuculas e maisculuas no TXT:");
	printf("\n   - Minuculas: %i \n   - Maisculuas: %i", totalMinusculo, totalMaiusculo);
	printf("\n>> Total geral de bytes em todos os arquivos: %i\n\n", countTotalBytes);
} 

int main(int argc, char *argv[]){
	FILE *f; 
	int i = 1, countBytes = 0, countTotalBytes = 0, txt = 0, totalMaiusculo = 0, totalMinusculo = 0, totalNaoTxt = 0, countBytesNaoTxt = 0;  
	verificaArquivos(argc);
	while(argv[i] != NULL){ 								// lendo os arquivos e avaliando os arquivos enviados. 
		f = fopen(argv[i], "r"); 							// Abrindo o arquivo
		fseek(f, 0, SEEK_END); 								// Função para ir para o fim do arquivo 
		countBytes = ftell(f); 								// Obtém posição atual do arquivo (fim)
		printf("\n[Arquivo %i] : %s 						[Bytes] : %d", i, argv[i], countBytes); 
		txt = validaTxt(argv[i]); 							// Envia pra função que vai descobrir se o arquivo é txt ou não
		if (txt == 1) { 									// validações se é txt ou não
		    totalMaiusculo = totalMaiusculo + countMaiuscula(f); 			// contando letras maisculuas
			totalMinusculo = totalMinusculo + countMinusculo(f); 			// contando letras minuculas 
			verificaUnder(f, argv[i]); 
		} else {
			totalNaoTxt++;									// Contado quantos arquivos não são txt
			countBytesNaoTxt = countBytesNaoTxt + ftell(f); // Somando o total de bytes de arquivos não txt 
		}
		countTotalBytes = countTotalBytes + ftell(f);
		fclose(f);
		i++; 
	}
	relGeral(totalNaoTxt, countBytesNaoTxt, totalMinusculo, totalMaiusculo, countTotalBytes);
	return 0; 
}