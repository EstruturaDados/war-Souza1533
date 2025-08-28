// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Constantes Globais
#define MAX_TERRITORIO 5
#define TAM_NOME 30
#define TAM_COR 10

// Definição da estrutura
struct Territorio {
    char nome[TAM_NOME];
    char cor_exercito[TAM_COR];
    int numero_tropas;
};

// Função para limpar buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Funcao principal
int main(){
    struct Territorio *exercito_ptr;
    
    exercito_ptr = (struct Territorio*) calloc(MAX_TERRITORIO, sizeof(struct Territorio));

    if(exercito_ptr == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    int t = 0;
    int total_territorio = 0;
    int opcao;
    int contagem = 1;

    // Exibe o titulo
    printf("\n===============================\n");
    printf("       Cadastro Territorial      \n");
    printf("=================================\n");
            
    do{//Cadastra NOME, EXERCITO, TROPAS
        printf("\n--- Cadastrando Territorio %d ---\n", contagem);
        if (total_territorio < MAX_TERRITORIO) {
            printf("\nNome do Territorio: ");
            fgets(exercito_ptr[total_territorio].nome, TAM_NOME, stdin);

            printf("Cor do Exercito: ");
            fgets(exercito_ptr[total_territorio].cor_exercito, TAM_COR, stdin);

            printf("Numero de tropas: ");
            scanf("%d", &exercito_ptr[total_territorio].numero_tropas);

            // Remove o '\n' do final das strings
            exercito_ptr[total_territorio].nome[strcspn(exercito_ptr[total_territorio].nome, "\n")] = '\0';
            exercito_ptr[total_territorio].cor_exercito[strcspn(exercito_ptr[total_territorio].cor_exercito, "\n")] = '\0';
            limparBufferEntrada();

            //Territorio contabilizado e guardando +1 na variavel total_territorio que inicialmente e 0
            total_territorio ++;
            contagem++;
        }

    //Vetor Exercito com [MAX_TERRITORIO] de parametro, atinge o valor 5
    } while (total_territorio < MAX_TERRITORIO);

    //Exibindo os territórios cadastrados
    printf("\n=================================\n");
    printf("     Mapa Mundo - Estado Atual   \n");
    printf("=================================\n\n");

    //Percorendo todos os conteutdos do array total_territorio que no caso o maximo e 5.
    for (int i = 0; i < total_territorio; i++) {
        printf("%d. ", i + 1);//Mostrando do 1 ao 5 na frente de territorio
        printf("%s ", exercito_ptr[i].nome);
        printf("(Exercito %s, ", exercito_ptr[i].cor_exercito);
        printf("Tropas: %d)", exercito_ptr[i].numero_tropas);
        printf("\n");
    }
    
    //Coleta de Dados para Ataque
    int opcao_attack = 0;
    int opcao_defender = 0;

    do{
    printf("\n--- Fase de Ataque ---\n");
        printf("Escolha o territorio atacante (1 a 5, ou 0 para sair)\n");
        scanf("%d", &opcao_attack);
        
        if (opcao_attack == 0) {
            printf("\nSaindo da fase de ataque...\n");
            break; // sai do loop
        }

        printf("Escolha o territorio que vai se defender:\n");
        scanf("%d", &opcao_defender);

        //checa se digitou opcao valida
        if (opcao_attack < 1 || opcao_attack > 5 || opcao_defender < 1 || opcao_defender > 5) {
            printf("\nOpção inválida! Tente novamente.\n");
            continue;
        }

        // Ajuste para índices do array
        opcao_attack--;
        opcao_defender--;

        // Gerando números aleatórios entre 1 e 6, como um dado
        srand(time(NULL));
        int nmr_atq = (rand() % 6) + 1; 
        int nmr_def = (rand() % 6) + 1;


        //Resultado Ataque
        printf("\nO Atacante %s rolou um dado e tirou: %d", exercito_ptr[opcao_attack].nome, nmr_atq);
        printf("\nO Defensor %s rolou um dado e tirou: %d\n", exercito_ptr[opcao_defender].nome, nmr_def);

        if (nmr_atq > nmr_def) {
            printf("\nAtacante Venceu!!\n");
        } else if (nmr_atq < nmr_def) {
            printf("\nDefensor Venceu!!\n");
        } else {
            printf("\nEmpate '-'\n");
        }

    } while(1);
        
    free(exercito_ptr);
    return 0;
}