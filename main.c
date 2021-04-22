#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct IMPLICA
{
    char expressao[1000];
    char negativos[100];
    char positivos[100];
}IMPLICA;

/*ASCII -> A to Z: 65 a 90
        -> a to z: 97 a 122*/
/*(~m | ~R | ~T | ~K | ~C | ~c | c) & (V)
TOP = + 
BOT = - */
void separarExpressaoGrande(char * expressao, IMPLICA A[][150],int * numeroExp)
{
    //printf("Entrou no for\n");
    for(int i = 0;i < strlen(expressao);i++)
    {
        if(expressao[i] == '(')
        {
            (*numeroExp)++;
        }else
        {
            strncat((*A)[(*numeroExp)-1].expressao,&expressao[i],1);
        }
    }
}

IMPLICA separarExpressaoInicial(char * expressao)
{
    int i,u;
    IMPLICA A;
    strcpy(A.negativos,"");
    strcpy(A.positivos,"");
    bool temNegativo=false;
    bool temPositivo=false;
    for(i = 0;i < strlen(expressao);i++)
    {
        if(expressao[i] == '~')
        {
            for(u=0;u < strlen(A.negativos);u++)
            {  
                if(A.negativos[u]==expressao[i+1])
                    temNegativo=true;
            }
            if(temNegativo == false)
            {
                //A.negativos += expressao[i+1];
                strncat(A.negativos,&expressao[i+1],1);
            }
                
            i++;
            temNegativo=false;
            continue;
        }else if((expressao[i]>= 65 && expressao[i] <=90) || (expressao[i]>= 97 && expressao[i] <=122))
        {
            for(u=0;u < strlen(A.positivos);u++)
            {
                if(A.positivos[u]==expressao[i])
                    temPositivo=true;
            }
            if(temPositivo==false)
            {
                //A.positivos += expressao[i];
                strncat(A.positivos,&expressao[i],1);
            }
               temPositivo=false; 
        }
    }
    return A;
}
int main(void)
{
    char buffer[60000];
    IMPLICA Arr[150];
    int numeroExp=0; 
    IMPLICA A;
    while(fgets(buffer,60000,stdin))
    {
        separarExpressaoGrande(buffer,&Arr,&numeroExp);
        /*for(int i = 0;i < numeroExp;i++)
        {
            printf("Expressão: %d\n",i+1);
            A = separarExpressaoInicial(Arr[i].expressao);
            for(size_t i =0;i < strlen(A.negativos);i++)
            {
                printf(" %c ",A.negativos[i]);
            }

            printf("\n");
            for(size_t i =0;i < strlen(A.positivos);i++)
            {
                printf(" %c ",A.positivos[i]);
            }
            printf("\n");
        }*/
    }
    
    return 0;
}