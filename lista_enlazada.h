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


void insertar(LISTA *, char *, char *, char *, char *, int, int , int , char);

void liberar_lista(LISTA *);

void guardar_en_archivo(char *, LISTA *);


