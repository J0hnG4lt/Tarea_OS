#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct NOD{

/*
Nodo de una lista enlazada
*/

	char *pregunta;
	
	char *respuesta1;
	char *respuesta2;
	char *respuesta3;
	int respuesta;
	
	int codigo;
	int nivel;
	char area;
	
	struct NOD *siguiente;

};

typedef struct NOD NODO;


struct LIST{

/*
Base de la lista enlazada
*/
	NODO *primero;
	NODO *ultimo;

};

typedef struct LIST LISTA;

void insertar(LISTA *miLista, char *quest, char *resp1, char *resp2, char *resp3, int resp, int cod, int niv, char area){

/*
Inserta un nuevo nodo en la lista enlazada
*/
	static int primer_elem = 1;

	NODO *nuevoNodo = (NODO *)malloc(sizeof(NODO));
	
	nuevoNodo->pregunta = quest;
	nuevoNodo->respuesta1 = resp1;
	nuevoNodo->respuesta2 = resp2;
	nuevoNodo->respuesta3 = resp3;
	nuevoNodo->respuesta = resp;
	nuevoNodo->codigo = cod;
	nuevoNodo->nivel = niv;
	nuevoNodo->area = area;
	
	if (primer_elem != 1){
	
		miLista->ultimo->siguiente = nuevoNodo;
		miLista->ultimo = nuevoNodo;
	}
	else{
	
		miLista->ultimo = nuevoNodo;
		miLista->primero = nuevoNodo;
	
	}
	
	primer_elem++;
	
}


void liberar_lista(LISTA *miLista){

/*
Libera la totalidad de la memria ocupada por la lista enlazada
*/

	NODO *temp = miLista->primero;
	NODO *sig = temp;
	
	while(sig != NULL){
		
		temp = sig;
		
		sig = temp->siguiente;
		free(temp);
	}
	

}

void guardar_en_archivo(char *nombre_arc, LISTA *miLista){

/*
Guarda los contenidos de la lista en el archivo
*/

	FILE *arc = fopen(nombre_arc,"w");
	
	if (arc == NULL){
		printf("No se pudo abrir archivo \n");
		exit(1);
	}
	
	NODO *temp = miLista->primero;
	
	while(temp != NULL){
	
		fprintf(arc, "%d %d %c \"%s\" \"%s\" \"%s\" \"%s\" %d\n", temp->codigo, temp->nivel, temp->area,
				temp->pregunta, temp->respuesta1, temp->respuesta2, temp->respuesta3,
				temp->respuesta);
		
		temp = temp->siguiente;
	}
	
	if (fclose(arc) == EOF){
		printf("\nProblema al cerrar archivo\n");
		exit(1);
	}

}







