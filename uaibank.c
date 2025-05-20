// INCLUSÃO DE BIBLIOTECAS

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// DEFINE O TAMANHO MÁXIMO DOS NOMES

const int NAME_MAX_SIZE = 101;
const int MAX_USERS = 1000;

// DEFINIÇÃO DE TIPOS DE DADOS

typedef struct // Define uma struct para armazenar todos os dados de um usuário
{
    int id;
    char* name;
    int age;
    double currency;
}
users;

// PROTÓTIPOS DE FUNÇÕES

int add_id();
int verify_id(int id);
void load_users(users* user_array, int numUsers);
void print_in_database(users* user_array, int numUsers);
void print_operations();
int select_operation();
void run_operation(int operation);
void new_user();
void new_users();
void search_id();
void transfer_user();
void remove_id();

// FUNÇÃO MAIN

int main(void)
{
    int operation; // Cria uma variavel pra armazenar a operação a ser feita

    while (1)
    {
        print_operations(); // Imprime as operações disponíveis

        operation = select_operation(); // Armazena em uma variável a operação a ser realizada
        if (operation == 0) // Define como 0 o valor de saída do programa
        {
            break;
        }
    
        run_operation(operation); // Roda a operação selecionada
    }

    return 0;
}

// OUTRAS FUNÇÕES

int add_id() // Função que adiciona um novo id contando o número de quebra de linhas no arquivo database.txt
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

int verify_id(int id) // Função que verifica se um ID existe; Retorna 0 para FALSO e retorna 1 para VERDADEIRO
{
    // Cria as variáveis que serão utilizadas
    int lastId = add_id() - 1;
    users* user = malloc(sizeof(users) * lastId); // Array de usuários
    char* removedUser = "removed_user";

    load_users(user, lastId); // Carrega, na array de usuários, todos os usuários do banco de dados

    if(id <= lastId) // Procura entre os IDS que são menores que o maior ID que existe
    {
        if(strcmp(user[id - 1].name, removedUser) == 0) // Se o ID for de um usuário removido
        {
            free(user); // Libera o espaço alocado para a array de usuários

            return 0; // Retorna FALSO
        }
        else // Se o usuário existir
        {
            free(user); // Libera o espaço alocado para a array de usuários

            return 1; // Retorna VERDADEIRO
        }
    }
    free(user); // Libera o espaço alocado para a array de usuários

    return 0; // Se o ID buscado for maior que o maior ID que existe, retorna FALSO
}

void load_users(users* user_array, int numUsers) // Função que carrega os usuários em uma matriz
{
    // Abre o arquivo no modo leitura
    char* filename = "database.txt";
    FILE* database = fopen(filename, "r");

    // Scaneia os dados do arquivo e armazena na array de usuários
    for(int i = 0; i < numUsers; i++)
    {
        user_array[i].name = malloc(sizeof(char) * NAME_MAX_SIZE);
        fscanf(database, "%d %99[^']%*c %d %lf", &user_array[i].id, user_array[i].name, &user_array[i].age, &user_array[i].currency);
    }

    fclose(database); // Fecha o arquivo

    return; // Retorna
}

void print_in_database(users* user_array, int numUsers) // Função que escreve os novos dados da matriz no banco de dados
{
    // Abre o arquivo no modo de escrita
    char* filename = "database.txt";
    FILE* database = fopen(filename, "w");

    // Imprime as informações da array de usuários no banco de dados
    for(int i = 0; i < numUsers; i++)
    {
        fprintf(database, "%d %s' %d %.2lf\n", user_array[i].id, user_array[i].name, user_array[i].age, user_array[i].currency);
    }

    fclose(database); // Fecha o arquivo

    return; // Retorna
}

void print_operations() // Função que imprime na tela as operações que podem ser realizadas pelo usuário
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

int select_operation() // Função que seleciona a operação a ser realizada
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

void run_operation(int operation) // Função que roda a operação selecionada
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
            transfer_user();
            break;
        case 5:
            remove_id();
            break;
    }

    return; // Retorna
}

