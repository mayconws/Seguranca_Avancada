#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno_t {
    
    char nome[50];
    int idade;

};

int main()
{
    
    aluno_t aluno;
    aluno_t alunos;
    
    strcpy(aluno.nome, "Maycon");
    aluno.idade = 17;
    
    return 0;

}
