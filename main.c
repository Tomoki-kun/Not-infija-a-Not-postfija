//(16 + 1.5 * (7 - 2))/ 2 + 4
//Notacion postfija: 16 1.5 7 2 - * + 2 / 4 +
//15,75

//2 * (3.14 + 4.0 * (43.1 – 9.8) – 52.3 /(3.09 + 7.32))
//Notacion postfija:
//2  3.14  4.0  43.1  9.8 -  * + 52.3 3.09  7.32 + / - *
//262.63

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infija_a_postfija.h"
#include "solve.h"


/*                 Funcion Principal
-----------------------------------------------------*/
int main(void)
{
    float resultado;
    char infija[max], postfija[max] = "\0";

    system("color 0a");

    printf("\nConversion de expresiones matematicas de INFIJA a POSTFIJA\n\n");
    printf("-------------------------------------------------------------\n\n");
    printf("\tIngrese expresion: (EJ: '(16+1.5*(7-2))/2+4' )\n--> ");
    scanf("%99[^\n]s", infija);
    fflush(stdin);

    if(correcto(infija))
    {
        inAPost(infija,postfija);
        printf("\n\tNotacion postfija:\n");
        printf("--> %s\n\n",postfija);        //imprime la cadena "postfija"
        resultado = resulPostfija(postfija);
        printf("\tEL resultado es:\n--> %.2f\n\n", resultado);
    }
    else
    {
        printf("\n-->ERROR DE SINTAXIS\n\n");
    }

    return 0;
}

