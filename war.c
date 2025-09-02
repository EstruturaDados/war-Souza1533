/*
    Programa: WAR Estruturado
    Autor: Nicolas Henrique
    Descrição: Simulação de um jogo estilo WAR com cadastro de territórios,
    exibição do mapa, fase de ataque e sistema de missões.
*/

#include <stdio.h>   // Funções de entrada e saída (printf, scanf, etc.)
#include <string.h>  // Manipulação de strings (fgets, strcspn)
#include <stdlib.h>  // Funções de alocação dinâmica (malloc, calloc, free)
#include <time.h>    // Geração de números aleatórios com srand() e rand()


#define MAX_TERRITORIO 5  // Número máximo de territórios no jogo
#define TAM_NOME 30       // Tamanho máximo do nome do território
#define TAM_COR 10        // Tamanho máximo da cor do exército


struct Territorio {
    char nome[TAM_NOME];        // Nome do território
    char cor_exercito[TAM_COR]; // Cor do exército associado
    int numero_tropas;          // Quantidade de tropas no território
};


// Função para limpar o buffer de entrada
// Evita que caracteres indesejados fiquem no stdin após scanf
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Exibe o menu principal do jogo
void ExibirMenuPrincipal(){
    printf("\n=================================\n");
    printf("     WAR ESTRUTURADO  -MESTRE-\n");
    printf("=================================\n");
    printf("     Mapa Mundo | Estado Atual   \n");
    printf("=================================\n\n");
}

// Cadastra territórios no vetor apontado por exercito_ptr
// exercito_ptr -> ponteiro para o array de territórios
// total_territorio -> ponteiro para o número de territórios cadastrados
void CadastroTerritorial(struct Territorio *exercito_ptr, int *total_territorio) {
    printf("-------Cadastro Territorial-------\n");
    
    do{
    printf("\n> Cadastrando Territorio %d <\n", *total_territorio + 1);

    if (*total_territorio < MAX_TERRITORIO) {
        printf("\nNome do Territorio: ");
        fgets(exercito_ptr[*total_territorio].nome, TAM_NOME, stdin);

        printf("Cor do Exercito: ");
        fgets(exercito_ptr[*total_territorio].cor_exercito, TAM_COR, stdin);

        printf("Numero de tropas: ");
        scanf("%d", &exercito_ptr[*total_territorio].numero_tropas);
        limparBufferEntrada();

        // Remove o '\n' do final da string lida pelo fgets
        exercito_ptr[*total_territorio].nome[strcspn(exercito_ptr[*total_territorio].nome, "\n")] = '\0';
        exercito_ptr[*total_territorio].cor_exercito[strcspn(exercito_ptr[*total_territorio].cor_exercito, "\n")] = '\0';

        (*total_territorio)++; //prioriza o ponteiro, em seguida incrementa +1.
    }
    } while (*total_territorio < MAX_TERRITORIO);
}

void ExibirTerritorios(struct Territorio *exercito_ptr, int total_territorio){
    printf("\n=================Mapa Mundo================\n");
    //Percorendo todos os conteutdos do array total_territorio que no caso o maximo e 5.
    for (int i = 0; i < total_territorio; i++) {
        printf("%d. ", i + 1);//Mostrando do 1 ao 5 na frente de territorio
        printf("%s ", exercito_ptr[i].nome);
        printf("(Exercito %s, ", exercito_ptr[i].cor_exercito);
        printf("Tropas: %d)", exercito_ptr[i].numero_tropas);
        printf("\n");
    }
    printf("\n===========================================\n");
    
}

