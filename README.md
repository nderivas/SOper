# Sistemas Operativos 🍴

###### Nicolás de Rivas Morillo - Universidad de Zaragoza - 3er cuatrimestre

---

- Práctica 3 (fork y exec):

**TP1.c**: Escribe un programa en C que cree un hijo. Además, antes de finalizar, cada uno de los procesos debe imprimir por pantalla:

1. Si es el padre o hijo
2. Su pid
3. El pid de su padre

**shpar.c**: Crea un programa que sea capaz de ejecutar dos aplicaciones en paralelo cuyos nombres recibirá en la línea de comandos. Las aplicaciones a ejecutar podrán tener parámetros y entre la especificación de la primera aplicación y la de la segunda habrá un símbolo +.
Ejemplo: `$hendrix> ./shpar ls -l *.c + ls -la`
Deberá ejecutar "ls -l \*.c" en paralelo con "ls -la".

- Práctica 4 (Señales):

**sendsignaltome.c**: Escribe un programa en C que se envíe a sí mismo un número de señal que le pasaremos como parámetro.
Ejemplo: `$hendrix> ./sendsignaltome 9` Se enviará a sí mismo la señal 9 (SIGKILL).

**duerme.h**: Con la ayuda del sistema de señales de UNIX, implementar la función duerme(segundos). Esta función mantendrá bloqueado al proceso que la llame durante el número de segundos pasado como parámetro.

**ej91.c**: Utilizar dicha función para realizar un programa que lance un mensaje a pantalla cada X segundos durante Y segundos. Para ello, ej91 ejecutará un fork()y el proceso hijo lanzará mensajes indefinidamente cada X segundos. Pasados Y segundos, el proceso padre suspenderá la ejecución del proceso hijo (SIGTSTP) durante Y segundos. Pasados estos últimos Y segundos, se retomará la ejecución del proceso hijo (SIGCONT), y pasados otros Y segundos el proceso padre matará al proceso hijo y finalizará. X e Y se pasarán a ej91 como parámetros:
Ejemplo: `./ej91 2 7`

**ej1001.c**: Modificar ej1001.c de forma que el proceso padre quede protegido contra las señales SIGINT y SIGQUIT y los procesos hijos no.
