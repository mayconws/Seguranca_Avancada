#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

FILE *abrir_arquivo(char *fname)
{
    FILE *arquivo;

    arquivo = fopen(fname, "rb+");

    if (arquivo == NULL)
    {
        arquivo = fopen(fname, "wb");

        if (arquivo == NULL)
        {
            printf("impossivel criar arquivo %s\n", fname);
            exit(1);
        }

        fclose(arquivo);

        arquivo = fopen(fname, "rb+");

        if (arquivo == NULL)
        {
            printf("impossivel abrir arquivo %s\n", fname);
            exit(1);
        }
    }

    return arquivo;
}

struct Cliente
{
    int codigo;
    char nome[100];
    int anoNasimento;
    char email[100];
    double valorComprado;
};

struct Produto
{
    int codigo;
    char nome[100];
    double valor;
};

struct Venda
{
    int codigo;
    int produto_codigo;
    int cliente_codigo;
};

void Vender()
{

    FILE *arquivoVenda;
    FILE *arquivoProduto;
    FILE *arquivoCliente;
    int n;
    int n2;
    int codigoPro;
    int codigoCli;
    int encontreiProduto = 0;
    int encontreiCliente = 0;
    double valorprodutoComprado;

    Produto produto;
    Cliente cliente;
    Venda venda;

    arquivoVenda = abrir_arquivo("venda.txt");

    cout << "Informe o codigo da venda: " << endl;
    cin >> venda.codigo;

    cout << "Informe o codigo do produto: " << endl;
    cin >> codigoPro;

    cout << "Informe o codigo do cliente: " << endl;
    cin >> codigoCli;

    arquivoProduto = abrir_arquivo("produto.txt");
    fseek(arquivoProduto, 0, SEEK_SET);

    arquivoCliente = abrir_arquivo("cliente.txt");
    fseek(arquivoCliente, 0, SEEK_SET);

    while (fread(&produto, sizeof(Produto), 1, arquivoProduto))
    {
        if (codigoPro == produto.codigo)
        {

            encontreiProduto = 1;
        }
    }

    if (encontreiProduto != 1)
    {
        cout << "Produto não encontrado" << endl;
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente))
    {
        if (codigoCli == cliente.codigo)
        {
            encontreiCliente = 1;
        }
    }

    if (encontreiCliente != 1)
    {
        cout << "Cliente não encontrado" << endl;
        return;
    }

    if (encontreiCliente == 1 && encontreiProduto == 1)
    {

        cliente.valorComprado += valorprodutoComprado;
        venda.produto_codigo = produto.codigo;
        venda.cliente_codigo = cliente.codigo;

        fseek(arquivoVenda, 0, SEEK_END);
        fwrite(&venda, sizeof(Venda), 1, arquivoVenda);
        fclose(arquivoVenda);
    }
}

void inserirProduto()
{
    FILE *arquivo;
    int n;

    Produto produto;
    arquivo = abrir_arquivo("produto.txt");

    cout << " Informe o codigo do Produto " << endl;
    cin >> produto.codigo;

    cout << "Informe a descrição: " << endl;
    cin >> produto.nome;

    cout << "Informe o valor: " << endl;
    cin >> produto.valor;

    fseek(arquivo, 0, SEEK_END);
    fwrite(&produto, sizeof(Produto), 1, arquivo);
    fclose(arquivo);
}

