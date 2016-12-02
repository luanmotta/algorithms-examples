#include <stdio.h>
#include <stdlib.h> 

int tamString(char *o) {// função responsável por contar o tamanho de uma String
    int i;
    for (i = 0; o[i]; i++);
    return (i);
}

void verificaArquivos(int argc){		// Função para validar se a aplicação recebeu arquivo. 
	if(argc >= 2){ 				// se o parâmetro for >= 2, quer dizer que na execução do código, foi enviado um arquivo
		printf("#OK [Arquivos enviados] : \n");
	} else {
		printf("#ERRO [Nao foi enviado arquivos]");  // se for < 2, quer dizer que não foi enviado nenhum arquivo na execução do programa
		exit(0); // finaliza
	}
}

int validaTxt(char *nome){ 			// Função responsável por validar se o arquivo é texto ou não
    int t = tamString(nome); 			// usa a função responsável por retornar o tamanho da string. 
    t = t - 4; 					// Pega o tamanho da string e volta 4 "casas" :) 
    if ((nome[t]=='.')&&(nome[t+1]=='t')&&(nome[t+2]=='x')&&(nome[t+3]=='t')) { // identifica se as próximas 4 casas será .txt
        return(1); 				// se for txt retorna 1
    }
    else {
        return(0); // se não for txt retorna 0
    }
}

int countMaiuscula(FILE *f){ // Função responsável por avaliar a quantidade de letras maiusculas dentro do arquivo
    int count = 0, t = 0;
    char let;
    t = fseek(f, 0, SEEK_SET); 			// vai pra posição inicial do arquivo
    for(let = fgetc(f);!feof(f);let=fgetc(f)){  // enquanto a letra avaliada não !feof, executa 
        if((let>='A')&&(let<='Z')) { 		// valiando se é maiscula 
            count++; 				// se for maiscula a letra, contar + 1
        }
    }
    return(count); // retorna o valor
}

int countMinusculo(FILE *f){ // Função responsável por avaliar a quantidade de letras minusculas dentro do arquivo
    int count = 0, t = 0;
    char let;
    t = fseek(f, 0, SEEK_SET); 			// vai pra posição inicial do arquivo
    for(let = fgetc(f);!feof(f);let=fgetc(f)){  // valida enquanto o arquivo for diferente de feof
        if((let>='a')&&(let<='z')) { 		// valida caracteres minusculos 
            count++;
        }
    }
    return(count);
}

void verificaUnder(FILE *f,char *nome){ // Função responsável por verificar se o nome do arquivo começa com _
    int t;				
    char let;
    if(nome[0] == '_') {		// valida se a primeira letra do arquivo é _
	    t=fseek(f, -1, SEEK_SET);  // Vai para o inicio do arquivo
	    for(let = fgetc(f);!feof(f);let=fgetc(f)){
	        if ((let >= 'a')&&(let<='z')){
	            let=let-32; // para tornar a váriavel maiscula, é utilizado a manipulação da tabela ASC
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
		fclose(f); // por questões de segurança, após manipulado o arquivo, o mesmo deve ser encerrado. 
		i++; 
	}
	relGeral(totalNaoTxt, countBytesNaoTxt, totalMinusculo, totalMaiusculo, countTotalBytes);
	return 0; 
}


// a função fseek, é responsável por movimentar a posição onde o arquivo se encontra
// o final de um arquivo, pode ser identificado pelo retorno feof, utilizado aqui em algumas funções
// 



