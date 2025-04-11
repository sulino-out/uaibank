#include "operations.h"

// DEFINIÇÃO DE TIPOS DE DADOS

typedef uint8_t BYTE; // Define um tipo de dado que possui tamanho de 1-byte
typedef char* string; // Define o tipo de dado string
typedef struct // Define uma struct para armazenar todos os dados de um usuário
{
    string name;
    int age;
    double currency;
}
user;

// OUTRAS FUNÇÕES

int add_id() // Função que adiciona um novo id contando o número de quebra de linhas no arquivo database.txt -- PRONTA (TALVEZ HAJA NECESSIDADE DE ALTERAÇÃO)
{
    int lastId = 1; // Seleciona, a principio, o ultimo id como sendo 1

    // Abre o arquivo database.txt no modo de leitura
    FILE *newId = fopen("database.txt", "r");
    if (newId == NULL) // Checa se o arquivo abriu corretamente, caso contrário, para o programa
    {
        printf("Nao foi possivel abrir o arquivo database.txt.\n");
        exit(1);
    }

    // Procura, carácter por carácter no arquivo de texto, por quebras de linhas
    char fileChar;
    while ((fileChar = fgetc(newId)) != EOF)
    {
        if (fileChar == '\n')
        {
            lastId++; // Para cada quebra de linha que existe no texto, aumenta o ulitmo id em 1
        }
    }

    fclose(newId); // Fecha o arquivo para desocupar espaço na memória

    return lastId; // Retorna o valor do novo id
}

int select_operation(void) // Função que seleciona a operação a ser realizada -- PRONTA
{
    int operation; // Cria uma variável para armazenar a operação

    // Pede ao usuário um valor entre 1 e 5 (operações válidas)
    while (1)
    {
        scanf("%d", &operation);

        if ((operation >= 1 && operation <= 5) || operation == 0)
        {
            break;
        }

        printf("Selecione uma opcao valida.\n");
    }

    return operation; // Retorna a variável para armazenar a operação
}

void run_operation(int operation) // Função que roda a operação selecionada -- PRONTA
{
    switch (operation)
    {
        case 1:
            // new_user()
            break;
        case 2:
            // new_users()
            break;
        case 3:
            // search_id()
            break;
        case 4:
            // transfer_user()
            break;
        case 5:
            // remove_id()
            break;
    }

    return;
}

// TODO: OPERAÇÃO 1
void new_user()  // Compensa Por verificação de quantos usuários tem antes?(M) - Sugestão
{   
    char nome[0];
    int idade;
    float saldo_atual;

    // Cria novo id.... (M)

}

// TODO: OPERAÇÃO 2
void new_users()
{
    char nome[0];
    int idade;
    float saldo_atual;
}

// TODO: OPERAÇÃO 3
void search_id()
{

}

// TODO: OPERAÇÃO 4
void transfer_user()
{

}

// TODO: OPERAÇÃO 5
void remove_id()
{

}
