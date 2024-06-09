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
#define MIN_PASSWORD_LENGTH 8
#define MAX_PRODUCTS 100
#define PRODUCT_NAME_MAX_LENGTH 50


typedef struct {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} User;

typedef struct {
    char name[30];
    char username[8];
    char password[8];
} Funcionario;

typedef struct {
    char name[30];
    char ID[14]; 
    float price;
} Product;


User users[MAX_USERS];
Funcionario funcionarios[MAX_FUNCIONARIOS];
Product produtos[MAX_PRODUCTS];
int userCount = 0;
int funcionarioCount = 0;
int produtoCount = 0;
const char *chefeUsername = "chefe";
const char *chefePassword = "senha123";


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


int isValidUsername(const char *username) {
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


int isValidPassword(const char *password) {
    if (strlen(password) < MIN_PASSWORD_LENGTH) {
        printf("Erro: A senha deve ter pelo menos %d caracteres.\n", MIN_PASSWORD_LENGTH);
        return 0;
    }
    return 1;
}


void registerUser(User users[], int *userCount) {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Cadastrar Novo Usuario\n");

    
    do {
        printf("Username: ");
        scanf("%49s", username);
        clearInputBuffer();
    } while (!isValidUsername(username));

    
    do {
        printf("Password: ");
        scanf("%49s", password);
        clearInputBuffer();
    } while (!isValidPassword(password));

    
    strcpy(users[*userCount].username, username);
    strcpy(users[*userCount].password, password);

    (*userCount)++;
    printf("Usuario cadastrado com sucesso!\n");
}


void displayUsers(const User users[], int userCount) {
    printf("Lista de Usuarios:\n");
    for (int i = 0; i < userCount; i++) {
        printf("Usuario %d:\n", i + 1);
        printf("Username: %s\n", users[i].username);
        printf("Password: %s\n", users[i].password);
    }
}


void displayEmployees(const Funcionario funcionarios[], int funcionarioCount) {
    printf("Lista de Funcionários:\n");
    for (int i = 0; i < funcionarioCount; i++) {
        printf("Funcionário %d:\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].name);
        printf("Username: %s\n", funcionarios[i].username);
        printf("Password: %s\n", funcionarios[i].password);
    }
}


int authenticateUser(const char *expectedUsername, const char *expectedPassword) {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    printf("Autenticacao\n");
    printf("Username: ");
    scanf("%49s", username);
    clearInputBuffer();
    printf("Password: ");
    scanf("%49s", password);
    clearInputBuffer();
    system("cls");
    
    return strcmp(username, expectedUsername) == 0 && strcmp(password, expectedPassword) == 0;
}


void editUser(User users[], int userCount) {
    int userIndex;
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Editar Usuario\n");
    printf("Digite o índice do usuário para editar (1-%d): ", userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; 

    if (userIndex < 0 || userIndex >= userCount) {
        printf("Índice inválido!\n");
        return;
    }

    do {
        printf("Novo Username: ");
        scanf("%49s", username);
        clearInputBuffer();
    } while (!isValidUsername(username));

    do {
        printf("Nova Password: ");
        scanf("%49s", password);
        clearInputBuffer();
    } while (!isValidPassword(password));

    
    strcpy(users[userIndex].username, username);
    strcpy(users[userIndex].password, password);

    printf("Usuario editado com sucesso!\n");
}


void deleteUser(User users[], int *userCount) {
    int userIndex;

    printf("Excluir Usuario\n");
    printf("Digite o índice do usuário para excluir (1-%d): ", *userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; 

    if (userIndex < 0 || userIndex >= *userCount) {
        printf("Índice inválido!\n");
        return;
    }

    
    for (int i = userIndex; i < *userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    (*userCount)--;
    printf("Usuario excluído com sucesso!\n");
}


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


void displayProducts(const Product produtos[], int produtoCount) {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < produtoCount; i++) {
        printf("Produto %d:\n", i + 1);
        printf("Nome: %s\n", produtos[i].name);
        printf("ID: %s\n", produtos[i].ID);
        printf("Preço: %.2f\n", produtos[i].price);
        printf("\t\n");
    }
}


void searchProduct(const Product produtos[], int produtoCount) {
    char searchName[PRODUCT_NAME_MAX_LENGTH];
    printf("Buscar Produto\n");
    printf("Digite o nome do produto: ");
    scanf("%49s", searchName);
    clearInputBuffer();

    for (int i = 0; i < produtoCount; i++) {
        if (strcmp(produtos[i].name, searchName) == 0) {
            printf("Produto encontrado:\n");
            printf("Nome: %s\n", produtos[i].name);
            printf("ID: %s\n", produtos[i].ID);
            printf("Preço: %.2f\n", produtos[i].price);
            return;
        }
    }
    printf("Produto não encontrado.\n");
}


void editProduct(Product produtos[], int produtoCount) {
    int produtoIndex;
    char name[PRODUCT_NAME_MAX_LENGTH];
    char ID[14];
    float price;

    printf("Editar Produto\n");
    printf("Digite o índice do produto para editar (1-%d): ", produtoCount);
    scanf("%d", &produtoIndex);
    clearInputBuffer();
    produtoIndex--; 

    if (produtoIndex < 0 || produtoIndex >= produtoCount) {
        printf("Índice inválido!\n");
        return;
    }

    printf("Novo Nome: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; 

    printf("Nova IDentificação: ");
    scanf("%13s", ID);
    clearInputBuffer();

    printf("Novo Preço: ");
    scanf("%f", &price);
    clearInputBuffer();

    
    strcpy(produtos[produtoIndex].name, name);
    strcpy(produtos[produtoIndex].ID, ID);
    produtos[produtoIndex].price = price;

    printf("Produto editado com sucesso!\n");
}


void deleteProduct(Product produtos[], int *produtoCount) {
    int produtoIndex;

    printf("Excluir Produto\n");
    printf("Digite o índice do produto para excluir (1-%d): ", *produtoCount);
    scanf("%d", &produtoIndex);
    clearInputBuffer();
    produtoIndex--; 

    if (produtoIndex < 0 || produtoIndex >= *produtoCount) {
        printf("Índice inválido!\n");
        return;
    }

    
    for (int i = produtoIndex; i < *produtoCount - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    (*produtoCount)--;
    printf("Produto excluído com sucesso!\n");
}


void cashierMenu() {
    int option;
    char choice;
    while (1) {
        printf("\nMenu do Caixa:\n");
        printf("1. Listar Produtos\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Buscar Produto\n");
        printf("4. Editar Produto\n");
        printf("5. Excluir Produto\n");
        printf("6. Venda\n");
        printf("7. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
        clearInputBuffer();
        system("cls");

        switch (option) {
            case 1:
                do {
                    displayProducts(produtos, produtoCount);
                    printf("\nDigite 'c' para continuar listando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 2:
                do {
                    registerProduct();
                    printf("\nDigite 'c' para continuar cadastrando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 3:
                do {
                    searchProduct(produtos, produtoCount);
                    printf("\nDigite 'c' para continuar buscando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 4:
                do {
                    editProduct(produtos, produtoCount);
                    printf("\nDigite 'c' para continuar editando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 5:
                do {
                    deleteProduct(produtos, &produtoCount);
                    printf("\nDigite 'c' para continuar excluindo ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 6:
                do {
                    // Função de vendas deve ser adicionada aqui
                    printf("\nDigite 'c' para continuar vendendo ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 7:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}


void login() {
    int choice;
    printf("\t\t\t\t\n");
    printf("\n\t\t\t\t                   Login                          \n");
    printf("\t\t\t\t\n");
    printf("\t\t\t\t                   1- Login como Chefe             \n");
    printf("\t\t\t\t                   2- Login como Caixa             \n");
    printf("\t\t\t\t\n");
    printf("\t\t\t\t                  Escolha uma opção: ");
    scanf("%d", &choice);
    clearInputBuffer();
    system("cls");

    if (choice == 1) {
        if (authenticateUser(chefeUsername, chefePassword)) {
            chefeMenu(users, &userCount, funcionarios, &funcionarioCount);
        } else {
            printf("Autenticacao falhou! Acesso negado.\n");
        }
    } else if (choice == 2) {
        cashierMenu();
    } else {
        printf("Opção inválida!\n");
    }
}


void registerEmployee() {
    Funcionario funcionario; 

    printf("Nome: ");
    fgets(funcionario.name, sizeof(funcionario.name), stdin);
    funcionario.name[strcspn(funcionario.name, "\n")] = '\0'; 

    printf("Crie um nome de usuário: ");
    scanf("%7s", funcionario.username);
    clearInputBuffer();

    printf("Crie uma senha: ");
    scanf("%7s", funcionario.password);
    clearInputBuffer();
    
    
    if (funcionarioCount < MAX_FUNCIONARIOS) {
        funcionarios[funcionarioCount] = funcionario;
        funcionarioCount++;
        printf("Funcionário cadastrado com sucesso!\n");
    } else {
        printf("Limite de funcionários atingido!\n");
    }
}


void registerProduct() {
    Product produto; 

    printf("Nome: ");
    fgets(produto.name, sizeof(produto.name), stdin);
    produto.name[strcspn(produto.name, "\n")] = '\0'; 

    printf("Crie uma IDentificação: ");
    scanf("%13s", produto.ID);
    clearInputBuffer();

    printf("Crie um preço: ");
    scanf("%f", &produto.price);
    clearInputBuffer();

    
    if (produtoCount < MAX_PRODUCTS) {
        produtos[produtoCount] = produto;
        produtoCount++;
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos atingido!\n");
    }
}


void option() {
    int choice;
    char choice_char;

    while (1) {
        printf("\n\t\t\t\t                   Menu                           \n");
        printf("\t\t\t\t\n");
        printf("\t\t\t\t                   1- Login                         \n");
        printf("\t\t\t\t                   2- Cadastro                      \n");
        printf("\t\t\t\t                   3- Desenvolvedores               \n");
        printf("\t\t\t\t                   4- Sair                          \n");
        printf("\t\t\t\t\n");
        printf("\t\t\t\t                  Escolha uma opção:  ");
        scanf("%d", &choice);
        clearInputBuffer();

        system("cls");

        switch (choice) {
            case 1:
                login();
                break;

            case 2:
                do {
                    registerEmployee();
                    printf("\nDigite 'c' para continuar cadastrando ou 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice_char);
                    clearInputBuffer();
                    system("cls");
                } while (choice_char == 'c');
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


int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    printLogo();
    option();

    return 0;
}