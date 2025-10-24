# Syntaxe
Les structures conditionnelles se construisent de la manière suivante en NBasic.

``` NBasic
if <condition> then
	<expression>
else if <condition> then
	<expression>
else
	<expression>
end
```
Tableau de syntaxe des opérateurs de comparaison :
| Syntaxe   | Significations                                                          |
| --------- | ----------------------------------------------------------------------- |
| `a == b`  | a est égal à b                                                          |
| `a != b`  | a est différent de b                                                    |
| `a < b`   | a est inférieur à b, ne fonctionne que sur des types numériques         |
| `a > b`   | a est supérieur à b, ne fonctionne que sur des types numériques         |
| `a <= b`  | a est inférieur ou égal à b, ne fonctionne que sur des types numériques |
| `a >= b`  | a est supérieur ou égal à b, ne fonctionne que sur des types numériques |
| `!a`      | non a, ne fonctionne qu'avec des expressions booléennes                 |
| `a and b` | a et b, ne fonctionne qu'avec des expressions booléennes                |
| `a or b`  | a ou b, ne fonctionne qu'avec des expressions booléennes                |

Exemple:
```NBasic
import console
import random

program
	dim a as integer
	dim b as integer
	
	; On tire un nombre entier aléatoire entre 1 et 10
	a = random.int(1, 100)
	
	; On demande à l'utilisateur de le deviner
	console.disp("Devinez le nombre tiré aléatoirement entre 1 et 100 : ")
	console.prompt(b)
	
	; On vérifie s'il a gagner
	if a == b then
		console.disp("Bravo !!! Tu as trouvé le nombre aléatoire.\n")
	else
		console.disp("Dommage ! Mếme joueur essaie encore.\n")
	end
end
```
