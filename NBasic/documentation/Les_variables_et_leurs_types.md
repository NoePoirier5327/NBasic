# Les types
Le langage NotSoBasic a à sa disposition quatre types primitifs :
- le type `integer` qui représente les entiers
- le type `boolean` qui représente les booléens
- le type `real` qui représente l'ensemble des réels
- le type `string` qui représente les caractères et les chaînes de caractères
Plus tard il y aura la possibilité de définir soit même ses propres types.
# Les variables
## La syntaxe de déclaration
Le mot clé de déclaration d'une variable est `dim`.
Son utilisation est la suivante `dim nom_de_variable as type`.
Dans un programme, on peut donc définir et utiliser une variable de la manière suivante : 
```NBasic
import console

program
	dim ma_variable as string ; On déclare une variable de type string en mémoire
	ma_variable = "Bonjour" ; On lui attribue une valeur
	console.disp(ma_variable) ; On affiche sa valeur associée
end
```
## Les opérations en fonction des types
- Sur les types entiers et réels, les opérations arithmétique classique sont disponibles (addition, soustraction, multiplication, division et modulo). Le reste des opérations plus poussées est disponible sur la librairie standard [math](la_bibliotheque_standard/Les_mathematiques.md). Sachant que les opérateurs couplés à des opérations d'assignation sont disponibles sous le même format que `python`.
- Sur les booléens, seulement les opérations booléennes primaires ainsi que les comparaisons sont autorisées.
- Sur les chaînes de caractères, la seule opération d'autoriser est celle de concaténation correspondant au "+".

Exemple :
```NBasic
import console

program
	; Attribution et modification d'un entier et un réel

	dim a as integer
	dim b as real
	
	a = 9
	b = 6.7
	b -= a / 7
	
	console.disp(b)
	
	; Attribution et comparaison de deux booléens
	
	dim ok as boolean
	dim continue as boolean
	
	ok = 7 == 8
	continue = ok and false
	
	console.disp(continue)
	
	; Déclaration et concaténation de deux chaînes de caractères
	dim name as string
	dim city as string
	
	name = "Jeffrey"
	city = name + " New York"
	
	console.disp(city)
end
```
