#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>

using namespace std;

struct produto_t {
	
	char nome[50];
	int codigo, qtd;
	double preco;
	
};

static list<produto_t> lista_produtos;


void adicionar_produto() {
		
	produto_t produto;	

	printf("\nDigite o nome do produto: ");
	scanf("%s", &produto.nome);
		
	printf("\nDigite o código do produto: ");
	scanf("%i", &produto.codigo);

	printf("\nDigite a quantidade do produto: ");
	scanf("%i", &produto.qtd);

	printf("\nDigite o preço do produto:");
	scanf("%lf", &produto.preco);

    lista_produtos.push_back(produto);       

};

void listar_produto() {

	printf("----- lISTA DE PRODUTOS -----\n");

    for (list<produto_t>::iterator listar = lista_produtos.begin(); listar != lista_produtos.end(); listar++){
        cout << "Produto: " << (listar)->nome << "\nCódigo: " << (listar)->codigo << "\nQuantidade: "
             << (listar)->qtd << "\nPreço: " << (listar)->preco << endl;
		printf("--------------------------\n");
        
    }

};

int menu_principal() {

	int opcao;
	
	while(opcao != 3) {
		
		printf("=== Escolha Uma das opções do Menu: ===\n");
		printf("\n1 - Adcionar Produtos: \n");
		printf("2 - Listar: \n");
		printf("3 - Voltar: \n");
		printf("\n====================================\n");

		printf("\nQual opção você deseja: ");
		scanf("%i", &opcao);
		
		if(opcao == 1) {

			adicionar_produto();					

		} else if (opcao == 2) {

			listar_produto();
		
		} else if (opcao == 3){
			
			printf("\n----- Voltando para a Tela Inicial -----");	
			return 0;
		}	

	}
	
};

int main()
{	
	char resposta[5];
	int i;

	printf ("================================");
	printf ("\n=== BEM VINDO AO SIS-ESTOQUE ===\n");
	printf ("================================\n");
	printf ("\nDeseja cadastrar um produto? Informe: ");	
    scanf ("%s",&resposta);
	
	while(1) {

    	if (!strcmp(resposta, "sim")) {
    				
			menu_principal();             
        
		} else {

			printf("\n--- Fechando o Sistema ---\n");
			printf("\n--- Obrigado! ---\n");
			break;
			
		}
	}			
        

	return 0;

};

