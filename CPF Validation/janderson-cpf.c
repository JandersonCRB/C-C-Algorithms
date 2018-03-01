#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 1
#define D(value) if (DEBUG) value;


int validSize(char *cpf)
{
    return (strlen(cpf) == 15);
}

//Convert the numbers to integer and remove all dots and hyphens
//Returns NULL if there's not enough numbers
int *normalize(char *cpf)
{
    int static normalized[11];
    int i;
    int j = 0;
    for(i = 0; i < strlen(cpf); ++i)
    {
        if(cpf[i] >= '0' && cpf[i] <= '9') //That means the current char is a number
        {
            normalized[j++] = cpf[i] - '0'; //By subtracting by '0' the value is converted from char to int
        }
    }
    //Returns the array if there are 11 numbers, else returns NULL
    if(j == 11)
    {
        return normalized;
    }
    return NULL;
}

int sumAll(int *cpf, int j)
{
    int i;
    int sum = 0;
    for(i = 0;j >= 2;i++)
    {
        sum += cpf[i] * j--;
        D(printf("i = %d\n",i))
        D(printf("cpf[%d] = %d\n",i,cpf[i]))
        D(printf("sum = %d\n",sum))
        D(printf("j = %d\n",j+1))
    }
    return sum;
}

bool isValid(int *cpf)
{
    int i = 0;
    D(printf("Verificando se todos os digitos sao iguais\n"))
    for(i = 1;i < 11;i++)
    {
        D(printf("Verificando de %d eh igual a %d\n",cpf[i-1],cpf[i]))
        if(cpf[i-1] != cpf[i]) //If any digit is different from another one that means they're not all the same
        {
            break;
        }
    }
    if(i == 11)
    {
        return false;
    }
    D(printf("Validando o primeiro digito\n"))
    int sum = sumAll(cpf,10);
    int module = (sum * 10) % 11;
    if((module) == 10)
        module = 0;
    D(printf("O resto da divisao eh %d\n",module))
    if(cpf[9] != module)
    {
        return false;
    }

    D(printf("Validando o segundo digito\n"))
    sum = sumAll(cpf,11);
    module = (sum * 10) % 11;
    if((module) == 10)
        module = 0;
    D(printf("O resto da divisao eh %d\n",module))
    if(cpf[10] != module)
    {
        return false;
    }
    return true;
}

int main()
{
    bool valid = false;
    char cpf[20];
    fgets(cpf,20,stdin); //Using fgets instead of gets to avoid buffer overflow

    if(validSize(cpf))
    {
        int *i_cpf = normalize(cpf);
        if(i_cpf != NULL)
        {
            valid = isValid(i_cpf);
        }
    }

    if(valid)
    {
        printf("O CPF digitado eh valido!\n");
    }
    else
    {
        printf("O CPF digitado eh invalido\n");
    }
}
