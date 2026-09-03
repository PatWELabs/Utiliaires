# Convertion de Virgule flottante 32/64bit vers décimal! 
### Applications.Maths.Appliquées.Info v1.01 
---
Représentation [32 ou 64] bits à détection automatique 
  PWE?> 11101010010101100000000000000000 
   32 octets entrés Normalisation IEEE 754 1|11010100|10101100000000000000000 
1. Table des exposants générée 
2. Valeur négative Exposant en binaire par excés[127] : 10101001 
	* Table32 pos: 1 actif:1 ==>128 
	* Table32 pos: 2 actif:1 ==>64 
	* Table32 pos: 3 actif:0 ==>0 
	* Table32 pos: 4 actif:1 ==>16 
	* Table32 pos: 5 actif:0 ==>0 
	* Table32 pos: 6 actif:1 ==>4 
	* Table32 pos: 7 actif:0 ==>0 
	* Table32 pos: 8 actif:0 ==>0 
3. Retrait de l'excés = 215-127=88 
4. Exposant par excés 88 
5. Total décimal: 0.00000 
6. Forme exponentielle :(1,)[2]x2exp88 
7. Résultat: 1 Convertion Table 32bits vers Norme IEEE 754  ==> ** 1|11010100|10101100000000000000000 **

### L'agorithme de sauvegarde est un **prototype** 
Il est probable que le texte généré nse soit pas alligné correctement
