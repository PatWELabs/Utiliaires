#include <stdio.h>
#include <conio.h>
void main(){
	char drv[80];
	int x=0,y=0;
	printf("%c Patrice Waechter-Ebling 2010\n\nSelectionnez un code barre à l'aide de la douchette: \t",184);
	scanf("%s",&drv);
	x=strlen(drv);
	switch(x+1){
		case 13:printf("Code type EAN13\n"); break;
		case 8:printf("Code type EAN8\n");break;
		case 39:printf("Code type 3 de 9 (39)\n");break;
	}
	for(y=0; y<x; y++){
		printf("%c",drv[y+10]);
	}
	printf("\nDonnees recues: %s\n Hexadecimal : 0x%x\n Decimal : %d\n Taille de la chaine recue %d\n\n\tAppuyez une touche pour quitter ...",drv,strupr(drv),drv,x);
	getch();
}
