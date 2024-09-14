# Laboratoire 2

## Question 3: passer une fonction auxiliaire à un algorithme

### Contexte 

La STL contient une gamme considérable d'algorithmes qui permettent d'analyser les données contenues dans une structure de données de la STL.

Par exemple, la fonction sort permet de trier les éléments d'un vecteur ou d'un array.  La fonction max_element retourne un itérateur à l'élément maximal d'une collection quelconque.  

Ces algorithmes sont disponibles dans le header ``<algorithm>`` et sont en général appelés avec la syntaxe suivante:
```std::algorithme(début, fin, fonction_auxilaire)```.  Par-exemple si je veux trier le vecteur ```tugabudoires``` du début à la fin je vais appeler:
```std::sort(tugabudoires.begin(), tugabudoire.end(), comparateur)``` où ```comparateur``` est un objet appelable qui retourne ```true``` si son opérande de gauche vient avant son opérande de droite.  C'est donc une fonction booléenne prenant en paramètres deux objets du même type que les éléments de la collection ```tugabudoires```et qui les compare.

### Travail à faire

L'objectif du présent projet est de donner des exemples de comparateurs qui peuvent être passés à l'algorithme.

Vous noterez au passage que pour comparer deux objets Étudiants il faut avoir accès à leur attribut m_points.  Le concepteur du présent TD a pris un dangereux raccourci en mettant en commentaire la mention private des attributs d'Étudiant.  Dans le contexte, ceci est-il approprié?  Comment contourner cette difficulté?

Je vous propose en exemple 4 solutions au problème demandé:

- Solution 1: une simple Lambda-expression.  Il s'agit donc d'une fonction anonyme, créée ad hoc, qui ne pourra pas être appelée ailleurs.
- Solution 2: Un objet-fonction ou foncteur.  Il s'agit d'une classe qui surcharge l'opérateur ().  On peut donc créer des instances de cette classe qui agissent exactement comme des fonctions.
- Solution 3: Une fonction libre "<"
- Solution 4: Exploiter la surcharge de "<" qui est membre de Étudiant.

Pour chacune de ces solutions, vous devez:
-[ ] L'essayer
-[ ] Analyser son interaction avec les attributs private ou non
-[ ] L'appliquer comme template pour la question 4 de l'énoncé du labo.  Essayez autant que possible de décommenter le private dans ce code et trouver une solution qui fonctionne.