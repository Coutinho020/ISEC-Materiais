#ifndef UTILS_H
#define UTILS_H
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX_SERVICOS      50
#define MAX_VEICULOS      10
#define MAX_UTILIZADORES  30
#define MAX_USERNAME      32
#define MAX_LOCAL         32
#define MAX_MSG      64

#define CTRL_FIFO "ctrl_fifo"  //FIFO Controlador
#define CLI_FIFO "cli_%d"  //FIFO Cliente

//Tipo de comando
typedef enum {
    CMD_LOGIN = 1,
    CMD_AGENDAR = 2,
    CMD_CONSULTAR = 3,
    CMD_CANCELAR = 4,
    CMD_TERMINAR = 5,
    CMD_INFO = 6
} CMD_CODE;

// Cliente -> Controlador
typedef struct {
    int pid_cliente; // para o controlador saber o FIFO a usar
    char username[MAX_USERNAME]; // utilizado no login
    int cmd;
    int  hora;
    int distancia;
    char local[MAX_LOCAL];
    int id_servico;
} PEDIDO;

//Controlador -> Cliente
typedef struct {
    int res;   //1 = sucesso , 0 = erro
    int cmd;
    char msg[MAX_MSG];  // texto de resposta
} RESPOSTA;

#endif