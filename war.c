// Bibliotecas
#include <stdio.h>
#include <string.h>

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
    int t = 0;
    struct Territorio Exercito[MAX_TERRITORIO];
    int total_territorio = 0;
    int opcao;

    // Exibe o titulo
    printf("\n===============================\n");
    printf("       Cadastro Territorial      \n");
    printf("=================================\n\n");
    printf("1 - Cadastrando Territorio...\n\n");
            
    do{//Cadastra NOME, EXERCITO, TROPAS
        if (total_territorio < MAX_TERRITORIO) {
            printf("\nNome do Territorio: ");
            fgets(Exercito[total_territorio].nome, TAM_NOME, stdin);

            printf("Cor do Exercito: ");
            fgets(Exercito[total_territorio].cor_exercito, TAM_COR, stdin);

            printf("Numero de tropas: ");
            scanf("%d", &Exercito[total_territorio].numero_tropas);

            // Remove o '\n' do final das strings
            Exercito[total_territorio].nome[strcspn(Exercito[total_territorio].nome, "\n")] = '\0';
            Exercito[total_territorio].cor_exercito[strcspn(Exercito[total_territorio].cor_exercito, "\n")] = '\0';
            limparBufferEntrada();

            //Territorio contabilizado e guardando +1 na variavel total_territorio que inicialmente e 0
            total_territorio ++;
        }

    //Vetor Exercito com [MAX_TERRITORIO] de parametro, atinge o valor 5
    } while (total_territorio < MAX_TERRITORIO);

    //Exibindo os territórios cadastrados
    printf("\n===============================\n");
    printf("     Mapa Mundo - Estado Atual   \n");
    printf("=================================\n\n");

    for (int i = 0; i < total_territorio; i++) {
        printf("TERRITORIO %d:\n", i + 1);//Mostrando do 1 ao 5 na frente de territorio
        printf("- Nome: %s\n", Exercito[i].nome);
        printf("- Dominado por: Exercito %s\n", Exercito[i].cor_exercito);
        printf("- Tropas: %d\n", Exercito[i].numero_tropas);
        printf("\n");
    }

    return 0;
}