// OPERAÇÃO 1
void new_user() // Função que adiciona um novo usuário ao banco de dados
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

    printf("0. Voltar\n"); // Imprime pro usuário a opção de voltar

    // Pede os dados para o usuário e as armazena nas respectivas variáveis do usuário
    printf("Nome: ");
    scanf("\n%[^\n]", user.name);
    if(user.name[0] == '0') // Se for digitado 0, volta para o menu inicial
    {
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    printf("Idade: ");
    scanf("%d", &user.age);
    while(user.age < 0) // Verifica se a idade é positiva
    {
        printf("Erro: A idade nao pode ser negativa.\n");
        printf("Idade: ");
        scanf("%d", &user.age);
    }

    printf("Saldo atual: ");
    scanf("%lf", &user.currency);
    while(user.currency < 0) // Verifica se o saldo é positivo
    {
        printf("Erro: O saldo nao pode ser negativo.\n");
        printf("Saldo atual: ");
        scanf("%lf", &user.currency);
    }

    char* databaseName = "database.txt"; // Define o nome do arquivo da base de dados
    FILE* database = fopen(databaseName, "a"); // Abre a base de dados
    if(database == NULL)
    {
        printf("Nao foi possivel abrir %s", databaseName);
        exit(2);
    }

    fprintf(database, "%d %s' %d %.2lf\n", newUserId, user.name, user.age, user.currency); // Escreve na base de dados os dados do usuários

    // Imprime que a operação foi um sucesso
    printf("=-=-=-=-=USUARIO %d REGISTADO-=-=-=-=-\n", newUserId);
    printf("\n");

    fclose(database); // Fecha a base de dados
    
    return; // Retorna
}

