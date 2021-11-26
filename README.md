# Filter
Programme qui applique des filtres aux BMP

l'image :

La façon la plus simple de représenter une image est peut-être d'utiliser une grille de pixels (c'est-à-dire des points), dont chacun peut être d'une couleur différente. Pour les images en noir et blanc, nous avons donc besoin de 1 bit par pixel, car 0 pourrait représenter le noir et 1 pourrait représenter le blanc

En ce sens, alors, une image n'est qu'un bitmap (c'est-à-dire une carte de bits). Pour des images plus colorées, vous avez simplement besoin de plus de bits par pixel. Un format de fichier (comme BMP , JPEG ou PNG ) qui prend en charge la « couleur 24 bits » utilise 24 bits par pixel. (BMP prend en charge les couleurs 1, 4, 8, 16, 24 et 32 ​​bits.)

Un BMP 24 bits utilise 8 bits pour signifier la quantité de rouge dans la couleur d'un pixel, 8 bits pour signifier la quantité de vert dans la couleur d'un pixel et 8 bits pour signifier la quantité de bleu dans la couleur d'un pixel. Si vous avez déjà entendu parler de la couleur RVB, eh bien, vous l'avez : rouge, vert, bleu.

Si les valeurs R, G et B d'un pixel dans un BMP sont, disons, 0xff, 0x00, et 0x00en hexadécimal, ce pixel est purement rouge, car 0xff(autrement connu comme 255en décimal) implique "beaucoup de rouge", tandis que 0x00et 0x00implique « pas de vert » et « pas de bleu », respectivement.

*_qu'en est-il du filtrage ?*

Que signifie même filtrer une image ? Vous pouvez penser à filtrer une image comme à prendre les pixels d'une image originale et à modifier chaque pixel de manière à ce qu'un effet particulier soit apparent dans l'image résultante.

DETAILS PLUS TECHNIQUE :

*_Nuance de gris* :

Un filtre commun est le filtre "niveaux de gris", où nous prenons une image et voulons la convertir en noir et blanc. Comment ça marche?

Rappelez-vous que si les valeurs rouge, verte et bleue sont toutes définies sur 0x00(hexadécimal pour 0), alors le pixel est noir. Et si toutes les valeurs sont définies sur 0xff(hexadécimal pour 255), alors le pixel est blanc. Tant que les valeurs rouge, verte et bleue sont toutes égales, le résultat sera des nuances de gris variables le long du spectre noir-blanc, avec des valeurs plus élevées signifiant des nuances plus claires (plus proches du blanc) et des valeurs plus faibles signifiant des nuances plus foncées (plus proches de le noir).

Ainsi, pour convertir un pixel en niveaux de gris, nous devons simplement nous assurer que les valeurs rouge, verte et bleue sont toutes identiques. Mais comment savoir quelle valeur les rendre ? Eh bien, il est probablement raisonnable de s'attendre à ce que si les valeurs d'origine rouge, vert et bleu étaient toutes assez élevées, la nouvelle valeur devrait également être assez élevée. Et si les valeurs d'origine étaient toutes faibles, la nouvelle valeur devrait également être faible.

En fait, pour garantir que chaque pixel de la nouvelle image a toujours la même luminosité ou obscurité générale que l'ancienne image, nous pouvons prendre la moyenne des valeurs rouge, verte et bleue pour déterminer quelle nuance de gris créer le nouveau pixel.

Si vous appliquez cela à chaque pixel de l'image, le résultat sera une image convertie en niveaux de gris.

*_Reflexion* :

Certains filtres peuvent également déplacer des pixels. La réflexion d'une image, par exemple, est un filtre où l'image résultante est ce que vous obtiendriez en plaçant l'image originale devant un miroir. Ainsi, tous les pixels sur le côté gauche de l'image devraient se retrouver sur la droite, et vice versa.

Notez que tous les pixels originaux de l'image originale seront toujours présents dans l'image réfléchie, c'est juste que ces pixels peuvent avoir été réorganisés pour être à un endroit différent dans l'image.

*_Brouiller* :

Il existe plusieurs façons de créer l'effet de flou ou d'adoucissement d'une image. Pour ce problème, nous utiliserons le "box blur", qui fonctionne en prenant chaque pixel et, pour chaque valeur de couleur, en lui donnant une nouvelle valeur en faisant la moyenne des valeurs de couleur des pixels voisins.

_Considerons une matrice 4 x 4 rempli de valeur allans de 1 à 16:_

La nouvelle valeur de chaque pixel serait la moyenne des valeurs de tous les pixels qui se trouvent dans une ligne et une colonne du pixel d'origine (formant une boîte 3x3). Par exemple, chacune des valeurs de couleur du pixel 6 serait obtenue en faisant la moyenne des valeurs de couleur d'origine des pixels 1, 2, 3, 5, 6, 7, 9, 10 et 11 (notez que le pixel 6 lui-même est inclus dans le moyenne). De même, les valeurs de couleur pour le pixel 11 seraient obtenues en faisant la moyenne des valeurs de couleur des pixels 6, 7, 8, 10, 11, 12, 14, 15 et 16.

Pour un pixel le long du bord ou du coin, comme le pixel 15, nous chercherions toujours tous les pixels d'une ligne et d'une colonne : dans ce cas, les pixels 10, 11, 12, 14, 15 et 16.

*_Bord* :

Dans les algorithmes _d'intelligence artificielle_ pour le traitement d'images, il est souvent utile de détecter les contours d'une image : des lignes dans l'image qui créent une frontière entre un objet et un autre. Une façon d'obtenir cet effet est d'appliquer l' opérateur Sobel à l'image.

Comme le flou d'image, la détection des contours fonctionne également en prenant chaque pixel et en le modifiant en fonction de la grille de pixels 3x3 qui entoure ce pixel. Mais au lieu de simplement prendre la moyenne des neuf pixels, l'opérateur Sobel calcule la nouvelle valeur de chaque pixel en prenant une somme pondérée des valeurs des pixels environnants. Et puisque les bords entre les objets peuvent avoir lieu à la fois dans le sens vertical et dans le sens horizontal, vous calculerez en fait deux sommes pondérées : une pour détecter les bords dans la direction x et une pour détecter les bords dans la direction y. En particulier, vous utiliserez les deux « noyaux » suivants :

considerons une premiere matrice rempli par ligne  de la maniere suivante : Gx = ((-1, 0, 1);(-2, 0, 2),(-1, 0, 1)) tel que des zero  sur la colonne 2
considerons une premiere matrice rempli par ligne  de la maniere suivante : Gy = ((-1, -2, -1);(0, 0, 0),(1, 2, 1)) tel que des zero sur la ligne 2

Comment interpréter ces noyaux ? En bref, pour chacune des trois valeurs de couleur pour chaque pixel, nous calculerons deux valeurs Gxet Gy. Pour calculer Gxla valeur du canal rouge d'un pixel, par exemple, nous allons prendre les valeurs rouges d'origine pour les neuf pixels qui forment une boîte 3x3 autour du pixel, les multiplier chacune par la valeur correspondante dans le Gxnoyau, et prendre la somme des valeurs résultantes.

Pourquoi ces valeurs particulières pour le noyau ? Dans la Gxdirection, par exemple, nous multiplions les pixels à droite du pixel cible par un nombre positif et multiplions les pixels à gauche du pixel cible par un nombre négatif. Quand on fait la somme, si les pixels de droite sont d'une couleur similaire aux pixels de gauche, le résultat sera proche de 0 (les nombres s'annulent). Mais si les pixels de droite sont très différents des pixels de gauche, alors la valeur résultante sera très positive ou très négative, indiquant un changement de couleur qui est probablement le résultat d'une frontière entre les objets. Et un argument similaire est vrai pour le calcul des arêtes dans la ydirection.

En utilisant ces noyaux, nous pouvons générer une valeur Gxet Gypour chacun des canaux rouge, vert et bleu d'un pixel. Mais chaque canal ne peut prendre qu'une valeur, pas deux : nous avons donc besoin d'un moyen de combiner Gxet Gyen une seule valeur. L'algorithme du filtre de Sobel combine Gxet Gyen une valeur finale en calculant la racine carrée de Gx^2 + Gy^2. Et puisque les valeurs de canal ne peuvent prendre que des valeurs entières de 0 à 255, assurez-vous que la valeur résultante est arrondie à l'entier le plus proche et plafonnée à 255 !

Et qu'en est-il de la gestion des pixels au bord, ou dans le coin de l'image ? Il existe de nombreuses façons de gérer les pixels au bord, mais pour les besoins de ce problème, nous vous demanderons de traiter l'image comme s'il y avait une bordure noire solide de 1 pixel autour du bord de l'image : par conséquent, essayer d'accéder un pixel au-delà du bord de l'image doit être traité comme un pixel noir uni (valeurs de 0 pour chacun du rouge, du vert et du bleu). Cela ignorera effectivement ces pixels de nos calculs de Gxet Gy.
