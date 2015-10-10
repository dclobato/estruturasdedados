#ifndef __ARVORE__
#define __ARVORE__
typedef enum {RAIZ, ESQ, DIR} TipoNo;

typedef struct __noar {
   int dado;
   struct __noar *esq;
   struct __noar *dir;
} NO_ARVORE;

typedef NO_ARVORE* ARVORE;

void inicializa_arvore (ARVORE *, int *);
ARVORE aloca_no_arvore (int, int*);
void definir_arvore (ARVORE *, TipoNo, ARVORE *, int *);
void percurso_pre (ARVORE);
void percurso_in (ARVORE);
void percurso_pos (ARVORE);
#endif
