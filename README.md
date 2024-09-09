# M1-projects-simulation-numerique

Ce présent projet donne un survol partiel de mon étude consistant à simuler numériquement un dispositif en C++. J'ai développé un programme qui calcule les solutions de l'équation de la chaleur, laquelle modélise le dispositif de refroidissement en fonction du temps, ainsi que sans la variable temporelle, en utilisant la méthode des différences finies. Cette équation différentielle est donnée par la formule suivante :

$$
\rho Cp \frac{\partial T}{\partial t} - \kappa \frac{\partial^2 T}{\partial x^2} + \frac{hcp}{S} (T - Te) = 0
$$

Ce dispositif supplémentaire, représenté avec la figure ci-dessous, permet d’augmenter la surface d’échange avec le flux d’air et d’ainsi refroidir plus efficacement le composant électronique.
<p align="center">
  <img src="images/ref.png" alt="Dispositif de refroidissement" width="500"/>
</p>
Ce travail est divisé en quatre parties :
Dans la première partie, nous présenterons un programme en C++ qui calcule le pas de temps et la matrice associée au problème. Ensuite, j'ai calculé les solutions en utilisant la méthode de décomposition LU. Nous examinerons également les erreurs entre la solution numérique et la solution exacte du modèle stationnaire.

<p align="center">
  <img src="images/ap1.png" alt="D" width="45%" style="margin-right: 10px;"/>
  <img src="images/ap2.png" alt="E" width="45%"/>
</p>

<p align="center">
  Erreur avec Lx = 40mm &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Erreur avec Lx = 80mm
</p>

- Dans la deuxième partie, nous examinerons les solutions en 3D et les visualiserons sur Paraview 

<p align="center">
  <img src="images/2.png" alt="Image 2" width="45%" style="margin-right: 10px;"/>
  <img src="images/3.png" alt="Image 3" width="45%"/>
</p>

<p align="center">
  <img src="images/4.png" alt="Image 4" width="45%" style="margin-right: 10px;"/>
  <img src="images/5.png" alt="Image 5" width="45%"/>
</p>

<p align="center"><b>Figure:</b> Résultats de la solution en 3D</p>

	  	 		
	  	 		
- Dans la troisième partie, nous procédons de la même manière, mais cette fois pour le cas instationnaire en 1D. Nous examinerons également les erreurs entre la solution numérique et la solution exacte du modèle instationnaire.

<p align="center">
  <img src="images/T.png" alt="Flux de chaleur constant" width="45%" style="margin-right: 10px;"/>
  <img src="images/x0.png" alt="Avec activation/désactivation du flux de chaleur" width="45%"/>
</p>

<p align="center">
  Flux de chaleur constant &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Avec activation/désactivation du flux de chaleur
</p>
        |

- Dans la quatrième partie, nous analyserons les solutions en 3D en fonction du temps et les visualiserons sur Paraview


<p align="center">
  <img src="images/c.png" alt="Image c" width="45%" style="margin-right: 10px;"/>
  <img src="images/d.png" alt="Image d" width="45%"/>
</p>

<p align="center">
  <img src="images/e.png" alt="Image e" width="45%" style="margin-right: 10px;"/>
  <img src="images/f.png" alt="Image f" width="45%"/>
</p>

<p align="center"><strong>Figure:</strong> Résultats de la solution en 3D</p>
