#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	unsigned int dni;
	char apellido[30];
	char nombre[30];
	char trabajo[45];
	char correo[100];
	char ciudad[30];
	char pais[30];
} persona;

typedef struct {
	unsigned int dni;
	unsigned int index;
} dato_idx;

typedef struct {
	dato_idx *dato;
	unsigned int length;
} Indice;

void bubbleSort(dato_idx *v, unsigned int size) {
	dato_idx aux;
	
	int i = 0, j = size;
	
	while (j) {
		for (i = 0; i < j; i++) {
			if (v[i].dni > v[i+1].dni) {
				aux = v[i];
				v[i] = v[i+1];
				v[i+1] = aux;
			}
		}
		j--;
	}
}

void ordenarArchivo(FILE *file) {
	fseek(file, 0, SEEK_SET);
	fseek(file, 0, SEEK_END);
	
	const int length = ftell(file) / sizeof(dato_idx);
	int i = 0;
	
	dato_idx v[length], *aux;
	
	aux = malloc(sizeof(dato_idx));
	
	fseek(file, 0, SEEK_SET);
	while (!feof(file)) {
		fread(aux, sizeof(dato_idx), 1, file);
		v[i++] = *aux;
		//printf("INDEX: %d\n",v[i-1].index);
	}
	
	bubbleSort(v, length); // Se podria implementar un algoritmo mas eficiente.
	
	fseek(file, 0, SEEK_SET);
	for (i = 0; i < length; i++) {
		fwrite(&v[i], sizeof(dato_idx), 1, file);
		//printf("INDEX: %10d DNI: %10d\n", v[i].index, v[i].dni);
	}
	
	fseek(file, 0, SEEK_SET);
	//printf("Cantidad personas: %d\n", length);
}

Indice* obtenerIndice(FILE *file) {
	fseek(file, 0, SEEK_SET);
	
	fseek(file, 0, SEEK_END);
	const int length = ftell(file) / sizeof(dato_idx);
	fseek(file, 0, SEEK_SET);
	
	Indice *indice = malloc(sizeof(Indice));
	indice->length = length;
	
	dato_idx *aux;
	aux = malloc(sizeof(dato_idx) * length);
	
	int pos = 0;
	while (!feof(file)) {
		fread(&aux[pos++], sizeof(dato_idx), 1, file);
	}
	
	indice->dato = aux;
	
	return indice;
}

int buscar(FILE *file, Indice indice, int DNI, persona *p) {
	int seEncontro = 0;
	int izquierda = 0, mitad, derecha = indice.length - 1;
	
	while (!seEncontro && izquierda <= derecha) {
		mitad = (izquierda + derecha) / 2;
		if (indice.dato[mitad].dni == DNI)
			seEncontro = 1;
		else if (indice.dato[mitad].dni < DNI) {
			izquierda = mitad + 1;
		} else {
			derecha = mitad - 1;
		}
	}
	
	if (seEncontro) { // Si se encontro el DNI, asignar *p

		fseek(file, indice.dato[mitad].index, SEEK_SET);
		fscanf(file, "%d;%d;%s;%s;%s;%s;%s;%s;%*[^\n]\n", &p->id, &p->dni, p->apellido, p->nombre, p->trabajo, p->correo, p->ciudad, p->pais);
		
		// printf("ID: %d DNI: %d\n", p->id, p->dni);
	}
	
	
	
	return seEncontro;
}

int main() {
	FILE *file0, *file1;
	
	// Abro los archivos
	file0 = fopen("personas.csv", "r"); // Abre un archivo para lectura
	file1 = fopen("personas.idx", "wb+"); // Crea un archivo para lectura y escritura.
	
	if (!file0 || !file1) {	// Si no se pudo abrir el archivo 0 o el archivo 1
		printf("No se pudo abrir el archivo.\n"); // Imprimir mensaje de error
		return 1; // Retornar 1 y cerrar el programa
	}
	
	while (fgetc(file0) != '\n'); // Me salteo el encabezado
	
	persona *aux0;
	aux0 = malloc(sizeof(persona));
	
	dato_idx *aux1;
	aux1 = malloc(sizeof(dato_idx));
	
	int dsplz_total = 0; // Desplazamiento total
	
	// Lectura del "personas.csv"
	while (!feof(file0)) { 
		dsplz_total = ftell(file0);// Tengo que ftell() devuelve la cantidad de bytes, en mi caso me sirve para saber donde se encuentra ubicada la persona.
		
		fscanf(file0, "%d;%d;%*[^\n]\n", &aux0->id, &aux0->dni); // Solo me interesa el DNI.
		
		aux1->dni = aux0->dni;
		aux1->index = dsplz_total;
		
		fwrite(aux1, sizeof(dato_idx), 1, file1); // Escribo en el archivo "personas.idx"
		
		//printf("ID: %d ; DNI: %d; POS: %d\n", aux0->id, aux0->dni, aux1->index);
	}
	
	ordenarArchivo(file1);
	
	//...
	
	// Punto B:
	
	Indice *indice = obtenerIndice(file1);
	
	persona *p;
	p = malloc(sizeof(persona));
	
	const int DNI = 3021912;
	
	printf("Buscar el DNI: %d\nSe Encontro?: %d", DNI, buscar(file0, *indice, DNI, p));
	
	//...
	
	fclose(file0);
	fclose(file1);
	
	return 0;
}
