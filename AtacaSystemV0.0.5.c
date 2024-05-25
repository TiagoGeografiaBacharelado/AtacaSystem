#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#define MAX 10

#include "AtacaSystemMenu.c"

typedef struct{
	char name[50];
	char code[30];
	char vality[8];
	int price;
}Product;

int cod = 0;

void menu(), listProducts();
int addProduct(), searchProduct();

int main(){
	setlocale(LC_ALL, "Portuguese");
	
    menu();
}

void menu(){
	int choice;
	
	do{
        printLogo();
		
		printf("\n1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Buscar Produto\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
				addProduct();
                break;
            case 2:
				listProducts();
                break;
            case 3:
				searchProduct();
                break;
            case 4:
                printf("\nSaindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
	}while(choice != 4);
}

int addProduct(){
	if(cod >= MAX){
		system("cls");
		printf("Cadastro cheio");
		system("cls");
		return;
	}
	
	Product item;
	
	system("cls");
	fflush(stdin);
	
	printf("Informe o nome do produto: ");
	  fgets(item.name, 50, stdin);
	  item.name[strcspn(item.name, "\n")] = '\0';
	  
	//GERAR CÓGIGO ALEATÓRIO // CODE = "CÓDIGO GERADO ALEATÓRIAMENTE"
	  
	printf("Informe a data de validade do produto (DATA/MÊS/ANO): ");
	  fgets(item.vality, 8, stdin);
	  item.vality[strcspn(item.vality, "\n")] = '\0';
	  
	fflush(stdin);
	
	printf("Informe o preço do produto: ");
	  scanf("%d", &item.price);
	  
	printf("Produto cadastrado com sucesso\n");
	  
	cod++;
	
	system("pause");
	system("cls");
}

int searchProduct(){
	printf("SearchProduct");
	system("pause");
	system("cls");
	return 0;
}

void listProducts(){
	printf("ListProduct");
	system("pause");
	system("cls");
}
