/*
 * Implementação circular com contador.
 */

#ifndef CIRCULAR
#define CIRCULAR

typedef struct {
	float x;
	float  y;
	float  z;
} ponto;

typedef struct {
	ponto pontoInicio;
	ponto pontoFim;
	ponto posicaoAtual;
	bool visivel; //depois da colizao o tiro não deve ser visivel
	float t;

} tiroMeteoro; //define um ponto.

#define MAX_ELEM 100
struct Fila_t {
  int i,f,c;
  tiroMeteoro vet[MAX_ELEM];
};

typedef struct Fila_t Fila; /* Tipo da fila (a ser redefinido) */

void cria_fila(Fila* fila);

int fila_vazia(Fila* fila);

void insere_fila(Fila* fila, tiroMeteoro elem);

tiroMeteoro remove_fila(Fila* fila);

void libera_fila(Fila* fila);

#endif
