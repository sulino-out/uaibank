// INCLUSÃO DE BIBLIOTECAS

#include "operations.h"

// FUNÇÃO MAIN

int main(void)
{
    int operation; // Cria uma variavel pra armazenar a operação a ser feita

    while (1)
    {
        print_operations();

        operation = select_operation(); // Armazena em uma variável a operação a ser realizada
        if (operation == 0) // Define como 0 o valor de saída do programa
        {
            break;
        }
    
        run_operation(operation); // Roda a operação selecionada
    }

    return 0;
}