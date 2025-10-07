#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struct com o nome do territorio, a cor das tropas e a quantidade de tropas
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;


} territorio;




//Função pra definir a quantidade de territorios e o valor de cada variavel.
void quantTerritorios(territorio *mapa, int quantTerr)
{
    int i;
    for(i=0; i<quantTerr; i++)
    {
        printf("Tropa %d\n",i+1);
        printf("Nome: ");
        fgets(mapa[i].nome, 30,stdin);
        mapa[i].nome[strcspn(mapa[i].nome,"\n")]='\0';

        printf("Cor: ");
        fgets(mapa[i].cor,10,stdin);
        mapa[i].cor[strcspn(mapa[i].cor,"\n")]='\0';

        printf("Quantidade de tropas: ");
        scanf("%d",&mapa[i].tropas);
        getchar();
        printf("\n-------------------------\n");

    }
}
//Função pra exibir os territorios
void exibir(territorio *mapa, int quantTerr)
{
    int i;
    for(i=0; i<quantTerr; i++)
    {

        printf("Territorio %d ",i+1);
        printf("Nome: %s -> (Cor: %s tropas: %d)\n",mapa[i].nome, mapa[i].cor, mapa[i].tropas);


    }

}

//Função pra definir o numero de ataque e defesa
void atacar(territorio *atacante, territorio *defensor )
{
    //randomizando os numeros de ataque e defesa
    int dadoAtk, dadoDef;

    dadoAtk=(rand()%6)+1;
    dadoDef=(rand()%6)+1;

    //Definindo o dado de ataque ou defesa pra 0 caso tropas seja menor que 0

    if(atacante->tropas<=0){
        dadoAtk=0;
        atacante->tropas=0;
    }
     if(defensor->tropas<=0){
        dadoDef=0;
        defensor->tropas=0;
    }

    printf("\n%s atacou com %d e %s defendeu com %d\n",atacante->nome, dadoAtk, defensor->nome,dadoDef);
    if (dadoAtk>dadoDef)
    {
        printf("\n%s Venceu agora o territorio do defensor e da cor %s\n",atacante->nome, atacante->cor);


        // Atualizando a cor e tropas do defensor e atacante
        strcpy(defensor->cor, atacante->cor);
        atacante->tropas = atacante->tropas + defensor->tropas / 2;
        defensor->tropas = defensor->tropas / 2;


    }
    else if(dadoAtk<dadoDef)
    {
        printf("%s Resistiu ao ataque, o territorio atacante perdeu 1 tropa\n\n",defensor->nome);
        atacante->tropas=atacante->tropas-1;
    }
    else
        printf("Os territorios empataram, ninguem perdeu nada\n");
}

// Função para liberar memória
void liberarMemoria(territorio *mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}


int main()
{
    //definindo a semente de random usando o time
    srand(time(NULL));
    int quantTerr;
    printf("Digite a quantidade de territorios que deseja\n");
    scanf("%d",&quantTerr);
    getchar();

    territorio *mapa = (territorio *) calloc(quantTerr, sizeof(territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória com calloc!\n");
        return 1;
    }
    quantTerritorios(mapa, quantTerr);
    int i;
    int opcao,vitoria;
    while(1)
    {
            //Finalizando a guerra e mostrando quem venceu
            vitoria=quantTerr;
            for(i=0;i<quantTerr;i++){
            if(strcmp (mapa[0].cor,mapa[i].cor)==0){
                vitoria--;
                if(vitoria==0){
                    printf("\n\nA guerra acabou, todos os territorios foram dominados\n");
                    printf("Todos os territorios sao da cor %s agora\n\n",mapa[0].cor);
                    printf("MAPA FINAL\n");
                    exibir(mapa,quantTerr);
                    break;
                }
             }
          }
        if(vitoria==0)
            break;
        exibir(mapa,quantTerr);
        //Escolhas pro usuario
        printf("\n====================A GUERRA INICOU====================\n");
        printf("\nEscolha a opcao que deseja\n");
        printf("1.Atacar\n");
        printf("2.Desistir\n");
        scanf("%d",&opcao);
        getchar();
        if (opcao==1)
        {


            int indiceAtk, indiceDef;
            while (1)
            {
                //Escolhendo qual territorio vai atacar e qual vai defende
                printf("\nEscolha o territorio que vai atacar e qual vai defender.\n");
                printf("Ataque: ");
                scanf(" %d",&indiceAtk);
                getchar();
                printf("Defesa: ");
                scanf(" %d",&indiceDef);
                getchar();
                //Verificando se o territorio existe
                if(indiceAtk>quantTerr || indiceDef>quantTerr)
                {
                    printf("\nEsse Territorio não existe\n");
                    continue;
                }
                //Verificando se o territorio atacante e defensor tem a mesma cor
                else if(strcmp(mapa[indiceAtk-1].cor, mapa[indiceDef-1].cor) == 0)
                {
                    printf("\nVocê não pode atacar um aliado\n");
                    continue;
                }
                else
                    atacar(&mapa[indiceAtk-1], &mapa[indiceDef-1]);
                break;


            }

        }

        else if(opcao==2)
            break;
        else{
            printf("Escolha uma opcao valida");
                continue;
            }
     }

    territorio *backupMapa = (territorio *)malloc(quantTerr * sizeof(territorio));
    if (backupMapa != NULL) {
        memcpy(backupMapa, mapa, quantTerr* sizeof(territorio));
        printf("\nBackup dos territorios criado usando malloc.\n");
        free(backupMapa);
    }
    //chamando a função liberarMemoria
    liberarMemoria(mapa);
    return 0;
}