// OPERAÇÃO 2
void new_users() // Função que adiciona vários usuários ao banco de dados
{
    int numberOfUsers; // Cria uma variável para armzenar o número de usuários que serão adicionados
    
    // Imprime para o usuário a operação que ele está realizando
    printf("\n");
    printf("=-=-=-=-=-=-NOVOS USUARIOS-=-=-=-=-=-\n");

    printf("0. Voltar\n"); // Imprime pro usuário a opção de voltar

    // Pede ao usuário a quantidade de usuários que devem ser adicionados
    printf("Quantidade de usuarios: ");
    scanf("%d", &numberOfUsers);
    while(numberOfUsers < 0) // Verifica se o número de usuários é um valor positivo
    {
        printf("Erro: Selecione um valor positivo.\n");
        printf("Quantidade de usuarios: ");
        scanf("%d", &numberOfUsers);
    }
    if(numberOfUsers == 0) // Se for digitado 0, volta para o menu inicial
    {
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    // Adiciona 'numberOfUsers' usuários novos
    for(int i = 0; i < numberOfUsers; i++)
    {
        new_user();
    }

    return; // Retorna
}

// OPERAÇÃO 3
void search_id() // Função que imprime as informações do usuário a partir do seu ID
{
    // Cria as variáveis que serão utilizadas
    const int LINES = add_id() - 1;
    users* user = malloc(sizeof(users) * LINES); // Array de usuários
    int id;

    // Carrega na array de usuários as informações do banco de dados
    load_users(user, LINES);

    // Imprime para o usuário a operação que está sendo realizada
    printf("\n");
    printf("=-=-=-=-=-=-PROCURA POR ID-=-=-=-=-=-\n");

    // Verifica se existem usuários já cadastrados
    if(LINES == 0)
    {
        printf("Nao existem usuarios cadastrados.\n");
        printf("=-=-=-=-=-OPERACAO REALIZADA-=-=-=-=-\n");
        printf("\n");
        return;
    }

    printf("0. Voltar\n"); // Imprime a opção de voltar

    // Pede ao usuário pelo ID
    printf("ID: ");
    scanf("%d", &id);

    // Volta se a opção de voltar tiver sido selecionada
    if(id == 0)
    {
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    // Verifica se o ID selecionado existe
    while(verify_id(id) == 0)
    {
        printf("Erro: Nao existe usuario com esse ID.\n");
        printf("ID: ");
        scanf("%d", &id);
    }

    // imprime as informações do usuário
    printf("Nome: %s\n", user[id - 1].name);
    printf("Idade: %d\n", user[id - 1].age);
    printf("Saldo atual: %.2lf\n", user[id - 1].currency);

    // Imprime que a operação foi realizada com sucesso
    printf("=-=-=-=-=-OPERACAO REALIZADA-=-=-=-=-\n");
    printf("\n");

    free(user); // Libera a memória alocada para a array de usuários

    return; // Retorna
}

// OPERAÇÃO 4
void transfer_user() // Função que faz transferência entre usuários
{
    // Define as variáveis que são utilizadas
    const int LINES = add_id() - 1;
	users* user = malloc(sizeof(users) * LINES); // Array de usuários
    double value;
    int originId, destinationId;

    // Carrega os usuários que existem no banco de dados
    load_users(user, LINES);
    
    // Imprime para o usuário o cabeçalho
    printf("\n");
    printf("=-=-TRANSFERENCIA ENTRE USUARIOS-=-=-\n");

    // Verifica se há pelo menos 2 usuários
    if(LINES < 2)
    {
        printf("Nao existem usuarios suficientes.\n");
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    printf("0. Voltar\n"); // Imprime a opção de voltar
    
    // Pede pelo ID do usuário que fará a transferência
    printf("ID de origem: ");
    scanf("%d", &originId);

    // Volta se a opção de voltar tiver sido selecionada
    if(originId == 0)
    {
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    // Verifica se o ID selecionado existe
    while(verify_id(originId) == 0)
    {
        printf("Erro: O ID não existe.\n");
        printf("ID de origem: ");
        scanf("%d", &originId);
    }

    printf("Usuario '%s' selecionado.\n", user[originId - 1].name); // Imprime qual é o usuário do ID de origem
    
    // Pede pelo ID do usuário que receberá a transferência
    printf("ID de destino: ");
    scanf("%d", &destinationId);

    // Volta se a opção de voltar tiver sido selecionada
    if(destinationId == 0)
    {
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    while(verify_id(destinationId) == 0) // Se o ID não existir, pede por outro
    {
        printf("Erro: O ID não existe.\n");
        printf("ID de destino: ");
        scanf("%d", &destinationId);
    }

    printf("Usuario '%s' selecionado.\n", user[destinationId - 1].name); // Imprime qual é o usuário do ID de destino
    
    // Pede pelo valor a ser transferido
    printf("Valor da transferencia: ");
    scanf("%lf", &value);

    while(value <= 0) // Se o valor não for positivo imprime erro e pede o valor novamente
    {
        printf("Erro: Digite um valor positivo.\n");
        printf("Valor da transferencia: ");
        scanf("%lf", &value);
    }

    while(value > user[originId - 1].currency) // Se o usuário de origem não tiver saldo suficiente
    {
        printf("Erro: O usuario %d: '%s' nao possui saldo suficiente.\n", originId, user[originId - 1].name);
        printf("Valor da transferencia: ");
        scanf("%lf", &value);
    }

    // Faz a tranferência
    user[originId - 1].currency -= value;
    user[destinationId - 1].currency += value;

    print_in_database(user, LINES); // Escreve os novos dados no banco de dados

    // Imprime que a transfência foi efetuada corretamente
    printf("\n");
    printf(">>> A transferencia foi um sucesso. <<<\n");
    printf("\n");

    printf("=-=-=-=-=-OPERACAO REALIZADA-=-=-=-=-\n"); // Imprime o final da operação
    printf("\n");

    free(user); // Libera a memória alocada para a array de usuários

    return; // Retorna
}

// OPERAÇÃO 5
void remove_id() // Função que remove um usuário pelo ID
{
    // Define as variáveis que serão utilizadas
    const int LINES = add_id() - 1;
    users *user = malloc(sizeof(users) * LINES); // Array de usuários
    int id;

    load_users(user, LINES); // Carrega os usuários do banco de dados na array

    // Imprime para o usuário o cabeçalho
    printf("\n");
    printf("=-=-=-=-=-=REMOVER USUARIO-=-=-=-=-=-\n");

    // Verifica se existem usuários no banco de dados
    if(LINES == 0)
    {
        printf("Nao existem usuarios a serem removidos.\n");
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    printf("0. Voltar\n"); // Imprime para o usuário a opção de voltar

    printf("ID: ");
    scanf("%d", &id);

    // Volta se a opção de voltar tiver sido selecionada
    if(id == 0)
    {
        printf("=-=-=-=-=-=-=VOLTANDO...-=-=-=-=-=-=-\n"); // Imprime o final da operação
        printf("\n");
        return;
    }

    // Verifica se o ID selecionado existe
    while(verify_id(id) == 0)
    {
        printf("Nao existe usuario com esse ID.\n");
        printf("ID: ");
        scanf("%d", &id); 
    }
    
    char* userName = user[id - 1].name; // Cria um buffer pra armazenar o nome do usuário selecionado

    // Remove as informações do usuário na array
    user[id - 1].name = "removed_user"; // O nome do usuário que o ID indica passa a ser 'removed_user'
    user[id - 1].age = 0;
    user[id - 1].currency = 0;
    
    print_in_database(user, LINES); // Imprime no banco de dados os usuários armazenados na array
    
    // Imprime para o usuário que a operação foi realizada corretamente
    printf("\n");
    printf("Usuario '%s' removido com sucesso.\n", userName);
    printf("\n");

    printf("=-=-=-=-=-OPERACAO REALIZADA-=-=-=-=-\n"); // Imprime o final da operação
    printf("\n");

    free(user); // Libera a memória alocada para armazenar a array de usuários

    return; // Retorna
}
