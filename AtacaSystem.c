#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "AtacaSystemMenu.c"

// Definição de constantes
#define MAX_USERS 100
#define MAX_FUNCIONARIOS 100
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define MIN_PASSWORD_LENGTH 8

// Definição das estruturas
typedef struct {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} User;

typedef struct {
    char name[30];
    char username[8];
    char password[8];
} Funcionario;

/*typedef struct {
	char nome
	char 
};
*/

// Declaração de variáveis globais
User users[MAX_USERS];
Funcionario funcionarios[MAX_FUNCIONARIOS];
int userCount = 0;
int funcionarioCount = 0;
const char *chefeUsername = "chefe";
const char *chefePassword = "senha123";

// Função para limpar o buffer de entrada
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Função para validar nome de usuário
int isValidUsername(char *username) {
    if (strlen(username) == 0) {
        printf("Erro: O nome de usuário não pode estar vazio.\n");
        return 0;
    }

    for (int i = 0; i < strlen(username); i++) {
        if (isspace(username[i])) {
            printf("Erro: O nome de usuário não pode conter espaços.\n");
            return 0;
        }
    }

    return 1;
}

// Função para validar senha
int isValidPassword(char *password) {
    if (strlen(password) < MIN_PASSWORD_LENGTH) {
        printf("Erro: A senha deve ter pelo menos %d caracteres.\n", MIN_PASSWORD_LENGTH);
        return 0;
    }

    return 1;
}

// Função para cadastrar novo usuário
void registerUser(User users[], int *userCount) {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Cadastrar Novo Usuario\n");

    // Validação do nome de usuário
    do {
        printf("Username: ");
        scanf("%s", username);
        clearInputBuffer();
    } while (!isValidUsername(username));

    // Validação da senha
    do {
        printf("Password: ");
        scanf("%s", password);
        clearInputBuffer();
    } while (!isValidPassword(password));

    // Armazenando o novo usuário
    strcpy(users[*userCount].username, username);
    strcpy(users[*userCount].password, password);

    (*userCount)++;
    printf("Usuario cadastrado com sucesso!\n");
}

// Função para exibir a lista de usuários
void displayUsers(User users[], int userCount) {
    printf("Lista de Usuarios:\n");
    for (int i = 0; i < userCount; i++) {
        printf("Usuario %d:\n", i + 1);
        printf("Username: %s\n", users[i].username);
        printf("Password: %s\n", users[i].password);
    }
}

