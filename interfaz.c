#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lista_enlazada.h"


char mostrar_menu(){
/*Muestra el menu de opciones. Devuelve el numero de la opcion. Si no es
correcta, entonces devuelve -1.
*/

	char respuesta; //Opcion elegida por usuario

	printf("\n\t\tBienvenido, elija una de las siguientes opciones: \n\n");

	printf("(1) Leer Base de Datos\n");
	printf("(2) Salvar Base de Datos\n");
	printf("(3) Consultar Preguntas según su dificultad\n");
	printf("(4) Eliminar Pregunta\n");
	printf("(5) Insertar Pregunta\n");
	printf("(6) Salir\n\n");

	printf("\tIntroduzca una Opción --> ");
	scanf("%c%*c",&respuesta);


	return respuesta;


}


void insertar_pregunta(LISTA *miLista){

/*
Inserta una pregunta en una lista enlazada. El usuario inserta 
sus elementos constituyentes.
*/

	int codigo;
	int nivel;
	char area; 
	char *pregunta = (char *)malloc(sizeof(char)*100);
	char *opcion1 = (char *)malloc(sizeof(char)*100);
	char *opcion2 = (char *)malloc(sizeof(char)*100);
	char *opcion3 = (char *)malloc(sizeof(char)*100);
	int respuesta;
	
	printf("\t\tIntroduzca la información que se solicita en el siguiente formato: \n\n");
	printf("\t\tcodigo nivel area pregunta opcion1 opcion2 opcion3 respuesta\n\t\t");
	scanf("%d %d %c \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d%*c",&codigo,&nivel,&area,pregunta,opcion1,
										opcion2, opcion3, &respuesta);
	
	
	insertar(miLista,pregunta,opcion1,opcion2,opcion3,respuesta,codigo,nivel,area);


}

void eliminar_pregunta(LISTA *miLista,int codigo){

/*
Elimina la pregunta cuyo codigo esta dado en la lista de argumentos.
Si no se encuentra, se imprime un mensaje de error.
*/

	NODO *actual = miLista->primero;
	NODO *anterior = actual;
	int error = 1;
	
	if (actual->codigo == codigo){
	
		actual = actual->siguiente;
		miLista->primero = actual;
		
		free(anterior);
		error = 0;
	
	}
	else{
	
		actual = actual->siguiente;
		
		while(actual != NULL){
		
			if (actual->codigo == codigo){
			
				if (actual->siguiente != NULL){
				
					anterior->siguiente = actual->siguiente;
					free(actual);
					error = 0;
					break;
				
				}
				else{
				
					miLista->ultimo = anterior;
					free(actual);
					error = 0;
					break;
				
				}
			
			}
			
			anterior = actual;
			actual = actual->siguiente;
		
		}
	
	}

if (error){

	printf("\t\tLa pregunta no se encuentra en la lista\n");

}

}


void consultar_todo(LISTA *miLista){

/*
Imprime todas las preguntas de la lista dada
*/

	NODO *nodo = miLista->primero;
	
	printf("\tPreguntas Guardadas: \n\n");
	
	while(nodo != NULL){
	
		printf("\nCodigo: %d; Nivel: %d; Area: %c;\n"
			,nodo->codigo,nodo->nivel,nodo->area);
		
		printf("Pregunta: %s\n", nodo->pregunta);
		printf("Opciones: \n(1)-%s\n",nodo->respuesta1);
		printf("(2)-%s\n",nodo->respuesta2);
		printf("(3)-%s\n",nodo->respuesta3);
		printf("Respuesta: \n-%d\n",nodo->respuesta);
	
	nodo = nodo->siguiente;
	
	}

}


void consultar_pregunta_por_dificultad(LISTA *miLista, int nivel){

/*
Imprime todas las preguntas de la lista que corresponden con la dificultad dada.
*/

	NODO *nodo = miLista->primero;
	int noHay = 1;
	
	while(nodo != NULL){
	
		if (nodo->nivel == nivel){
			printf("Codigo: %d; Nivel: %d; Area: %c;\n"
				,nodo->codigo,nodo->nivel,nodo->area);
			
			printf("Pregunta: %s\n", nodo->pregunta);
			printf("Opciones: \n(1)-%s\n",nodo->respuesta1);
			printf("(2)-%s\n",nodo->respuesta2);
			printf("(3)-%s\n",nodo->respuesta3);
			printf("Respuesta: \n-%d\n",nodo->respuesta);
			noHay = 0;
		}
		
		nodo = nodo->siguiente;
	
	}
	if (noHay){
		printf("\t\tNo se encontro la pregunta\n");
	}


}


void leer_archivo(LISTA *miLista, char *nombre){

/*
Abre el archivo dado como argumento he inserta en la lista suministrada
todas sus lineas.
*/

	
	int codigo;
	int nivel;
	char area;
	char *pregunta = (char *)malloc(sizeof(char)*100);
	char *opcion1 = (char *)malloc(sizeof(char)*100);
	char *opcion2 = (char *)malloc(sizeof(char)*100);
	char *opcion3 = (char *)malloc(sizeof(char)*100);
	int respuesta;
	
	FILE *arch;
	
	if ((int)(arch = fopen(nombre,"r")) == -1){
		
		printf("\nNo se pudo abrir el archivo\n");
		exit(1);
	}
	
	
	while(fscanf(arch,"%d %d %c \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d%*c",&codigo,&nivel,&area,pregunta,opcion1,
											opcion2, opcion3, &respuesta) != EOF){
		
		insertar(miLista, pregunta, opcion1, opcion2, 
						opcion3, respuesta, codigo, nivel, area);
	}
	
	if (fclose(arch) == -1){
		printf("\nProblema al cerrar archivo\n");
		exit(1);
	}

}




int main(int argc, char **argv){


LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
char respuesta;
char otra_pregunta;
int codigo_eliminar;
int nivel_consultar;
int guardar_al_salir = 0;

leer_archivo(lista, argv[1]);

while(1){

	respuesta = mostrar_menu();

	switch (respuesta){

	case '1':
		
		consultar_todo(lista);
		break;
	
	case '2':
		
		printf("\nPreguntas Guardadas\n\n"); //Se engana al usuario
		guardar_al_salir = 1;
		//exit(0);
		break;
		
	case '3':
		
		printf("\tIntroduzca el nivel que desea consultar: ");
		scanf("%d%*c",&nivel_consultar);
		printf("\n");
		
		consultar_pregunta_por_dificultad(lista,nivel_consultar);
		
		//exit(0);
		break;
		
	case '4':
		
		
		printf("\t\tIngrese el codigo de la pregunta que desea eliminar: ");
		scanf("%d%*c",&codigo_eliminar);
		printf("\n");
		
		eliminar_pregunta(lista, codigo_eliminar);
		
		//exit(0);
		break;
		
	case '5':
		
		while(1){
			
			insertar_pregunta(lista);
			
			printf("\n\t\t(1) si hay otra pregunta, (0) de lo contrario: ");
			scanf("%c%*c", &otra_pregunta);
			printf("\n");
			
			if (otra_pregunta == '0'){
				break;
			}
		}
		
		//liberar_lista(lista);
		//exit(0);
		break;
		
	case '6':
		
		if (guardar_al_salir){
		
			guardar_en_archivo(argv[1],lista);
		}
		
		liberar_lista(lista);
		exit(0);
		break;
		
	default:
		
		printf("\t\tHa introducido una opción que no se ofrece\n");
		printf("INTENTELO NUEVAMENTE\n");
		

	}



}

return 0;

}
