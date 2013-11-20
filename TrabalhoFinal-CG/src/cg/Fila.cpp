/*
 * Implementação circular com contador.
 */

#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

void cria_fila(Fila* fila) {
  fila->i = 0;
  fila->f = 0;
  fila->c = 0;
}

int fila_vazia(Fila* fila) {
  return (fila->c == 0);
}

void insere_fila(Fila* fila, tiroMeteoro elem) {
  if (fila->c == MAX_ELEM) {
    printf("Erro: fila cheia!\n");
   // exit(0);
  }
  fila->c++;
  fila->f = (fila->f +1) % MAX_ELEM;
  fila->vet[fila->f] = elem;
}

tiroMeteoro remove_fila(Fila* fila) {
  if (fila_vazia(fila)) {
    printf("Erro: fila vazia!\n");
    //exit(0);
  }
  fila->c--;
  fila->i = (fila->i +1) % MAX_ELEM;
  return fila->vet[fila->i];
}

void libera_fila(Fila* fila) {
  cria_fila(fila);
}
