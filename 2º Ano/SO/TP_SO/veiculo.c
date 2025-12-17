#include "utils.h"

int cancelado = 0;

//Handler para SIGUSR1 (marca a viagem como cancelada)
void trata_cancelamento(int sig, siginfo_t *info, void *ucontext) {
    cancelado = 1;
}

int main(int argc, char *argv[]) {

    //verifica argumentos
    if (argc < 3) {
        printf("Uso: %s <local> <distancia>\n", argv[0]);
        return 1;
    }

    char local[32];
    strcpy(local, argv[1]);
    int distancia_total = atoi(argv[2]);

    //Instalar handler de cancelamento
    struct sigaction ca;
    ca.sa_sigaction = trata_cancelamento;
    ca.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &ca, NULL);

    printf("[VEICULO] Cheguei ao local (%s)\n", local);
    fflush(stdout);

    int km_percorridos = 0;
    int proxima_percentagem = 10;

    //Ciclo da viagem (1km por segundo)
    while (km_percorridos < distancia_total) {

        sleep(1);
        km_percorridos++;

        //Verificar se foi cancelado pelo controlador
        if (cancelado == 1) {
            printf("[VEICULO] Viagem cancelada a meio\n");
            fflush(stdout);
            exit(5);
        }

        //calcular percentagem concluida
        int percentagem_atual = km_percorridos * 100 / distancia_total;

        //Enviar telemetria de 10% em 10%
        if (percentagem_atual >= proxima_percentagem) {
            printf("[VEICULO] %d%% concluido\n", proxima_percentagem);
            fflush(stdout);
            proxima_percentagem += 10;
        }
    }

    usleep(50000); //Evitar que as duas ultimas mensagens sejam enviadas juntas/coladas, para que o controlador as possa intrepertar separadamente
    printf("[VEICULO] Viagem concluida\n");
    fflush(stdout);

    return 0;
}