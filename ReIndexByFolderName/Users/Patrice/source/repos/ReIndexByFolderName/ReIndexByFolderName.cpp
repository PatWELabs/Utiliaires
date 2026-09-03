// ReIndexByFolderName.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
HANDLE hStdout, hStdin; 
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
WORD wOldColorAttrs; 
char curdir[260];
char szFolderName[128];
void logo(){
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED |FOREGROUND_BLUE|  FOREGROUND_INTENSITY);
	
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",     201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
	printf("\t%c                                                               %c\n",     186,186);
	printf("\t%c    %c Patrice Wächter-Ebling 2017-2018              v:1.0.0    %c\n",     186,64,186);
	printf("\t%c    Renomme le contenu d'un dossier en indexant les fichiers   %c\n",     186,186);
	printf("\t%c    Filtre JPEG v:0.97                                         %c\n",     186,186);
	printf("\t%c    Filtre FolderName v:0.98.32                                %c\n",     186,186);
	printf("\t%c                                                               %c\n",     186,186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",     200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
	SetConsoleTextAttribute(hStdout,wOldColorAttrs);
}

void ErreurData(){
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED |  FOREGROUND_INTENSITY);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",     201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
	printf("\t%c                                                               %c\n",     186,186);
	printf("\t%c    Parmètre du dossier manquant                               %c\n",     186,186);
	printf("\t%c                                                               %c\n",     186,186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",     200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
	SetConsoleTextAttribute(hStdout,wOldColorAttrs);
}

void RecupFolderName(char* Path){
	strcpy(szFolderName,PathFindFileName(Path) );
}
void RenameFile(char* Path,char* File,int ListIndex){
	char src[256],cbl[256];
	sprintf(src,"%s\\%s",Path,File);
	sprintf(cbl,"%s\\%s %.3d.jpg",Path,szFolderName,ListIndex);
	MoveFile(src,cbl);
}
void ScanFolder(char* Path){
	SetCurrentDirectory(Path);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind; 
	int brc=1;
	hFind = FindFirstFile("*.jp*", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
	  printf ("FindFirstFile failed (%d)\n", GetLastError());
	  return;   // and return
	}  else {
		printf ("%2d: The first file found is %s\n",brc, FindFileData.cFileName);
		RenameFile(Path,FindFileData.cFileName,brc);
		brc++;
	} 	do	{
		printf ("%2d: The next file found is  %s\n", brc, FindFileData.cFileName);
		RenameFile(Path,FindFileData.cFileName,brc);
		brc++;
	}
	while(FindNextFile(hFind,&FindFileData));
	FindClose(hFind);
}

int main(int argc, char* argv[])
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo); 
	wOldColorAttrs = csbiInfo.wAttributes; 
	logo();
	if(argc<2){
		ErreurData(); return -1;
		}else{
		strcpy(curdir,argv[1]);
		RecupFolderName(curdir);
		printf("Dossier : %s\n",szFolderName);
		ScanFolder(curdir);
		}
return 0;
}
