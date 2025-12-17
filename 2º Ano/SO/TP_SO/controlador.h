#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include "utils.h"

// ====== Estrutura de um serviço ======
typedef struct {
    int id;
    int hora;
    int distancia;
    char username[MAX_USERNAME];
    char local[MAX_LOCAL];
    int ativo;
    int execucao;
    int pid_veiculo;
    int pid_cliente;
} SERVICO;

// ====== Estrutura de um utilizador ======
typedef struct{
    char username[MAX_USERNAME];
    int pid;
} UTILIZADOR;

// ====== Estrutura de cada veículo da frota ======
typedef struct{
    int ativo;
    int servico_id;
    int pid;
    int percentagem;
} VEICULO;

// Estrutura para dados partilhados entre threads
typedef struct {
    int continua; //flag para terminar thread
    pthread_mutex_t *ptrinco;

    SERVICO *servicos;
    UTILIZADOR *utilizadores;
    VEICULO *frota;

    int *total_servicos;
    int *total_veiculos_ativos;
    int *tempo;
    int *nveic;
    int *km_total;
} TDATA;

//Dados utilizados pela thread que lê telemetria de um processo veiculo
typedef struct {
    int canal_fd; //descritor de leitura do pipe
    SERVICO *servico;
    VEICULO *veiculo;
    int id_veiculo;
    pthread_mutex_t *trinco;
    int *total_veiculos_ativos;
    int *km_total;
} TELEM_DATA;

// Funções utilitárias
void enviar_resposta(int pid, RESPOSTA *r);
void remover_utilizador(TDATA *td, int pid);
void notificar_todos_clientes_terminar(TDATA *td);
int encontrar_utilizador(TDATA *td, const char *username);
int encontrar_slot_livre(TDATA *td);

// Comandos do cliente
void comando_login(PEDIDO *p, TDATA *td);
void comando_agendar(PEDIDO *p, TDATA *td);
void comando_consultar(PEDIDO *p, TDATA *td);
void comando_cancelar(PEDIDO *p, TDATA *td);
void comando_terminar(PEDIDO *p, TDATA *td);

// Interpretador de pedidos
void tratar_pedido_cliente(PEDIDO *p, TDATA *td);

// Veículos e serviços
void verifica_lancar_veiculo(TDATA *td);
void lancar_processo_veiculo(int idx_servico, int idx_veiculo, TDATA *td);
void cancelar_servico(int id_servico, TDATA *td);
void cancelar_todos_os_servicos(TDATA *td);

//Comandos internos do controlador
void processar_comando(char *cmd, TDATA *td);

//Threads
void *thread_pedidos(void *data);
void *thread_tempo(void *data);
void *thread_telemetria(void *data);

void naofaznada(int s, siginfo_t *si, void *uc);

int ler_nveiculos();

#endif