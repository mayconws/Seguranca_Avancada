#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno_t {

    char nome[50], email[50];
    int idade, opcao;
};

int main() 
{
	int c;
	int opcao = 0;
   
    aluno_t aluno[2];    
     
	printf("Forneça as informações necessárias:\n");
    for(c=0; c < 2;c++){
        printf("\nNome do aluno:");
        scanf("%s",aluno[c].nome);
        printf("\nEmail do aluno:");
        scanf("%s",aluno[c].email);
        printf("idade do Aluno:");
        scanf("%i",&aluno[c].idade);
	
	printf("Digite 1 para continuar ou 0 para imprimir os resultados:");
	scanf("%i",&opcao);
	
	if (opcao == 0)	{

		for(c = 0;c < 2;c++){
			printf("Nome do aluno:%s\n",aluno[c].nome);
			printf("Email do aluno:%s\n",aluno[c].email);
			printf("idade do aluno:%d\n",aluno[c].idade);
		}
	
    }	

}

    return 0;

}
