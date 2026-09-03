================================================================================
    BIBLIOTHÈQUE MFC (MICROSOFT FOUNDATION CLASS) : Vue d'ensemble du projet 
    Assistant_Git
===============================================================================

L'Assistant Application a créé cette application Assistant_Git pour
vous. Cette application ne montre pas seulement l'essentiel de l'utilisation de 
Microsoft Foundation Classes, mais constitue également un point de départ pour 
l'écriture de votre application.

Ce fichier contient un résumé du contenu de chacun des fichiers qui constituent
votre application Assistant_Git.

Assistant_Git.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à 
    l'aide d'un Assistant Application.
    Il contient des informations sur la version de Visual C++ utilisée pour 
    générer le fichier ainsi que des informations relatives aux plateformes, 
    configurations et fonctionnalités projet que vous avez sélectionnées dans 
    l'Assistant Application.

Assistant_Git.h
    Il s'agit du fichier d'en-tête principal de l'application. Il inclut 
    d'autres en-têtes spécifiques au projet (dont Resource.h) et déclare la 
    classe d'application CAssistant_GitApp.

Assistant_Git.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CAssistant_GitApp.

Assistant_Git.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows utilisées 
    par le programme. Il inclut les icônes, les bitmaps et les curseurs qui 
    sont stockés dans le sous-répertoire RES. Ce fichier peut être directement 
    modifié dans Microsoft Visual C++. Vos ressources de projet se trouvent 
    dans 1036.

res\Assistant_Git.ico
    Il s'agit du fichier icône utilisé comme icône de l'application. Cette 
    icône est incluse par le fichier de ressources principal 
    Assistant_Git.rc.

res\Assistant_Git.rc2
    Ce fichier contient les ressources qui ne sont pas modifiées par 
    Microsoft Visual C++. Vous devez placer toutes les ressources non 
    modifiables par l'éditeur de ressources dans ce fichier.

Assistant_Git.reg
    Il s'agit d'un exemple de fichier .reg qui vous indique le type de 
    paramètres d'inscription que l'infrastructure définit pour vous. Vous 
    pouvez l'utiliser comme un fichier .reg
    pour votre application ou simplement le supprimer et conserver 
    l'inscription par défaut RegisterShellFileTypes.


/////////////////////////////////////////////////////////////////////////////

Pour la fenêtre frame principale :
    Le projet inclut une interface MFC standard.

MainFrm.h, MainFrm.cpp
    Ces fichiers contiennent la classe de frame CMainFrame, qui 
    est dérivée de
    CMDIFrameWnd et qui contrôle toutes les fonctionnalités du frame MDI.

res\Toolbar.bmp
    Ce fichier bitmap permet de créer des images en mosaïque pour la barre 
    d'outils.
    La barre d'outils et la barre d'état initiales sont construites dans la 
    classe CMainFrame. Modifiez le bitmap de cette barre 
    d'outils à l'aide de l'éditeur de ressources et mettez à jour le tableau 
    IDR_MAINFRAME TOOLBAR dans Assistant_Git.rc afin d'ajouter des 
    boutons à la barre d'outils.
/////////////////////////////////////////////////////////////////////////////

Pour la fenêtre frame enfant :

ChildFrm.h, ChildFrm.cpp
    Ces fichiers définissent et implémentent la classe 
    CChildFrame, qui prend en charge les fenêtres enfants dans 
    une application MDI.

/////////////////////////////////////////////////////////////////////////////

L'Assistant Application crée un type de document et un affichage :

Assistant_GitDoc.h, Assistant_GitDoc.cpp - document
    Ces fichiers contiennent votre classe CAssistant_GitDoc. Modifiez ces 
    fichiers pour ajouter vos données de document spéciales et implémenter 
    l'enregistrement et le chargement de fichiers (via 
    CAssistant_GitDoc::Serialize).
    Le document contiendra les chaînes suivantes :
        Extension de fichier :         git
        ID du type de fichier :        AssistantGit.Document
        Titre du frame principal :     Assistant_Git
        Nom du type de document :      Assistant_Git
        Nom du filtre :                Assistant_Git Files (*.git)
        Nouveau nom court du fichier : Assistant_Git
        Nom long du type de fichier :  Assistant_Git.Document

Assistant_GitView.h, Assistant_GitView.cpp - affichage du document
    Ces fichiers contiennent votre classe CAssistant_GitView.
    Les objets CAssistant_GitView permettent d'afficher des objets 
    CAssistant_GitDoc.

res\Assistant_GitDoc.ico
    Il s'agit du fichier icône utilisé comme icône des fenêtres enfants MDI de 
    la classe CAssistant_GitDoc. Cette icône est incluse par le fichier de 
    ressources principal Assistant_Git.rc.




/////////////////////////////////////////////////////////////////////////////

Autres fonctionnalités :

Contrôles ActiveX
    L'application prend en charge l'utilisation de contrôles ActiveX.

/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers permettent de générer un fichier d'en-tête précompilé (PCH) 
    nommé Assistant_Git.pch et un fichier de types précompilé nommé 
    StdAfx.obj.

Resource.h
    Il s'agit du ficher d'en-tête standard, qui définit les nouveaux ID de 
    ressources.
    Microsoft Visual C++ lit et met à jour ce fichier.

/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise "TODO:" pour indiquer les parties du code 
source que vous devez ajouter ou personnaliser.

Si votre application utilise une bibliothèque MFC dans une DLL partagée, vous 
devez redistribuer les DLL MFC. Si votre application utilise une autre langue 
que celle définie dans les paramètres régionaux du système d'exploitation, vous 
devez également redistribuer les MFC90XXX.DLL des ressources localisées 
correspondantes.
Pour plus d'informations sur ces deux rubriques, consultez la section relative 
à la redistribution des applications Visual C++ dans la documentation MSDN.

/////////////////////////////////////////////////////////////////////////////