void inserirCliente()
{
    FILE *arquivo;
    int n;

    Cliente cliente;

    arquivo = abrir_arquivo("cliente.txt");

    cout << "informe o id: " << endl;
    cin >> cliente.codigo;

    cout << "informe nome do cliente: " << endl;
    cin >> cliente.nome;

    cout << "digite ano de nasimento: " << endl;
    cin >> cliente.anoNasimento;

    cout << "informe seu email: " << endl;
    cin >> cliente.email;

    fseek(arquivo, 0, SEEK_END);
    fwrite(&cliente, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
}

void listar_produto()
{
    FILE *arquivo;
    Produto produto;
    int n;

    arquivo = abrir_arquivo("produto.txt");
    fseek(arquivo, 0, SEEK_SET);

    cout << "========== Lista de Produtos ========== " << endl;
    while (fread(&produto, sizeof(Produto), 1, arquivo))
    {

        cout << produto.codigo << " - " << produto.nome << " - " << produto.valor<< endl;
    }

    fclose(arquivo);
}

void listar_venda()
{
    FILE *arquivoVenda;
    Venda venda;
    Produto produto;
    Cliente cliente;
    int n;

    arquivoVenda = abrir_arquivo("venda.txt");
    fseek(arquivoVenda, 0, SEEK_SET);

    cout << "========== Lista de Produtos Vendidos ========== " << endl;
    while (fread(&venda, sizeof(Venda), 1, arquivoVenda))
    {
        cout << "Codigo da Venda "
             << " - " << venda.codigo << endl;
        cout << "Codigo do Produto "
             << " - " << venda.produto_codigo << endl;
        cout << "Codigo do Cliente "
             << " - " << venda.cliente_codigo << endl;

        FILE *arquivoProduto;
        arquivoProduto = abrir_arquivo("produto.txt");
        fseek(arquivoProduto, 0, SEEK_SET);

        while (fread(&produto, sizeof(Produto), 1, arquivoProduto))
        {
            if (venda.produto_codigo == produto.codigo)
            {
                cout << "Nome do Produto: " << produto.nome << endl;
            }
        }

        FILE *arquivoCliente;
        arquivoCliente = abrir_arquivo("cliente.txt");
        fseek(arquivoCliente, 0, SEEK_SET);
        while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente))
        {
            if (venda.cliente_codigo == cliente.codigo)
            {
                cout << "Nome do Cliente: " << cliente.nome << endl;
            }
        }
    }

    fclose(arquivoVenda);
}

void listar_cliente()
{
    FILE *arquivo;
    Cliente cliente;
    int n;

    arquivo = abrir_arquivo("cliente.txt");
    fseek(arquivo, 0, SEEK_SET);

    cout << "========== Lista de clientes ==========" << endl;

    while (fread(&cliente, sizeof(Cliente), 1, arquivo))
    {

        cout << cliente.codigo << " - " << cliente.nome << endl;
    }

    fclose(arquivo);
}

void alterar_cliente()
{
    FILE *arquivo;
    Cliente cliente;
    int codigo;

    cout << "========== Digite o id do cliente para alterar ==========" << endl;
    cin >> codigo;

    arquivo = abrir_arquivo("cliente.txt");
    while (fread(&cliente, sizeof(Cliente), 1, arquivo))
    {
        if (cliente.codigo == codigo)
        {
            fseek(arquivo, sizeof(Cliente) * -1, SEEK_CUR);

            cout << "Digite o novo nome: " << endl;
            cin >> cliente.nome;

            cout << "Digite o novo email: " << endl;
            cin >> cliente.email;
            

            fwrite(&cliente, sizeof(Cliente), 1, arquivo);
        }
    }
    fclose(arquivo);
}

void alterar_produto()
{
    FILE *arquivo;
    Produto produto;
    int codigo;

    cout << "========== Digite o id do produto para alterar ==========" << endl;
    cin >> codigo;

    arquivo = abrir_arquivo("produto.txt");
    while (fread(&produto, sizeof(Produto), 1, arquivo))
    {
        if (produto.codigo == codigo)
        {
            fseek(arquivo, sizeof(Produto) * -1, SEEK_CUR);

            cout << "Digite o novo nome: " << endl;
            cin >> produto.nome;

            cout << "Digite o novo preço: " << endl;
            cin >> produto.valor;

            fwrite(&produto, sizeof(Produto), 1, arquivo);
        }
    }
    fclose(arquivo);
}

void excluirCliente()
{
    FILE *arquivo;
    Cliente cliente;
    int codigo;
    int posicao;
    int posicaoatrucar;

    cout << "========== Digite o id do cliente para excluir ==========" << endl;
    cin >> codigo;
    arquivo = abrir_arquivo("cliente.txt");
    while (fread(&cliente, sizeof(Cliente), 1, arquivo))
    {
        if (cliente.codigo == codigo)
        {
            posicao = ftell(arquivo) - sizeof(cliente);
            fseek(arquivo, sizeof(Cliente) * -1, SEEK_END);
            posicaoatrucar = ftell(arquivo);
            fread(&cliente, sizeof(Cliente), 1, arquivo);
            fseek(arquivo, posicao, SEEK_SET);
            fwrite(&cliente, sizeof(Cliente), 1, arquivo);
            fflush(arquivo);
            ftruncate(fileno(arquivo), posicaoatrucar);
            break;
        }
    }
    fclose(arquivo);
}

