/*
 * Implementa��o circular com contador.
 */

#ifndef CIRCULAR
#define CIRCULAR

typedef struct {
	float x;
	float y;
	float z;
} ponto;

typedef struct {
	ponto pontoInicio;
	ponto pontoFim;
	bool visivel; //depois da colizao o tiro n�o deve ser visivel
	float t;

} tiro; //define um ponto.

#define MAX_ELEM 100
struct Fila_t {
  int i,f,c;
  tiro vet[MAX_ELEM];
};

typedef struct Fila_t Fila; /* Tipo da fila (a ser redefinido) */

void cria_fila(Fila* fila);

int fila_vazia(Fila* fila);

void insere_fila(Fila* fila, tiro elem);

tiro remove_fila(Fila* fila);

void libera_fila(Fila* fila);

#endif
