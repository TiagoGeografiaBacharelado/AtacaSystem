#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>

#define VERMELHO     "\x1b[31m"
#define RESET   "\x1b[0m"

void login(){
	
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("");
	printf("\t\t\t\t#########################################################\n");
    printf("\t\t\t\t#                                                       #\n");
	printf("\t\t\t\t#             Ben-vindo ao AtacaSystem                  #\n");
	printf("\t\t\t\t#                                                       #\n");
    printf("\t\t\t\t#########################################################\n");

        printf("\n\t\t\t\t                   1- Login                      \n");
        printf("\t\t\t\t                   2- Desenvolvedores                             \n");
        printf("\t\t\t\t                   3- Sair                        \n");
        printf("\t\t\t\t                                                       \n");
        printf("\t\t\t\t                   Opção: ");
}
