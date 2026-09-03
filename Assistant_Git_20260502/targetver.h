// Ce code source des exemples MFC illustre l'utilisation de l'interface utilisateur Microsoft Office Fluent MFC 
// (interface utilisateur "Fluent UI"). Il est fourni uniquement en tant que référence complémentaire du 
// Guide de référence Microsoft Foundation Classes et de la documentation électronique associée 
// inclus avec les logiciels de la bibliothèque MFC C++.  
// Les termes du contrat de licence pour la copie, l'utilisation ou la distribution de l'interface utilisateur Fluent sont disponibles séparément.  
// Pour en savoir plus sur notre programme de licence de l'interface utilisateur Fluent, visitez 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// Tous droits réservés.

#pragma once

// Les macros suivantes définissent la plateforme minimale requise. La plateforme minimale requise
// est la version de Windows, Internet Explorer etc. qui dispose des fonctionnalités nécessaires pour exécuter 
// votre application. Les macros fonctionnent en activant toutes les fonctionnalités disponibles sur les versions de la plateforme jusqu'à la 
// version spécifiée.

// Modifiez les définitions suivantes si vous devez cibler une plateforme avant celles spécifiées ci-dessous.
// Reportez-vous à MSDN pour obtenir les dernières informations sur les valeurs correspondantes pour les différentes plateformes.
#ifndef WINVER                          // Spécifie que la plateforme minimale requise est Windows Vista.
#define WINVER 0x0600           // Attribuez la valeur appropriée à cet élément pour cibler d'autres versions de Windows.
#endif

#ifndef _WIN32_WINNT            // Spécifie que la plateforme minimale requise est Windows Vista.
#define _WIN32_WINNT 0x0600     // Attribuez la valeur appropriée à cet élément pour cibler d'autres versions de Windows.
#endif

#ifndef _WIN32_WINDOWS          // Spécifie que la plateforme minimale requise est Windows 98.
#define _WIN32_WINDOWS 0x0410 // Attribuez la valeur appropriée à cet élément pour cibler Windows Me ou version ultérieure.
#endif

#ifndef _WIN32_IE                       // Spécifie que la plateforme minimale requise est Internet Explorer 7.0.
#define _WIN32_IE 0x0700        // Attribuez la valeur appropriée à cet élément pour cibler d'autres versions d'Internet Explorer.
#endif