// Função para exibir a lista de funcionários
void displayEmployees(Funcionario funcionarios[], int funcionarioCount) {
    printf("Lista de Funcionários:\n");
    for (int i = 0; i < funcionarioCount; i++) {
        printf("Funcionário %d:\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].name);
        printf("Username: %s\n", funcionarios[i].username);
        printf("Password: %s\n", funcionarios[i].password);
    }
}

// Função para autenticar usuário
int authenticateUser(const char *expectedUsername, const char *expectedPassword) {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    printf("Autenticacao\n");
    printf("Username: ");
    scanf("%s", username);
    clearInputBuffer();
    printf("Password: ");
    scanf("%s", password);
    clearInputBuffer();
    
    if (strcmp(username, expectedUsername) == 0 && strcmp(password, expectedPassword) == 0) {
        return 1; 
    }
    return 0; 
}

// Função para editar usuário
void editUser(User users[], int userCount) {
    int userIndex;
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Editar Usuario\n");
    printf("Digite o índice do usuário para editar (1-%d): ", userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; // ajustar para índice baseado em 0

    if (userIndex < 0 || userIndex >= userCount) {
        printf("Índice inválido!\n");
        return;
    }

    do {
        printf("Novo Username: ");
        scanf("%s", username);
        clearInputBuffer();
    } while (!isValidUsername(username));

    do {
        printf("Nova Password: ");
        scanf("%s", password);
        clearInputBuffer();
    } while (!isValidPassword(password));

    // Atualizando o usuário
    strcpy(users[userIndex].username, username);
    strcpy(users[userIndex].password, password);

    printf("Usuario editado com sucesso!\n");
}

// Função para excluir usuário
void deleteUser(User users[], int *userCount) {
    int userIndex;

    printf("Excluir Usuario\n");
    printf("Digite o índice do usuário para excluir (1-%d): ", *userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; // ajustar para índice baseado em 0

    if (userIndex < 0 || userIndex >= *userCount) {
        printf("Índice inválido!\n");
        return;
    }

    // Movendo os usuários para preencher o espaço vazio
    for (int i = userIndex; i < *userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    (*userCount)--;
    printf("Usuario excluído com sucesso!\n");
}

// Menu do chefe
void chefeMenu(User users[], int *userCount, Funcionario funcionarios[], int *funcionarioCount) {
    int option;
    char choice;
    while (1) {
        printf("\nMenu do Chefe:\n");
        printf("1. Listar Funcionários\n");
        printf("2. Editar Funcionário\n");
        printf("3. Excluir Funcionário\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        clearInputBuffer();
        system("cls");

        switch (option) {
            case 1:
                do {
                    displayEmployees(funcionarios, *funcionarioCount);
                    printf("\nDigite 'c' para continuar listando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 2:
                do {
                    editUser(users, *userCount);
                    printf("\nDigite 'c' para continuar editando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 3:
                do {
                    deleteUser(users, userCount);
                    printf("\nDigite 'c' para continuar excluindo ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 4:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

// Função placeholder para o caixa
void caixa() {
    printf("Bem-vindo ao Caixa!\n");
    // Adicione as funcionalidades do caixa aqui
}

// Função de login
void login() {
    int choice;
    printf("\t\t\t\t                                                    \n");
    printf("\n\t\t\t\t                   Login                          \n");
    printf("\t\t\t\t                                                    \n");
    printf("\t\t\t\t                   1- Login como Chefe             \n");
    printf("\t\t\t\t                   2- Login como Caixa             \n");
    printf("\t\t\t\t                                                    \n");
    printf("\t\t\t\t                  Escolha uma opção: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1) {
        if (authenticateUser(chefeUsername, chefePassword)) {
            chefeMenu(users, &userCount, funcionarios, &funcionarioCount);
        } else {
            printf("Autenticacao falhou! Acesso negado.\n");
        }
    } else if (choice == 2) {
        caixa();
    } else {
        printf("Opção inválida!\n");
    }
}

// Função para cadastrar funcionário
void registerEmployee() {
    Funcionario funcionario; // Variável para armazenar os dados do funcionário

    printf("Nome: ");
    scanf(" %29[^\n]", funcionario.name); // Use [^\n] para ler toda a linha até a quebra de linha
    clearInputBuffer(); // Limpar o buffer de entrada

    printf("Crie um nome de usuário: ");
    scanf(" %7s", funcionario.username); // Use %7s para ler até 7 caracteres (evitando buffer overflow)
    clearInputBuffer(); // Limpar o buffer de entrada

    printf("Crie uma senha: ");
    scanf(" %7s", funcionario.password); // Use %7s para ler até 7 caracteres (evitando buffer overflow)
    clearInputBuffer(); // Limpar o buffer de entrada

    // Adicionar o funcionário ao array de funcionários
    funcionarios[funcionarioCount] = funcionario;
    funcionarioCount++;

    printf("Funcionário cadastrado com sucesso!\n");
}

// Função principal de opções
void option() {
    int choice;
    char choice_char;

    while (1) {
        printf("\n\t\t\t\t                   Menu                           \n");
        printf("\t\t\t\t                                                    \n");
        printf("\t\t\t\t                   1- Login                         \n");
        printf("\t\t\t\t                   2- Cadastro                      \n");
        printf("\t\t\t\t                   3- Desenvolvedores               \n");
        printf("\t\t\t\t                   4- Sair                          \n");
        printf("\t\t\t\t                                                    \n");
        printf("\t\t\t\t                  Escolha uma opção:  ");
        scanf("%d", &choice);
        clearInputBuffer(); // Limpar o buffer de entrada para evitar problemas na leitura posterior

        system("cls");

        switch (choice) {
            case 1:
                login();
                break;

            case 2:
                do {
                    registerEmployee(); // Chame a função de registro de funcionário
                    printf("\nDigite 'c' para continuar cadastrando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice_char);
                    clearInputBuffer();
                    system("cls");
                } while (choice_char == 'y');
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
        clearInputBuffer();
        if (choice_char == 'n') {
            break;
        }
        system("cls");
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    
	printLogo();
	
    option();
    
    return 0;
}