# .csv-Parser
En este repositorio subo el ejercicio 12 de la practica 6.

# Enunciado

a) Realice un programa que permita generar un índice para acceder por DNI de manera eficiente a
la información del archivo de texto “personas.csv”. Este archivo contiene los datos de una persona
(identificador, dni, nombre, apellido, correo, ciudad, país y trabajo que desarrolla) en formato CSV.
  El índice debe generarse en memoria y estar ordenado por DNI para finalmente almacenarlo en el
archivo binario “personas.idx”. Este archivo binario deberá tener por cada línea del archivo
“personas.csv” una entrada que contenga el DNI de la persona junto con la posición absoluta dentro
del archivo a los datos asociados a dicho DNI. Diseñe una estructura de datos adecuada para el
índice y tenga en cuenta al momento de generarlo que la primera línea del archivo CSV es de
encabezado.

b) Realice un programa que muestre en pantalla toda la información de una persona a través de un
DNI ingresado por teclado. Si la persona no existe deberá informar el error.
Tenga en cuenta para la implementación:
• Utilizar una estructura de datos adecuada que permita tener el índice completamente en
memoria.
• Implemente para la búsqueda una función que realice una búsqueda dicotómica.
• Implemente el siguiente prototipo para la función de búsqueda:
int buscar(FILE* personas, Indice indice, int dni, persona * persona)
donde:
• personas es el descriptor del archivo “personas.csv”
• indice es la estructura de datos con la información del archivo “personas.idx”.
• dni es el nro de dni de la persona a buscar
• persona es una estructura con los datos con la información asociada al dni de la
persona.
• El valor de retorno es 0 sino encuentra a la persona y 1 en caso contrario. 

# Como ejecutar
  Entrar en la carpeta ./Debug y ejecutar 5.12.exe
# Como compilar
  En el directorio raiz, ejecutar el comando: 
  ```
    "gcc main.c -o 5.12"
  ```
  
