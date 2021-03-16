#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

typedef struct contato CONTATO;
struct contato
{
    int ativo;
    char nome[50];
    char cpf[30];
};
void flush_in();
void cadastrar();
void listar();
void editar();
//VARIAVEL UNIVERSAL
FILE *arquivo;
CONTATO ctt;
int op;
int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    do
    {
        system("cls");
        printf("\n1 - Cadastrar");
        printf("\n2 - Listar");
        printf("\n3 - Editar");
        printf("\n0 - Sair\n\n");

        printf("Digite uma opção: ");
        scanf("%d", &op);
        //flush_in();

        switch(op)
        {
            case 1:
                cadastrar();
            break;
            case 2:
                listar();
            break;
            case 3:
                editar();
            break;
            case 0:
            break;
            default:
                printf("\nOpção Inválida!\n");
                getch();
            break;
        }

    }while(op!=0);
}
void flush_in() {
    int ch;
    
    while ( ( ch = fgetc ( stdin ) ) != '\n' && ch != EOF) {}
}
void cadastrar()
{
    flush_in();
	do
    {
        arquivo = fopen("base.txt","a+b");
        system("cls");
        printf("Nome: ");
        gets(ctt.nome);

        printf("CPF: ");
        gets(ctt.cpf);

        ctt.ativo = 1;

        fwrite(&ctt, sizeof(CONTATO),1,arquivo);
        fclose(arquivo);
        printf("Deseja realizar novo Cadastro (s/n)?");
    }while(getche()=='s');

}
void listar()
{
    system("cls");

    arquivo = fopen("base.txt","rb");

    while(fread(&ctt,sizeof(CONTATO),1,arquivo)==1)
    {
        printf("Status: %d\n", ctt.ativo);
        printf("Nome: %s\n",ctt.nome);
        printf("CPF: %s\n",ctt.cpf);
        printf("--------------------\n\n");
    }
    fclose(arquivo);
    getch();

}
void editar()
{
    int posicao = 0; // Inicio do Arquivo;
    int achou = 0;
    char AltCpf[30];
    char AltNome[50];


    flush_in();
    printf("Digite o CPF: ");
    gets(AltCpf);

    arquivo = fopen("base.txt","r+b");

    system("cls");
    op = -1;
    while(fread(&ctt, sizeof(CONTATO), 1, arquivo)==1 && op!=0)
    {
        if(strcmp(AltCpf,ctt.cpf)==0)
        {
            printf("\n1 - Nome: %s",ctt.nome);
            printf("\n2 - CPF: %s",ctt.cpf);
            printf("\n0 - Voltar");
            printf("\n-------------\n\n");

            printf("\n\nEscolha uma opção: ");
            scanf("%d", &op);
            flush_in();

            switch(op)
            {
                case 1:
                    printf("Digite o Novo nome: ");
                    gets(ctt.nome);

                    fseek(arquivo, posicao, SEEK_SET);
                    achou= fwrite(&ctt,sizeof(CONTATO),1,arquivo) == sizeof(CONTATO);
                break;
                
                case 2:
                    printf("Digite o novo CPF: ");
                    gets(ctt.cpf);

                    fseek(arquivo, posicao, SEEK_SET);
                    achou= fwrite(&ctt,sizeof(CONTATO),1,arquivo) == sizeof(CONTATO);
                break;

                case 0:
                	/*Não se deve chamar main() de dentro da função, isso criar uma recursividade
					com comportamento imprevisivel*/
                	//main();
                break;
                
                default:
                    printf("\nOpção Inválida!\n");
                    getch();
                break;
            }

        }
        /*É aqui que a posição deve ser atualizada, no final do ciclo WHILE,
        sendo descolocado de +sizeof(CONTATO) a cada iteração do ciclo*/
        posicao = posicao + sizeof(CONTATO);
        
        /*Move posição de leitura/escrita de volta para a posição original*/
        fseek(arquivo, posicao, SEEK_SET);
    }
    op=-1;
    fclose(arquivo);
}