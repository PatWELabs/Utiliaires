// CreerFichiersWebInitiaux.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <windows.h>
#include <iostream>
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

struct WebPage {
    char Chemin[260];
    char html[40];
    char nom[40];
    char titre[40];
    char css[40];
} wp;
int main()
{
    SetConsoleTitle("Createur de Fichiers Web Initiaux");
    char fichier[260];
    printf("Entrez le nom du fichier a creer : ");
    int a=scanf("%s",wp.nom);
    if (wp.nom[0] != NULL) {
        printf("Entrez le titre de la page Web (Ne doit pas contenir d'espaces): ");
        a=scanf("%s",wp.titre);
        printf("%s.html, %s.css ; Titre: %s", wp.nom, wp.nom, wp.titre);
        if (strlen(wp.titre)>0) {
            GetCurrentDirectory(0xFF, wp.Chemin);
            if (wp.Chemin[strlen(wp.Chemin)] != '\\') {
                strcat(wp.Chemin, "\\");
                sprintf(wp.html, "%s.html", wp.nom);
                FILE* f = fopen(wp.html, "w+");
                fprintf(f, "<!--\n* %s\n-->", wp.titre);   
                fprintf(f, "\n<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//fr-ca\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
                fprintf(f, "\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr-ca\" lang=\"fr-ca\">");
                fprintf(f, "\n<head>");
                fprintf(f, "\n    <meta charset=\"utf-8\" />");
                fprintf(f, "\n    <title>%s</title>",wp.titre);
                fprintf(f, "\n    <link rel=\"stylesheet\" href=\"./%s.css\" />",wp.nom);
                fprintf(f, "\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                fprintf(f, "\n</head>");
                fprintf(f, "\n    <body class=\"ConteneurGrandParent\">");
                fprintf(f, "\n          <h1> Genere par CreerFichiersWebInitiaux v:1.0</h1>");
                fprintf(f, "\n          <h2> © Patrice Waechter-Ebling 2022</h2>");
                fprintf(f, "\n    </body>");
                fprintf(f, "\n</html>");
                fclose(f);
                /*fin du fichier HTML*/
                sprintf(wp.css, "%s.css", wp.nom);
                f = fopen(wp.css, "w+");
                fprintf(f, "/*******************\n* %s\n****************/", wp.titre);
                /*integration Flexbox*/
                fprintf(f, "\nbody {");
                fprintf(f, "\n    position: fixed;");
                fprintf(f, "\n    padding: 0px;");
                fprintf(f, "\n    margin: 0px;");
                fprintf(f, "\n    width: 99.5%%;");
                fprintf(f, "\n    height: 99%%;");
                fprintf(f, "\n}");
                fprintf(f, "\n.ConteneurGrandParent{");
                fprintf(f, "\n    display: flex;");
                fprintf(f, "\n    flex-basis:90%%;");
                fprintf(f, "\n    flex-direction:row;");
                fprintf(f, "\n    font-size: 20px;");
                fprintf(f, "\n    box-sizing: border-box;");
                fprintf(f, "\n    justify-content:space-evenly;");
                fprintf(f, "\n    align-items: stretch;");
                fprintf(f, "\n    left:2.5%%;");
                fprintf(f, "\n    height:380px;");
                fprintf(f, "\n}");
                fprintf(f, "\n.ConteneurParent {");
                fprintf(f, "\n    display: flex;");
                fprintf(f, "\n    height: 97%%;");
                fprintf(f, "\n    flex-basis: 99%%;");
                fprintf(f, "\n    flex-direction: row;");
                fprintf(f, "\n    flex-wrap: wrap-reverse;");
                fprintf(f, "\n    align-items: stretch;");
                fprintf(f, "\n    align-content: flex-start;");
                fprintf(f, "\n    justify-content:space-evenly;");
                fprintf(f, "\n    border: 4px solid rgba(2, 59, 20, 0.815);");
                fprintf(f, "\n    text-align: center;");
                fprintf(f, "\n    box-sizing: border-box;");
                fprintf(f, "\n    margin: 5px;");
                fprintf(f, "\n    padding: 0.5%%;");
                fprintf(f, "\n}");
                fprintf(f, "\n.espacement_enfants{");
                fprintf(f, "\n    margin-left:5px;");
                fprintf(f, "\n    margin-bottom:5px;");
                fprintf(f, "\n    margin-top:5px;");
                fprintf(f, "\n}");
                fprintf(f, "\n.ItemFlexilbePetitEnfant{");
                fprintf(f, "\n    border:2px solid blue;");
                fprintf(f, "\n    flex-basis: 29.75%%;");
                fprintf(f, "\n    flex-shrink: 0;");
                fprintf(f, "\n    flex-grow:1;");
                fprintf(f, "\n}");
                fprintf(f, "\n.item1 {");
                fprintf(f, "\n    margin: 2px;");
                fprintf(f, "\n    padding: 3px;");
                fprintf(f, "\n    border-color: rgb(1, 170, 255);");
                fprintf(f, "\n    border-width:1px;");
                fprintf(f, "\n}");
                fclose(f);
                /* fin de l'integration flexbox*/ 
            }
        }

    }
}
