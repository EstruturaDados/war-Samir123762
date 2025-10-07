#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Criando struct com as variaveis nome, cor, tropas
typedef struct{
    char nome[30];
    char cor[10];
    int tropas;

}territorio;

int main()
{
    
    territorio territoriovet[5];//criando o vetor territoriovet com o struct territorio
    int i; //variavel para o for

    
    printf("\n========== Informe sobre as tropas dos territorios ==========\n\n");
    //for para conseguir dados sobre cada territorio
    for(i=0;i<5;i++){
        printf("\nTerritorio %d\n",i+1);
        printf("\nNome: ");
        fgets(territoriovet[i].nome,30,stdin);//informando valor de nome
        territoriovet[i].nome[strcspn(territoriovet[i].nome,"\n")]='\0';// Remove o '\n' que o fgets coloca no final
        printf("\nCor das tropas: ");
        fgets(territoriovet[i].cor,10,stdin);//informando valor de cor
        territoriovet[i].cor[strcspn(territoriovet[i].cor,"\n")]='\0';

        printf("\nQuantidade de tropas: ");
        scanf("%d",&territoriovet[i].tropas);//informando valor de tropas
        while (getchar() != '\n');//limpando o buffer do teclado, para evitar problemas com fgets
    }

    for(i=0;i<5;i++){
        printf("\n========== Territorio%d ==========\n",i+1);
        //Imprimindo o dados informados
        printf("Nome: %s\nCor: %s\nNumero de tropas: %d\n",territoriovet[i].nome, territoriovet[i].cor, territoriovet[i].tropas);
        printf("\n==================================\n");

    }
    return 0;
}
