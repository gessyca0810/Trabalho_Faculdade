#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE *abre, *copia;
    char nome_arquivo[100], nome_copia[100], c;
    
  
    printf("Escreva o nome do arquivo que voce quer copiar \n");
    scanf("%s", nome_arquivo);
  
    abre = fopen(nome_arquivo, "r");
    if (abre == NULL)
    {
        printf("Esse arquivo '%s' nao existe\n", nome_arquivo);
        exit(0);
    }
  
    printf("Escreva o nome que voce quer dar para o arquivo copiado\n");
    scanf("%s", nome_copia);

  
    copia = fopen(nome_copia, "r");
    if(copia != NULL) {
        printf("Esse arquivo já existe, por favor escolha outro nome \n");
        exit(0);
    }
    else {
        copia = fopen(nome_copia, "w");
        // Read contents from file
        c = fgetc(abre);
        while (c != EOF)
        {

            fputc(c, copia);
            c = fgetc(abre);
        }

        printf("\nO arquivo foi copiado para %s", nome_copia);
        fclose(abre);
        fclose(copia);
    }

    return 0;
}