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
	scanf("%1f", &produto.preco);

        lista_produtos.push_back(produto);	
       

};

void listar_produto() {

    for (list<produto_t>::iterator listar = lista_produtos.begin(); listar != lista_produtos.end(); listar++){
        cout << "Produto: " << (listar)->nome << "\nCódigo: " << (listar)->codigo << "\nQuantidade: "
             << (listar)->qtd << "\nPreço: " << (listar)->preco << endl;
        
    };

};     
	


int main()
{	

	adicionar_produto();
        listar_produto();
        

	return 0;

}
