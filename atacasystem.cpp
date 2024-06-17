#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
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
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} Funcionario;

typedef struct {
    char name[30];
    char ID[14];
    float price;
    int amount;
    char expirationDate[11];
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
    printf("Lista de Funcion?rios:\n");
    for (int i = 0; i < funcionarioCount; i++) {
        printf("Funcionário %d:\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].name);
        printf("Username: %s\n", funcionarios[i].username);
        printf("Password: %s\n", funcionarios[i].password);
        printf("\n");
    }
}

int authenticateUser(const char *expectedUsername, const char *expectedPassword) {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    
    printf("Autenticação\n");
    printf("Username: ");
    scanf("%49s", username);
    clearInputBuffer();
    printf("Password: ");
    scanf("%49s", password);
    clearInputBuffer();
    system("cls");

    if ((strcmp(username, expectedUsername) == 0 && strcmp(password, expectedPassword) == 0)) {
        return 1;
    }

    // Verifica se o usu?rio ? um caixa registrado
    for (int i = 0; i < funcionarioCount; i++) {
        if (strcmp(username, funcionarios[i].username) == 0 && strcmp(password, funcionarios[i].password) == 0) {
            return 1;
        }
    }

    printf("Falha na autenticação. Verifique suas credenciais.\n");
    return 0;
}

void editUser(User users[], int userCount) {
    int userIndex;
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Editar Usuario\n");
    printf("Digite o ID do usuário para editar (1-%d): ", userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; 

    if (userIndex < 0 || userIndex >= userCount) {
        printf("ID inválido!\n");
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
    printf("Digite o ID do usuário para excluir (1-%d): ", *userCount);
    scanf("%d", &userIndex);
    clearInputBuffer();
    userIndex--; 

    if (userIndex < 0 || userIndex >= *userCount) {
        printf("ID inválido!\n");
        return;
    }

    for (int i = userIndex; i < *userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    (*userCount)--;
    printf("Usuario excluído com sucesso!\n");
}

void commissionis() {
	char nome[50];
	float venda;
	float taxa;
	float comissao;

	printf("Por favor, informe os dados da venda\n");

	printf("Nome do vendedor: ");
	scanf("%s", nome);

	printf("Valor das vendas (R$): ");
	scanf("%f", &venda);

	printf("Taxa em %%: ");
	scanf("%f", &taxa);

	comissao = venda * taxa / 100;

	printf("\n");
	printf("|Nome do vendedor: %s\n", nome);
	printf("|Valor da venda(R$): %.2f\n", venda);
	printf("|Taxa: %.2f %%\n", taxa);
	printf("|Comissão a pagar o vendedor: R$ %.2f\n", comissao);

	FILE *file = fopen("comissoes.txt", "a");
	if (file == NULL) {
    	printf("Erro ao abrir o arquivo!\n");
    return;
}

	fprintf(file, "Codigo do vendedor: %s\n", nome);
	fprintf(file, "Valor da venda(R$): %.2f\n", venda);	
	fprintf(file, "Taxa: %.2f %%\n", taxa);
	fprintf(file, "Comissão a pagar o vendedor: R$ %.2f\n", comissao);
	fprintf(file, "\n");
	system("pause");
	system("cls");


	fclose(file);
}

void chefeMenu(User users[], int *userCount, Funcionario funcionarios[], int *funcionarioCount) {
    int option;
    char choice;
    while (1) {
        printf("\nMenu do Chefe:\n");
        printf("1. Listar Funcion?rios\n");
        printf("2. Editar Funcion?rio\n");
        printf("3. Excluir Funcion?rio\n");
        printf("4. Comissão do funcionario\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma op??o: ");
        scanf("%d", &option);
        clearInputBuffer();
        system("cls");

        switch (option) {
            case 1:
                do {
                    displayEmployees(funcionarios, *funcionarioCount);
                    printf("\nDigite 'c' para continuar listando\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 2:
                do {
                    editUser(users, *userCount);
                    printf("\nDigite 'c' para continuar editando\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 3:
                do {
                    deleteUser(users, userCount);
                    printf("\nDigite 'c' para continuar excluindo\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 4:
            	do{
            		commissionis();
            		clearInputBuffer();
                    system("cls");
				}while (choice == 'c');
            case 5:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
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
        printf("Quantidade: %d\n", produtos[i].amount);
        printf("Data de Validade: %s\n", produtos[i].expirationDate);
        printf("\n");
    }
}

void searchProduct(const Product produtos[], int produtoCount) {
    char searchName[30];
    printf("Buscar Produto\n");
    printf("Digite o nome do produto: ");
    scanf("%29s", searchName);
    clearInputBuffer();

    for (int i = 0; i < produtoCount; i++) {
        if (strcmp(produtos[i].name, searchName) == 0) {
            printf("Produto encontrado:\n");
            printf("Nome: %s\n", produtos[i].name);
            printf("ID: %s\n", produtos[i].ID);
            printf("Preço: %.2f\n", produtos[i].price);
            printf("Quantidade em estoque: %d\n", produtos[i].amount);
            printf("Data de vencimento: %s\n", produtos[i].expirationDate);
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void editProduct(Product produtos[], int produtoCount) {
    int produtoIndex;
    char name[30];
    char ID[14];
    float price;
    int amount;
    char expirationDate[11];

    printf("Editar Produto\n");
    printf("Digite o ID do produto para editar (1-%d): ", produtoCount);
    scanf("%d", &produtoIndex);
    clearInputBuffer();
    produtoIndex--; 

    if (produtoIndex < 0 || produtoIndex >= produtoCount) {
        printf("ID inválido!\n");
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

    printf("Nova Quantidade em estoque: ");
    scanf("%d", &amount);
    clearInputBuffer();

    printf("Nova Data de vencimento (DD/MM/AAAA): ");
    scanf("%10s", expirationDate);
    clearInputBuffer();

    strcpy(produtos[produtoIndex].name, name);
    strcpy(produtos[produtoIndex].ID, ID);
    produtos[produtoIndex].price = price;
    produtos[produtoIndex].amount = amount;
    strcpy(produtos[produtoIndex].expirationDate, expirationDate);

    printf("Produto editado com sucesso!\n");
}

void deleteProduct(Product produtos[], int *produtoCount) {
    int produtoIndex;

    printf("Excluir Produto\n");
    printf("Digite o indice do produto para excluir (1-%d): ", *produtoCount);
    scanf("%d", &produtoIndex);
    clearInputBuffer();
    produtoIndex--; 

    if (produtoIndex < 0 || produtoIndex >= *produtoCount) {
        printf("ID inválido!\n");
        return;
    }

    for (int i = produtoIndex; i < *produtoCount - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    (*produtoCount)--;
    printf("Produto excluído com sucesso!\n");
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
    
    printf("Crie uma quantidade em estoque: ");
    scanf("%d", &produto.amount);
    clearInputBuffer();
    
     printf("Crie uma data de vencimento (DD/MM/AAAA): ");
    scanf("%10s", produto.expirationDate);
    clearInputBuffer();

    if (produtoCount < MAX_PRODUCTS) {
        produtos[produtoCount] = produto;
        produtoCount++;
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos atingido!\n");
    }
}

int findProductIndexByID(const Product produtos[], int produtoCount, const char *ID) {
    for (int i = 0; i < produtoCount; i++) {
        if (strcmp(produtos[i].ID, ID) == 0) {
            return i;
        }
    }
    return -1;
}

void sellProduct(Product produtos[], int produtoCount) {
    char productID[14];
    int quantity;

    printf("Venda de Produto\n");
    printf("Digite o ID do produto: ");
    scanf("%13s", productID);
    clearInputBuffer();

    int productIndex = findProductIndexByID(produtos, produtoCount, productID);
    if (productIndex == -1) {
        printf("Produto n?o encontrado.\n");
        return;
    }

    printf("Produto encontrado:\n");
    printf("Nome: %s\n", produtos[productIndex].name);
    printf("Pre?o: %.2f\n", produtos[productIndex].price);
    printf("Estoque: %d\n", produtos[productIndex].amount);

    printf("Digite a quantidade que deseja vender: ");
    scanf("%d", &quantity);
    clearInputBuffer();

    if (quantity > produtos[productIndex].amount) {
        printf("Quantidade indisponível em estoque.\n");
        return;
    }

    float total = produtos[productIndex].price * quantity;
    produtos[productIndex].amount -= quantity;

    printf("Venda realizada com sucesso!\n");
    printf("Total da venda: R$ %.2f\n", total);
}

void menuBox(Product produtos[], int produtoCount) {
    int option;
    char choice;
    while (1) {
        printf("\nMenu do Caixa:\n");
        printf("1. Vender Produto\n");
        printf("2. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        clearInputBuffer();
        system("cls");

        switch (option) {
            case 1:
                do {
                    sellProduct(produtos, produtoCount);
                    printf("\nDigite 'c' para continuar vendendo\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 2:
                return;
            default:
                printf("Op??o inv?lida! Tente novamente.\n");
        }
    }
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
                    printf("\nDigite 'c' para continuar listando\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 2:
                do {
                    registerProduct();
                    printf("\nDigite 'c' para continuar cadastrando\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 3:
                do {
                    searchProduct(produtos, produtoCount);
                    printf("\nDigite 'c' para continuar buscando\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 4:
                do {
                    editProduct(produtos, produtoCount);
                    printf("\nDigite 'c' para continuar editando\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 5:
                do {
                    deleteProduct(produtos, &produtoCount);
                    printf("\nDigite 'c' para continuar excluindo\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 6:
                do {
                    menuBox(produtos, produtoCount);
                    printf("\nDigite 'c' para continuar vendendo\nDigite 'b' para voltar ao menu anterior: ");
                    scanf(" %c", &choice);
                    clearInputBuffer();
                    system("cls");
                } while (choice == 'c');
                break;
            case 7:
                return;
            default:
                printf("Op??o inv?lida! Tente novamente.\n");
        }
    }
}

void login(User users[], int userCount, Funcionario funcionarios[], int funcionarioCount) {
    char choice;
    while (1) {
        printf("Bem-vindo ao AtacaSystem!\n");
        printf("Escolha o tipo de usu?rio:\n");
        printf("1. Chefe\n");
        printf("2. Caixa\n");
        printf("3. Sair\n");
        printf("Escolha uma op??o: ");
        int option;
        scanf("%d", &option);
        clearInputBuffer();
        system("cls");

        switch (option) {
            case 1:
                if (authenticateUser(chefeUsername, chefePassword)) {
                    chefeMenu(users, &userCount, funcionarios, &funcionarioCount);
                } else {
                    printf("Falha na autenticação. Verifique suas credenciais.\n");
                }
                break;
            case 2:
                if (authenticateUser("caixa", "senha456")) {
                    cashierMenu();
                } else {
                    printf("Falha na autenticação. Verifique suas credenciais.\n");
                }
                break;
            case 3:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
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

void expirationAlert(const Product produtos[], int produtoCount) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char today[11];
    sprintf(today, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("Alerta de Vencimento\n");
    for (int i = 0; i < produtoCount; i++) {
        if (strcmp(produtos[i].expirationDate, today) == 0) {
            printf("O produto %s está vencendo hoje!\n", produtos[i].name);
		}
	}
}

void inicializarFuncionarios(Funcionario funcionarios[], int *funcionarioCount) {
    
    strcpy(funcionarios[*funcionarioCount].name, "Bob Esponja");
    strcpy(funcionarios[*funcionarioCount].username, "BOB");
    strcpy(funcionarios[*funcionarioCount].password, "Gary");
    (*funcionarioCount)++;

    strcpy(funcionarios[*funcionarioCount].name, "Lula Molusco");
    strcpy(funcionarios[*funcionarioCount].username, "Molusco");
    strcpy(funcionarios[*funcionarioCount].password, "clarinete");
    (*funcionarioCount)++;
}

void inicializarProdutos(Product produtos[], int *produtoCount) {
    
    strcpy(produtos[*produtoCount].name, "Nescau");
    strcpy(produtos[*produtoCount].ID, "4002892222222");
    produtos[*produtoCount].price = 6.99;
    produtos[*produtoCount].amount = 50;
    strcpy(produtos[*produtoCount].expirationDate, "2024-12-31");
    (*produtoCount)++;

    strcpy(produtos[*produtoCount].name, "Leite");
    strcpy(produtos[*produtoCount].ID, "4003456789012");
    produtos[*produtoCount].price = 5.0;
    produtos[*produtoCount].amount = 30;
    strcpy(produtos[*produtoCount].expirationDate, "2023-08-15");
    (*produtoCount)++;

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
                login(users, userCount, funcionarios, funcionarioCount); // Passando os par?metros corretos
                break;

            case 2:
                do {
                    registerEmployee();
                    printf("\nDigite 'c' para continuar cadastrando\nDigite 'b' para voltar ao menu anterior: ");
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
                printf("Obrigado por usar o AtacaSystem!\n");
                exit(EXIT_SUCCESS);

            default:
                printf("Opção inv?lida\n");
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
    inicializarFuncionarios(funcionarios, &funcionarioCount);
    inicializarProdutos(produtos, &produtoCount);
    printLogo();
    
    option();

    return 0;
}
