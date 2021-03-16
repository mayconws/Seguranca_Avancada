import random

# Função para calcular o totiente do numero primo
def num_totiente(numero): 
    
    if(num_primo(numero)):
        return numero-1
    else:
        return False

    
# Função para verificar se o número gerado é primo
def num_primo(n):
    
    if (n <= 1):
        return False

    if (n <= 3):
        return True

    if (n%2 == 0 or n%3 == 0):
        return False

    i = 5

    while(i * i <= n):
        if (n%i == 0 or n%(i + 2) == 0):
           return False

        i+=6

    return True

# Gerando um numero aleatório M, satisfazendo as condições
def gerado_M(numero): 

    def mdc(n1, n2):
        rest = 1
        
        while(n2 != 0):
            rest = n1%n2
            n1 = n2
            n2 = rest
        return n1

    while True:
        e = random.randrange(2, numero)

        if(mdc(numero, e) == 1):
            return e

# Gerando um numero primo aleatório
def gerar_num_primo():

    while True: 
        x=random.randrange(1, 100)

        if(num_primo(x)==True):
            return x

## Função modular entre dois números
def mod(a, b): # mod da função

    if(a<b):
        return a
    else:
        c=a%b
        return c   
    
# Cifra o texto digitado
def cifrar(words, e, n):
    
    tamanho = len(words)
    i = 0
    lista = []

    while(i < tamanho):
        letter = words[i]
        k = ord(letter)
        k = k**e
        d = mod(k,n)
        lista.append(d)
        i += 1
    return lista

# Descriptografa o texto criptografado
def descifrar(cifra, n, d):

    lista = []
    i = 0
    tamanho = len(cifra)
    # texto=cifra ^ d mod n
    while i < tamanho:
        result = cifra[i]**d
        texto = mod(result ,n)
        letra = chr(texto)
        lista.append(letra)
        i += 1
    return lista

# Calcula a chave privada
def calcular_chave_privada(toti, e):

    d = 0

    while(mod(d*e,toti)!=1):
        d += 1
    return d

# Função Principal
if __name__=='__main__':

    texto = input("Informe o texto: ")
    p = gerar_num_primo()
    q = gerar_num_primo()
    n = p*q
    y = num_totiente(p)
    x = num_totiente(q)
    totient_de_N = x*y 
    e = gerado_M(totient_de_N) 
    chave_publica = (n, e)

    print('Sua chave Pública:', chave_publica)
    texto_cifrado = cifrar(texto, e ,n)

    print('Sua mensagem Criptografada:', texto_cifrado)
    d = calcular_chave_privada(totient_de_N,e)

    print('Sua mensagem privada é:', d)

    texto_original = descifrar(texto_cifrado, n, d)
    print('Sua mensagem original:', texto_original)