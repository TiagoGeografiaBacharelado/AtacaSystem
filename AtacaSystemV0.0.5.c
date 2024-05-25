#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

#include "AtacaSystemMenu.c"

typedef struct{
	char name[50];
	char code[30];
	char vality[8];
	int price;
}Product;

void menu(), listProducts();
int addProduct(), searchProduct();

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printLogo();
    menu();
}

void menu(){
	int choice;
	
	do{
        printf("Escolha uma opção: \n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Buscar Produto\n");
        printf("4 - Sair\n");
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
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
	}while(choice != 4);
}

int addProduct(){
	printf("AddProduct");
	system("pause");
	system("cls");
	return 0;
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
