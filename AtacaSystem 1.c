#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "AtacaSystemMenu.c"

#define MAX_USERS 100
#define MAX_FUNCIONARIOS 100
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

typedef struct {
    char name[30];
    char username[8];
    char password[8];
} Funcionario;

Funcionario funcionarios[MAX_FUNCIONARIOS];
int funcionarioCount = 0;

void displayEmployees(Funcionario funcionarios[], int funcionarioCount) {
    printf("Lista de Funcionários:\n");
    for (int i = 0; i < funcionarioCount; i++) {
        printf("Funcionário %d:\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].name);
        printf("Username: %s\n", funcionarios[i].username);
        printf("Password: %s\n", funcionarios[i].password);
    }
}

void registerEmployee() {
    Funcionario funcionario;

    printf("Nome: ");
    scanf(" %29[^\n]", funcionario.name);

    printf("Crie um nome de usuário: ");
    scanf(" %7s", funcionario.username);

    printf("Crie uma senha: ");
    scanf(" %7s", funcionario.password);

    funcionarios[funcionarioCount] = funcionario;
    funcionarioCount++;

    printf("Funcionário cadastrado com sucesso!\n");
}

void option() {
    int choice;
    char choice_char;

    while (1) {
        printf("\n\t\t\t\t                   Menu                           \n");
        printf("\t\t\t\t                                                    \n");
        printf("\t\t\t\t                   1- Cadastrar Funcionário        \n");
        printf("\t\t\t\t                   2- Listar Funcionários          \n");
        printf("\t\t\t\t                   3- Desenvolvedores               \n");
        printf("\t\t\t\t                   4- Sair                          \n");
        printf("\t\t\t\t                                                    \n");
        printf("\t\t\t\t                  Escolha uma opção:  ");
        scanf("%d", &choice);

        system("cls");

        switch (choice) {
            case 1:
                do {
                    registerEmployee();
                    printf("\nDigite 'c' para continuar cadastrando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice_char);
                    system("cls");
                } while (choice_char == 'c');
                break;

            case 2:
                displayEmployees(funcionarios, funcionarioCount);
                break;

            case 3:
                printf("Tiago Carneiro do Nascimento\n");
                printf("\nAdriel Saretto\n");
                printf("\nGabriel de Souza\n");
                printf("\nJoão Arthur\n");
                break;

            case 4:
                printf("Saindo...\n");
                return;

            default:
                printf("Opção inválida\n");
        }

        printf("\nDigite 'y' para continuar no menu ou 'n' para sair: ");
        scanf(" %c", &choice_char);
        if (choice_char == 'n') {
            break;
        }
        system("cls");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    printLogo();

    option();

    return 0;
}