void FaseDeAtaque(struct Territorio *exercito_ptr, int total_territorio) {
    int opcao_attack = 0;
    int opcao_defender = 0;
    do {
        printf("\n--- Fase de Ataque ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", total_territorio);
        scanf("%d", &opcao_attack);

        if (opcao_attack == 0) {
            printf("\nSaindo da fase de ataque...\n");
            break;
        }

        printf("Escolha o territorio que vai se defender:\n");
        scanf("%d", &opcao_defender);

        //
        if (opcao_attack < 1 || opcao_attack > total_territorio ||
            opcao_defender < 1 || opcao_defender > total_territorio) {
            printf("\nOpção inválida! Tente novamente.\n");
            continue;
        }

        opcao_attack--;
        opcao_defender--;

        // Gera dois números aleatórios entre 1 e 6 (simulação de dado)
        int nmr_atq = (rand() % 6) + 1;
        int nmr_def = (rand() % 6) + 1;

        printf("\nO Atacante %s rolou um dado e tirou: %d", exercito_ptr[opcao_attack].nome, nmr_atq);
        printf("\nO Defensor %s rolou um dado e tirou: %d\n", exercito_ptr[opcao_defender].nome, nmr_def);

        exercito_ptr[opcao_defender].numero_tropas -= nmr_atq;
        exercito_ptr[opcao_attack].numero_tropas -= nmr_def;

        // Atualiza tropas após batalha, garantindo que não fiquem negativas
        if (exercito_ptr[opcao_defender].numero_tropas < 0)
            exercito_ptr[opcao_defender].numero_tropas = 0;

        if (exercito_ptr[opcao_attack].numero_tropas < 0)
            exercito_ptr[opcao_attack].numero_tropas = 0;

        if (nmr_atq > nmr_def) {//atacante
            if(nmr_def > 1){
                 printf("\nAtacante vence a batalha.\n");
                printf("Mesmo apos algumas baixas\n");
                printf("Tropas do exercito %s derrotadas com sucesso!\n\n", exercito_ptr[opcao_defender].cor_exercito);
                break;
            }
            printf("\nAtacante vence a batalha.\n");
            printf("Tropa do exercito %s derrotado com sucesso!\n", exercito_ptr[opcao_defender].cor_exercito);
        } else if (nmr_atq < nmr_def) {//defensor
            if(nmr_def == 1){
                printf("\nDerrota, exercito defensor derrotou sua tropa\n");
            }
            printf("\nDerrota, exercito defensor derrotou as %d tropas\n", nmr_def);
        } else {
            printf("\nEmpate '-'\n");
        }

        printf("\nApos o combate:\n");
        printf("%s agora tem %d tropas.\n", exercito_ptr[opcao_attack].nome, exercito_ptr[opcao_attack].numero_tropas);
        printf("%s agora tem %d tropas.\n", exercito_ptr[opcao_defender].nome, exercito_ptr[opcao_defender].numero_tropas);

        ExibirTerritorios(exercito_ptr, total_territorio);

    } while (0);
}

void ExibirMissao(struct Territorio *exercito_ptr){
    int opcao;
    int missao_minha;
    int missao_sua;

    do{
        missao_minha = (rand() % 5); 
        missao_sua = (rand() % 5); 
    } while(missao_minha == missao_sua);

    while(opcao != 3){
        
        printf("----- SUA MISSAO (Exercito %s) -----\n", exercito_ptr[missao_minha].cor_exercito);
        printf("Destruir o exercito %s\n\n", exercito_ptr[missao_sua].cor_exercito);
        printf("----- MENU DE ACOES -----\n");
        printf("1- Atacar\n");
        printf("2- Verificar Missao\n");
        printf("3- Sair\n\n");
        
        printf("-> "); scanf("%d", &opcao);

        if (opcao == 1) {
            FaseDeAtaque(exercito_ptr, MAX_TERRITORIO); 
        } else if (opcao == 2){//verifica qual tropa zera para poder atualizar o verificar missao
            if(exercito_ptr[missao_minha].numero_tropas <= 0 && exercito_ptr[missao_sua].numero_tropas <= 0){
                printf("-> Ambos exercitos perderam, game over.\n");
            }
            if(exercito_ptr[missao_minha].numero_tropas >= 1 && exercito_ptr[missao_sua].numero_tropas <= 0){
                    printf("Missao de Derrotar Exercito: Concluida!\n");
            } else if (exercito_ptr[missao_sua].numero_tropas >= 1 && exercito_ptr[missao_minha].numero_tropas <= 0){
                printf("-> Missao de Derrotar Exercito: Fracassada!\n");
            } else if (exercito_ptr[missao_minha].numero_tropas >= 1 && exercito_ptr[missao_sua].numero_tropas >= 1){
                 printf("-> Missao andamento...\n");
            }

        } else {
            break;
        }

    }

}


//Funçao principal
int main(){
    srand(time(NULL));// Inicializa gerador de números aleatórios
    struct Territorio *exercito_ptr;
    
    // Aloca memória para os territórios
    exercito_ptr = (struct Territorio*) calloc(MAX_TERRITORIO, sizeof(struct Territorio));

    if(exercito_ptr == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    int total_territorio = 0;

    ExibirMenuPrincipal();// Exibe o menu inicial do jogo
    CadastroTerritorial(exercito_ptr, &total_territorio);// Cadastra os territórios
    ExibirTerritorios(exercito_ptr, total_territorio);// Mostra o mapa atual
    ExibirMissao(exercito_ptr);// Inicia a fase de missões
    
    free(exercito_ptr);// Libera a memória alocada
    return 0;
}

   