#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infija_a_postfija.h"

void inAPost(char *infija, char *postfija)
{
    int i, tam, j=-1;
    Ptrpila pila=NULL;
    char op;
    tam = strlen(infija);
    for(i=0;i<tam;i++)
    {
        if(infija[i]=='-'&& !i)
        {
            postfija[++j] = infija[i];
            continue;
        }
        if(infija[i]=='(')  //si abre parentesis se lo coloca si o si en la pila
        {
            push(&pila,infija[i]);
            if(infija[i+1]=='-')
                postfija[++j] = infija[++i];
        }
        else if(infija[i]=='+'||infija[i]=='-'||infija[i]=='*'||infija[i]=='/')
        {
            if(!pila || InfijaMayorAPila(infija[i],pila->oper) >= 0)   //si el operador infija tiene mayor o igual procedencia que el de pila
            {
                push(&pila,infija[i]);                                 //se lo mete a la pila
                postfija[++j] = ' ';
            }
            else if(InfijaMayorAPila(infija[i],pila->oper) < 0) //si operador de infija tiene menor procedencia que el de pila
            {
                do                              //se pasan todos los operadores de la pila, mientras que tengan mayor procedencia o se vacie la pila,
                {                               //a la cadena "postfija"
                    op = pop(&pila);
                    postfija[++j] = ' ';
                    postfija[++j] = op;
                }while(pila && InfijaMayorAPila(infija[i],pila->oper) < 0);
                postfija[++j] = ' ';
                push(&pila,infija[i]);
            }

        }
        else if(infija[i]==')')
        {
            while(pila->oper != '(')//Coloca en "postfija" todas las operaciones que estaban dentro del parentesis
            {
                op = pop(&pila);
                postfija[++j] = ' '; //Le agrego un espacio para que no esten todos los operadores juntos
                postfija[++j] = op;
            }
            pop(&pila);//quita el parentesis "(" que quedaba en la pila
        }
        else if(infija[i]==' ')
            continue;
        else //Todo lo que no sean operadores pasan directo a la cadena "postfija" (numeros, puntos y espacios)
        {
            postfija[++j] = infija[i];
        }
        //fin del for
    }
    while(pila!=NULL)//si quedan operadores en la pila, las pasa a la cadena "postfija"
    {
        op = pop(&pila);
        postfija[++j] = ' ';
        postfija[++j] = op;
    }
}

/*                 Apilar
-------------------------------------------------*/
void push(Ptrpila *pila,char c)
{
    Ptrpila nuevo = (Ptrpila) malloc(sizeof(Nodo));

    if(nuevo)
    {
        nuevo->oper = c;
        nuevo->sgte = NULL;
        if(!pila)
            *pila=nuevo;
        else
        {
            nuevo->sgte = *pila;
            *pila = nuevo;
        }
    }
    else
        printf("ERROR! Memoria insuficiente\n");
}

/*                 Desempilar
-------------------------------------------------*/
char pop(Ptrpila *pila)
{
    char op;
    Ptrpila aux;

    op = (*pila)->oper;
    aux = *pila;
    *pila = (*pila)->sgte;
    free(aux);
    return op;

}


/*                 Destruir Pila
--------------------------------------------------*/
void destruir(Ptrpila *pila)
{
    Ptrpila aux;
    aux = *pila;

    while(aux!=NULL)
    {
        *pila = (*pila)->sgte;
        free(aux);
        aux = *pila;
    }
}

int InfijaMayorAPila(char inf, char pil)
{
    int infijo=0, pila=0;

    if( inf=='*')
        infijo = 4;
    else if( inf=='/')
        infijo = 3;
    else if( inf=='+')
        infijo = 2;
    else if( inf=='-')
        infijo = 1;

    if( pil=='*')
        pila = 4;
    else if( pil=='/')
        pila = 3;
    else if( pil=='+')
        pila = 1;
    else if( pil=='-')
        pila = 2;
    else if( inf=='(')
        infijo = 0;

    return (infijo-pila);
}


/*                Balanceo de simbolos de agrupacion
---------------------------------------------------------------------*/
int correcto(char *array)
{
    Ptrpila pila=NULL;
    int i = 0, ret = 0 , tam;

    tam = strlen(array);
    while( i < tam )
    {
        if( array[i]=='(')
        {
            push( &pila, array[i] );
        }
        else if( array[i]==')')
        {

            if(pila!=NULL)
            {
                if( pila->oper == '(')
                       pop(&pila);
                   else
                       break;
            }
            else
                break;
        }

        i++;
    }

    if(!pila && i==tam)
        ret = 1;
    else if(pila)
        destruir(&pila);
    return ret;
}
