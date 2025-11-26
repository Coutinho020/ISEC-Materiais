#ifndef P2324_AULA9_PARQUE_H
#define P2324_AULA9_PARQUE_H


typedef struct tipoA cliente, *pCliente;
typedef struct tipoB acesso, *pAcesso;

typedef struct {int h, m;} hora;

struct tipoA{
    int id;         // Identificador único
    int contador;   // Número de utilizações nesse dia
    pAcesso lista;  // Ponteiro para a lista de acessos
    pCliente prox;  // Ponteiro para o próximo cliente
};

struct tipoB{
    hora in, out;   // Horas de entrada e saída
    pAcesso prox;
};

void libertaTudo(pCliente p);

pCliente criaExemploED();

void mostraTudo(pCliente p);

int dentroParque(pCliente p);

int dentroParqueHora(pCliente p, hora x);

int maisMinutos(pCliente p, int *m);

pCliente eliminaCliente(pCliente p, int id);

pCliente acessoParque(pCliente p, int id, hora x);

pCliente elimina_sessoes_abertas(pCliente p);

#endif //P2324_AULA9_PARQUE_H
