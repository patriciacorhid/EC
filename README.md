# EC
## Estructura de Computadores - 2º Curso

### Prácticas de la asignatura:

Contine una carpeta por cada práctica de la asignatura. En cada carpeta se encuentra el guión de la práctica,
así como el *PDF* con las respuestas a las preguntas del guión.

##### Primera práctica: 

Aprender a depurar programas con *objdump*. Los programas propuestos para depurarlos son `saludo.s` y `suma.s`.
Tras esto, realizar un programa ensambladorque sume una lista de N números en binario, sin signo, de 32bits. 
Dicho programa está incluido en la carpeta correspondiente con el nombre de `sumasinsigno.s`. Además, realizar
otro programa que sume una lista de N números en binario de 32bits con signo. El nombre se este programa es 
`sumaconsigno.s` Por último, implementar un programa para que calcule la media de lista de números anterior. 
Este programa es `media.s`.
Las preguntas del guión correspondientes a dichos programas están contestadas en el *PDF*.

##### Segunda práctica: 

Se realizarán dos programas diferentes, `paridad.c` y `popcount.c`. De ambos se realizarán varias versiones y se 
medirá el tiempo que tarda cada una en ejecutarse de media (se ejecutará 10 veces cada versión) cada una de las 
versiones con cada una de las optimizaciones diferentes, `-O0`, `-O1` y `-O2`.
Las preguntas del guión correspondientes a dichos programas están contestadas en el *PDF*.

###### Paridad:
  Suma las paridades de todos los elementos de un array, es decir, devuelve el número de elementos que tienen un número
  impar de unos en su forma binaria. 
  De este programa se realizaron 6 versiones diferentes.
  ***Un ejemplo:***
  Sea la lista de números (en decimal): 0, 1, 2, 3, 4.
  ```
	Número:   Paridad:
	0000          0
	0001          1
	0010          1
	0011          0
	0100          1
  ```
  El programa devuelve 3, que es el número de elementos de la lista con un número impar de unos en su forma binaria.
  
###### Popcount:
  Suma los pesos de Hamming (nº de bits activos) de todos los elementos de un array.
  impar de unos en su forma binaria.  
  De este programa se realizaron 5 versiones diferentes.
  
##### Tercera práctica: 
Implementar una *Bomba Digital*: Un programa que solicita una contraseña, simulando una explosión si
no es correcta o si se tarda demasiado tiempo en introducirla. Tras esto solicita un código, y el programa 
actuará igual que antes. Si se introducen ambos correctamente la *Bomba Digital* quedará desactibada.
En el *PDF* se explica como desactivar la Bomba Digital*, ***PCH_bomb***, sin saber la contraseña, cómo 
averiguar la contraseña y cómo desactivar la *Bomba Digital* de un compañero, la ***MaxiBomb***.
