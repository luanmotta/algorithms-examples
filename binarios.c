/*
  parametro 1: ponteiro do dado que sera salvo
  parametro 2: tamanho unitario do dado que sera salvo
  parametro 3: quantidade de items com o tamanho do parametro 2 que sera salvo
  parametro 4: arquivo onde vai ser salvo
*/
fwrite(&tam, sizeof(int), 1, arq);// salva quantidade de alunos
fread(a, sizeof(struct ALUNOS), tam, arq);// le alunos


// salva tam e os alunos no arquivo (faz de conta q ta populado)
fwrite(&tam, sizeof(int), 1, arq);
fwrite(a, sizeof(struct ALUNOS), tam, arq);


/**** DESAFIO IMPORTANTE DADO PELO PROFESSOR ****/
/*
  Pegar precisamente apenas um aluno do arquivo binario e trazer para memoria
*/

int tam = 2;
struct ALUNOS a[tam];
FILE *arq = fopen("dados.bin", "rb");// adiciona o 'b' em qualquer operacao q envolva arquivo binario

// le o a quantidades de alunos que salvamos no inicio do arquivo
fread(&tam, sizeof(int), 1, arq);

int num = 5;//aluno 5 q queremos
int pos;
struct ALUNOS a;

// importante validar se ta dentro da quantidade q lemos no binario
if (num < 0 || num > tam) return (0);

// pegando posicao (num * tamanho unitario + tamanho de um inteiro)
pos = (num * sizeof(struct ALUNOS)) + sizeof(int);

// achando posicao do aluno
fseek(arq, pos, SEEK_SET);
fread(&a, sizeof(struct ALUNOS), 1, arq);

printf("%d %s \n", a.mat, a.nome);

fclose(arq);

/*
  Para alterar seria a mesma coisa so ter a posicao pegar o cara e editar ele e salvar no mesmo lugar
*/
fseek(arq, pos, SEEK_SET);
fwrite(&a, sizeof(struct ALUNOS), 1, arq);