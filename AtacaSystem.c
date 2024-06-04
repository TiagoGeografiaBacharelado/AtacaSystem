#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "AtacaSystemMenu.c"

// Defini��o de constantes
#define MAX_USERS 100
#define MAX_FUNCIONARIOS 100
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define MIN_PASSWORD_LENGTH 8

// Defini��o das estruturas
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

// Declara��o de vari�veis globais
User users[MAX_USERS];
Funcionario funcionarios[MAX_FUNCIONARIOS];
int userCount = 0;
int funcionarioCount = 0;
const char *chefeUsername = "chefe";
const char *chefePassword = "senha123";

// Fun��o para limpar o buffer de entrada
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Fun��o para validar nome de usu�rio
int isValidUsername(char *username) {
    if (strlen(username) == 0) {
        printf("Erro: O nome de usu�rio n�o pode estar vazio.\n");
        return 0;
    }

    for (int i = 0; i < strlen(username); i++) {
        if (isspace(username[i])) {
            printf("Erro: O nome de usu�rio n�o pode conter espa�os.\n");
            return 0;
        }
    }

    return 1;
}

// Fun��o para validar senha
int isValidPassword(char *password) {
    if (strlen(password) < MIN_PASSWORD_LENGTH) {
        printf("Erro: A senha deve ter pelo menos %d caracteres.\n", MIN_PASSWORD_LENGTH);
        return 0;
    }

    return 1;
}

// Fun��o para cadastrar novo usu�rio
void registerUser(User users[], int *userCount) {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Cadastrar Novo Usuario\n");

    // Valida��o do nome de usu�rio
    do {
        printf("Username: ");
        scanf("%s", username);
        clearInputBuffer();
    } while (!isValidUsername(username));

    // Valida��o da senha
    do {
        printf("Password: ");
        scanf("%s", password);
        clearInputBuffer();
    } while (!isValidPassword(password));

    // Armazenando o novo usu�rio
    strcpy(users[*userCount].username, username);
    strcpy(users[*userCount].password, password);

    (*userCount)++;
    printf("Usuario cadastrado com sucesso!\n");
}

// Fun��o para exibir a lista de usu�rios
void displayUsers(User users[], int userCount) {
    printf("Lista de Usuarios:\n");
    for (int i = 0; i < userCount; i++) {
        printf("Usuario %d:\n", i + 1);
        printf("Username: %s\n", users[i].username);
        printf("Password: %s\n", users[i].password);
    }
}

// Fun��o para exibir a lista de funcion�rios
void displayEmployees(Funcionario funcionarios[], int funcionarioCount) {
    printf("Lista de Funcion�rios:\n");
    for (int i = 0; i < funcionarioCount; i++) {
        printf("Funcion�rio %d:\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].name);
        printf("Username: %s\n", funcionarios[i].username);
        printf("Password: %s\n", funcionarios[i].password);
    }
}

// Fun��o para autenticar usu�rio
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

// Fun��o para editar usu�rio
void editUser(User users[], int userCount) {
    int userIndex;
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Editar Usuario\n");
    printf("Digite o �ndice do usu�rio para editar (1-%d): ", userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; // ajustar para �ndice baseado em 0

    if (userIndex < 0 || userIndex >= userCount) {
        printf("�ndice inv�lido!\n");
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

    // Atualizando o usu�rio
    strcpy(users[userIndex].username, username);
    strcpy(users[userIndex].password, password);

    printf("Usuario editado com sucesso!\n");
}

// Fun��o para excluir usu�rio
void deleteUser(User users[], int *userCount) {
    int userIndex;

    printf("Excluir Usuario\n");
    printf("Digite o �ndice do usu�rio para excluir (1-%d): ", *userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; // ajustar para �ndice baseado em 0

    if (userIndex < 0 || userIndex >= *userCount) {
        printf("�ndice inv�lido!\n");
        return;
    }

    // Movendo os usu�rios para preencher o espa�o vazio
    for (int i = userIndex; i < *userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    (*userCount)--;
    printf("Usuario exclu�do com sucesso!\n");
}

// Menu do chefe
void chefeMenu(User users[], int *userCount, Funcionario funcionarios[], int *funcionarioCount) {
    int option;
    char choice;
    while (1) {
        printf("\nMenu do Chefe:\n");
        printf("1. Listar Funcion�rios\n");
        printf("2. Editar Funcion�rio\n");
        printf("3. Excluir Funcion�rio\n");
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

// Fun��o placeholder para o caixa
void caixa() {
    printf("Bem-vindo ao Caixa!\n");
    // Adicione as funcionalidades do caixa aqui
}

// Fun��o de login
void login() {
    int choice;
    printf("\t\t\t\t                                                    \n");
    printf("\n\t\t\t\t                   Login                          \n");
    printf("\t\t\t\t                                                    \n");
    printf("\t\t\t\t                   1- Login como Chefe             \n");
    printf("\t\t\t\t                   2- Login como Caixa             \n");
    printf("\t\t\t\t                                                    \n");
    printf("\t\t\t\t                  Escolha uma op��o: ");
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
        printf("Op��o inv�lida!\n");
    }
}

// Fun��o para cadastrar funcion�rio
void registerEmployee() {
    Funcionario funcionario; // Vari�vel para armazenar os dados do funcion�rio

    printf("Nome: ");
    scanf(" %29[^\n]", funcionario.name); // Use [^\n] para ler toda a linha at� a quebra de linha
    clearInputBuffer(); // Limpar o buffer de entrada

    printf("Crie um nome de usu�rio: ");
    scanf(" %7s", funcionario.username); // Use %7s para ler at� 7 caracteres (evitando buffer overflow)
    clearInputBuffer(); // Limpar o buffer de entrada

    printf("Crie uma senha: ");
    scanf(" %7s", funcionario.password); // Use %7s para ler at� 7 caracteres (evitando buffer overflow)
    clearInputBuffer(); // Limpar o buffer de entrada

    // Adicionar o funcion�rio ao array de funcion�rios
    funcionarios[funcionarioCount] = funcionario;
    funcionarioCount++;

    printf("Funcion�rio cadastrado com sucesso!\n");
}

// Fun��o principal de op��es
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
        printf("\t\t\t\t                  Escolha uma op��o:  ");
        scanf("%d", &choice);
        clearInputBuffer(); // Limpar o buffer de entrada para evitar problemas na leitura posterior

        system("cls");

        switch (choice) {
            case 1:
                login();
                break;

            case 2:
                do {
                    registerEmployee(); // Chame a fun��o de registro de funcion�rio
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
                printf("\nJo�o Arthur\n");
                break;

            case 4:
                printf("Saindo...\n");
                return;

            default:
                printf("Op��o inv�lida\n");
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

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    
	printLogo();
	
    option();
    
    return 0;
}