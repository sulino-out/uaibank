#include "operations.h"

// DEFINE O TAMANHO MÁXIMO DOS NOMES

const int NAME_MAX_SIZE = 101;

// DEFINIÇÃO DE TIPOS DE DADOS

typedef struct // Define uma struct para armazenar todos os dados de um usuário
{
    char* name;
    int age;
    double currency;
}
users;

// OUTRAS FUNÇÕES

int add_id() // Função que adiciona um novo id contando o número de quebra de linhas no arquivo database.txt -- PRONTA
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

int verify_id(int id) // Função que verifica se um ID existe
{
    // Se o ID existe, retorna 1

    // Se o ID não existe, retorna 0
}

char* user_name(int id) // Função que retorna o nome do usuário de determinado ID -- TODO
{

}

int user_age(int id) // Função que retorna a idade do usuário de determinado ID -- TODO
{

}

double user_currency(int id) // Função que retorna o saldo atual do usuário de determinado ID -- TODO
{

}

void print_operations() // Função que imprime na tela as operações que podem ser realizadas pelo usuário -- PRONTA
{
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Selecione uma operacao para realizar:\n");
    printf("0. Sair\n");
    printf("1. Novo usuario\n");
    printf("2. Novos usuarios\n");
    printf("3. Procurar usuario por ID\n");
    printf("4. Fazer transferencia entre usuarios\n");
    printf("5. Remover usuario por ID\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

int select_operation() // Função que seleciona a operação a ser realizada -- PRONTA
{
    int operation; // Cria uma variável para armazenar a operação

    // Pede ao usuário um valor entre 1 e 5 (operações válidas)
    while (1)
    {
        scanf("%d", &operation);

        if ((operation >= 1 && operation <= 5) || operation == 0) // Se o valor for válido, continua
        {
            break;
        }

        printf("Selecione uma opcao valida.\n"); // Se não, volta pro início do loop
    }

    return operation; // Retorna a variável para armazenar a operação
}

void run_operation(int operation) // Função que roda a operação selecionada -- PRONTA
{
    switch (operation)
    {
        case 1:
            new_user();
            break;
        case 2:
            new_users();
            break;
        case 3:
            search_id();
            break;
        case 4:
            // transfer_user();
            break;
        case 5:
            // remove_id();
            break;
    }

    return;
}

// OPERAÇÃO 1
void new_user() // Função que adiciona um novo usuário ao banco de dados -- PRONTA
{   
    int newUserId = add_id(); // Cria um novo ID para o usuário
    
    users user; // Cria uma variável para armazenar as informações do usuário
    user.name = malloc(sizeof(char) * NAME_MAX_SIZE); // Define o máximo de caractéres do nome sendo 100
    if(user.name == NULL)
    {
        printf("Sem espaco na memoria.\n");
        exit(1);
    }
    
    // Imprime para o usuário a operação que ele está realizando
    printf("\n");
    printf("=-=-=-=-=-=-=NOVO USUARIO=-=-=-=-=-=-\n");

    // Pede os dados para o usuário e as armazena nas respectivas variáveis do usuário
    printf("Nome: ");
    scanf("\n%[^\n]", user.name);
    printf("Idade: ");
    scanf("%d", &user.age);
    printf("Saldo atual: ");
    scanf("%lf", &user.currency);

    char* databaseName = "database.txt"; // Define o nome do arquivo da base de dados
    FILE* database = fopen(databaseName, "a"); // Abre a base de dados
    if(database == NULL)
    {
        printf("Nao foi possivel abrir %s", databaseName);
        exit(2);
    }

    fprintf(database, "%d '%s' %d %.2lf\n", newUserId, user.name, user.age, user.currency); // Escreve na base de dados os dados do usuários

    fclose(database); // Fecha a base de dados

    // Imprime que a operação foi um sucesso
    printf("=-=-=-=-=USUARIO %d REGISTADO-=-=-=-=-\n", newUserId);
    printf("\n");

    return;
}

// OPERAÇÃO 2
void new_users() // Função que adiciona vários usuários ao banco de dados -- PRONTA
{
    int numberOfUsers; // Cria uma variável para armzenar o número de usuários que serão adicionados
    
    // Imprime para o usuário a operação que ele está realizando
    printf("\n");
    printf("=-=-=-=-=-=-NOVOS USUARIOS-=-=-=-=-=-\n");

    // Pede ao usuário a quantidade de usuários que devem ser adicionados
    printf("Quantidade de usuarios: ");
    scanf("%d", &numberOfUsers);

    // Adiciona 'numberOfUsers' usuários novos
    for(int i = 0; i < numberOfUsers; i++)
    {
        new_user();
    }

    return;
}

// TODO: OPERAÇÃO 3
void search_id() // Função que imprime as informações do usuário a partir do seu ID -- TODO
{
    users user;
    int searchId;

    printf("\n");
    printf("=-=-=-=-=-=-PROCURA POR ID-=-=-=-=-=-\n");
    printf("ID: ");
    scanf("%d", &searchId);

/*     // Armazena o nome do usuário em user.name
    user.name = user_name(searchId); 

    // Armazena a idade do usuário em user.age
    user.age = user_age(searchId);

    // Armazena o saldo atual do usuário em user.currency
    user.currency = user_currency(searchId);

    // imprime as informações do usuário

    printf("Nome: %s\n", user.name);
    printf("Idade: %d\n", user.age);
    printf("Saldo atual: %lf\n", user.currency); */

    printf("=-=-=-=-=-OPERACAO REALIZADA-=-=-=-=-\n");
    printf("\n");

    return;
}

// TODO: OPERAÇÃO 4
void transfer_user() // Função que faz transferência entre usuários -- TODO
{

}

// TODO: OPERAÇÃO 5
void remove_id() // Função que remove um usuário pelo ID -- TODO
{

}
