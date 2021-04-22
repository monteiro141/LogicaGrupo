#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct IMPLICA
{
    char expressao[1000];
    char negativos[100];
    char positivos[100];
    int verificado;
}IMPLICA;

/*ASCII -> A to Z: 65 a 90
        -> a to z: 97 a 122*/
/*(~m | ~R | ~T | ~K | ~C | ~c | c) & (V)
TOP = + 
BOT = - */
void separarExpressaoGrande(char * expressao, IMPLICA A[][300],int * numeroExp)
{
    //printf("Entrou no for\n");~
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

int contarLiteralPositivo(char * expressao)
{
    if(strlen(expressao) >=2)
        return -1;
    return 1;
}

void adicionarAoGrupo(char  grupo[][300], char * positivos)// +,Q,P     P       Q
{
    int i,u;
    bool existe=false;
    for(i=0;i<strlen(positivos);i++)
    {
        for(u=0;u<strlen(*grupo);u++)
        {
            if((*grupo)[u] == positivos[i])
                existe=true;
        }
        if(existe==false)
        {
            strncat((*grupo),&positivos[i],1);
            existe=false;
        }
    }
}
//M e Q -> P    Grupo: +, M, Q   entao adiciona P
//A e B -> C    Grupo: +, A    então não faz nada porque B não está no grupo
int compararGrupo(char  grupo[][300],char * negativos,char * positivos)//  +,Q,P     P Q R -> A
{
    bool existe=false;
    int i,u;
    for(i=0;i<strlen(negativos);i++)
    {
        for(u=0;u<strlen(*grupo);u++)
        {
            if((*grupo)[u] == negativos[i])
                existe=true;
        }
        if(existe==true)
        {
            existe=false;
            continue;
        }else
        {
            return -1;
        }
    }
    adicionarAoGrupo(grupo,positivos);
    return 1;
}

int verBottom(char  grupo[][300],char * negativos)// +,p,q ... q p  -> -
{
    bool existe=false;
    int i,u;
    for(i=0;i<strlen(negativos);i++)
    {
        existe=false;
        for(u=0;u<strlen(*grupo);u++)
        {
            //printf("grupo: %c vs %c neg\n",(grupo)[u],negativos[i]);
            if((*grupo)[u] == negativos[i])
            {
                
                existe=true;
            }
        }
        if(!existe)
        {
            //printf("-1\n");
            return -1;
        }
    }
    //printf("Um\n");
    return 1;
}

void satOrUnsat(IMPLICA * A, char  grupo[][300],int numeroExpressoes,bool * temBot) //grupo = "+"
{
    int i;
    for(i=0;i<numeroExpressoes;i++)//Tratar os negativos
    {
        if(A[i].verificado == 0)
        {
            if(strlen(A[i].negativos)==0)
            {
                adicionarAoGrupo(grupo,A[i].positivos);
                A[i].verificado=1;
                i=-1;
            }else if(strlen(A[i].positivos)==0)
            {
                    if(verBottom(grupo,A[i].negativos)==1)//1 -> pode adicionar bottom, -1-> nao adicionou
                    {
                        (*temBot)=true;
                        return;
                    }
            }else
            {
                if(compararGrupo(grupo,A[i].negativos,A[i].positivos) == 1)
                {
                    A[i].verificado=1;
                    i=-1;
                }else
                {
                    continue;
                }
            }
        }else
        {
            continue;
        }
    }
}

int main(void)
{
    char buffer[60000];
    IMPLICA Arr[300];
    int numeroExp=0,i; 
    IMPLICA ArrFinal[300];
    IMPLICA Decoy;
    strcpy(Decoy.expressao,"");
    strcpy(Decoy.negativos,"");
    strcpy(Decoy.positivos,"");
    Decoy.verificado=0;
    char grupo[300];
    bool NA=false,temBot=false;

    while(fgets(buffer,60000,stdin))
    {
        for(i=0;i < 300;i++)
        {
            Arr[i] = Decoy;
            ArrFinal[i] = Decoy;
        }
        NA=false;
        temBot=false;
        strcpy(grupo,"+");
        numeroExp=0;
        separarExpressaoGrande(buffer,&Arr,&numeroExp);
        for(i = 0;i < numeroExp;i++)
        {
            //printf("Expressão: %d\n",i+1);
            ArrFinal[i] = separarExpressaoInicial(Arr[i].expressao);
            ArrFinal[i].verificado=0;
            if(contarLiteralPositivo(ArrFinal[i].positivos)==-1)
            {
                NA=true;
            }
                
        }
        if(NA)
            printf("NA\n");
        else
        {
            satOrUnsat(ArrFinal,&grupo,numeroExp,&temBot);
            if(temBot==false)
            {
                printf("SAT\n");
            }else
                printf("UNSAT\n");
        }
    }
    
    return 0;
}