void excluirProduto()
{
    FILE *arquivo;
    Produto produto;
    int codigo;
    int posicao;
    int posicaoatrucar;

    cout << "========== Digite o id do produto para excluir ==========" << endl;
    cin >> codigo;
    arquivo = abrir_arquivo("produto.txt");
    while (fread(&produto, sizeof(Produto), 1, arquivo))
    {
        if (produto.codigo == codigo)
        {
            posicao = ftell(arquivo) - sizeof(produto);
            fseek(arquivo, sizeof(Produto) * -1, SEEK_END);
            posicaoatrucar = ftell(arquivo);
            fread(&produto, sizeof(Produto), 1, arquivo);
            fseek(arquivo, posicao, SEEK_SET);
            fwrite(&produto, sizeof(Produto), 1, arquivo);
            fflush(arquivo);
            ftruncate(fileno(arquivo), posicaoatrucar);
            break;
        }
    }
    fclose(arquivo);
}

int main()
{

    int opcao;
    int opcao2;

    do
    {
        
        cout << "===========================" << endl;
        cout << "Bem Vindo Ao SIS-ESTOQUE" << endl;
        cout << "===========================" << endl;
        cout << "Escolha uma das opções:" << endl;
        cout << "1 - Cliente" << endl;
        cout << "2 - Produto" << endl;
        cout << "3 - Venda" << endl;

    
        cin >> opcao;

        if (opcao == 1)
        {   
            cout << "===========================" << endl;
            cout << "O que você deseja realizar:" << endl;
            cout << "===========================" << endl;
            cout << "1 - Cadastrar" << endl;
            cout << "2 - Listar" << endl;
            cout << "3 - Excluir" << endl;
            cout << "4 - Alterar" << endl;

            cin >> opcao2;

            if (opcao2 == 1)
            {
                inserirCliente();
            }
            else if (opcao2 == 2)
            {
                listar_cliente();
            }
            else if (opcao2 == 3)
            {
                listar_cliente();

                excluirCliente();
            }
            else if (opcao2 == 4)
            {
                alterar_cliente();
            }
        }
        else if (opcao == 2)
        {

            cout << "===========================" << endl;
            cout << "O que você deseja realizar:" << endl;
            cout << "===========================" << endl;
            cout << "1 - Cadastrar" << endl;
            cout << "2 - Listar" << endl;
            cout << "3 - Excluir" << endl;
            cout << "4 - Alterar" << endl;
            cin >> opcao2;

            if (opcao2 == 1)
            {

                inserirProduto();
            }
            else if (opcao2 == 2)
            {
                listar_produto();
            }
            else if (opcao2 == 3)
            {
                listar_produto();
                excluirProduto();
            }
            else if (opcao2 == 4)
            {
                alterar_produto();
            }
        }
        else if (opcao == 3)
        {

            cout << "===========================" << endl;
            cout << "O que você deseja realizar:" << endl;
            cout << "===========================" << endl;
            cout << "1 - Vender" << endl;
            cout << "2 - Listar" << endl;

            cin >> opcao2;

            if (opcao2 == 1)
            {

                cout << "======================================" << endl;
                cout << "Lista de todos os clientes cadastrados" << endl;
                 cout << "======================================" << endl;
                listar_cliente();

                cout << "======================================" << endl;
                cout << "Lista de todos os produtos cadastrados" << endl;
                cout << "======================================" << endl;
                listar_produto();
                
                cout << "==========" << endl;
                cout << "Menu Venda" << endl;
                cout << "==========" << endl;
                Vender();
            }
            else if (opcao2 == 2)
            {
                listar_venda();
            }
        }
    } while (opcao != 0);

    return 0;
}