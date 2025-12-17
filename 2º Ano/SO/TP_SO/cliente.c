#include "utils.h"

//Intrepreta o comando escrito pelo utilizador, validando a sintaxe e preenche a estrutura PEDIDO 
// Se retorna 1 -> Comando sintaxe valida
// SE retorna 0 -> Comndo com sintaxe invalida
int processar_comando(char *buffer, PEDIDO *p){
    int h, d, id;
    char loc[32];

    if(buffer[0] == '\0')
        return 0;

    // ---------- AGENDAR ----------
    if (sscanf(buffer, "agendar %d %s %d", &h, loc, &d) == 3) {

        if (h <= 0 || d <= 0) {
            return 0;
        }

        p->cmd = CMD_AGENDAR;
        p->hora = h;
        p->distancia = d;
        strcpy(p->local, loc);
        return 1;
    }

    // ---------- CANCELAR ----------
    if (sscanf(buffer, "cancelar %d", &id) == 1) {
        if(id < 0)
            return 0;

        p->cmd = CMD_CANCELAR;
        p->id_servico = id;
        return 1;
    }

    // ---------- CONSULTAR ----------
    if (strcmp(buffer, "consultar") == 0) {
        p->cmd = CMD_CONSULTAR;
        return 1;
    }

    // ---------- TERMINAR ----------
    if (strcmp(buffer, "terminar") == 0) {
        p->cmd = CMD_TERMINAR;
        return 1;
    }

    return 0;  // Comando desconhecido ou sintaxe errada
}


int main(int argc, char *argv[]) {

    // Valida os argumentos
    if (argc != 2){
        printf("Uso: ./cliente <username>\n");
        exit(1);
    }

    // Verifica se o controlador esta em execução
    if (access(CTRL_FIFO, F_OK) != 0) {
        printf("[ERRO] Controlador não está ativo.\n");
        exit(2);
    }

    PEDIDO p;
    RESPOSTA r;
    fd_set fds;
    int fd_cli, fd_ctrl, n;
    char fifo_cli[64];
    char buffer[MAX_MSG];

    //Abrir o FIFO do controlador para enviar pedidos
    fd_ctrl = open(CTRL_FIFO, O_WRONLY);
    if(fd_ctrl == -1){
        printf("[CLIENTE] Erro ao abrir FIFO do controlador");
        exit(3);
    }

    // Criar FIFO privado do clinte
    p.pid_cliente = getpid();
    sprintf(fifo_cli, CLI_FIFO, p.pid_cliente);

    if (mkfifo(fifo_cli, 0640) == -1) {
        printf("[CLIENTE] Erro ao criar FIFO do cliente");
        close(fd_ctrl);
        exit(4);
    }

    //Abrir FIFO do cliente para leitura e escrita
    fd_cli = open(fifo_cli, O_RDWR);
    if (fd_cli == -1) {
        printf("[CLIENTE] Erro ao abrir FIFO do cliente");
        unlink(fifo_cli);
        close(fd_ctrl);
        exit(5);
    }

    //Preparar e enviar pedido login
    strcpy(p.username, argv[1]);
    p.cmd = CMD_LOGIN;

    n = write(fd_ctrl, &p, sizeof(PEDIDO));
    if (n != sizeof(PEDIDO)) {
        printf("[CLIENTE] Erro ao enviar pedido de login (escrevi %d bytes)\n", n);
        close(fd_cli);
        unlink(fifo_cli);
        close(fd_ctrl);
        exit(6);
    }

    //Ler resposta de login
    n = read(fd_cli, &r, sizeof(RESPOSTA));
    if (n != sizeof(RESPOSTA)) {
        printf("[CLIENTE] Erro ao ler resposta do controlador\n");
        unlink(fifo_cli);
        close(fd_cli);
        close(fd_ctrl);
        exit(7);
    }

    printf("[CONTROLADOR] %s\n", r.msg);

    //Se a res == 0, já esiste um utilizador com o mesmo nome
    if (r.res == 0) {
        printf("[CLIENTE] Login falhou. A terminar...\n");
        unlink(fifo_cli);
        close(fd_cli);
        close(fd_ctrl);
            return 0;
    }

    //Ciclo principal do cliente (input + mensagens do controlador)
    while (1) {

    FD_ZERO(&fds); //Inicia limpa conjunto de descritores
    FD_SET(0, &fds); //stdin
    FD_SET(fd_cli, &fds); //Mensagens vindas do controlador do FIFO CLIENTE

    int sel = select(fd_cli + 1, &fds, NULL, NULL, NULL); //Preparar o select para esperar atividade de cada um dos descritores
    if (sel == -1) {
        printf("[CLIENTE] Erro no select.\n");
        break;
    }
    //Comandos do utilizador
    if (FD_ISSET(0, &fds)) {
        if (fgets(buffer, MAX_MSG, stdin) != NULL) {

            int t = strlen(buffer);
            if (t > 0) buffer[t-1] = '\0';

            if (buffer[0] != '\0') {      // ENTER é ignorado
                if (processar_comando(buffer, &p)) {

                    n = write(fd_ctrl, &p, sizeof(PEDIDO));
                    if (n != sizeof(PEDIDO)) {
                        printf("[CLIENTE] Erro ao enviar comando\n");
                        break;
                    }
                }
                else {
                    printf("[CLIENTE] Comando inválido.\n");
                }
            }
        }
    }
    //Resposta do Controlador
    if (FD_ISSET(fd_cli, &fds)) {

    n = read(fd_cli, &r, sizeof(RESPOSTA));

    if (n == 0) {
        printf("[CLIENTE] Controlador desligou.\n");
        break;
    }

    if (n == sizeof(RESPOSTA)) {

        if (r.cmd == CMD_TERMINAR && r.res == 1) { //Resposta ao pedido de terminar, ou controlador a avisar que vai terminar

            if (r.msg[0] != '\0')
                printf("[CONTROLADOR] %s\n", r.msg);

            break; //sair do ciclo
        }
        if (r.cmd == CMD_INFO) {  //Mensagens vindas do veiculo

            if (r.msg[0] != '\0')
                printf("%s\n", r.msg);
        }else {

            if (r.msg[0] != '\0') {

                if (r.res)
                    printf("[CONTROLADOR] %s\n", r.msg);  //PEDIDO ACEITE
                else
                    printf("[CONTROLADOR][ERRO] %s\n", r.msg); //PEDIDO NAO ACEITE
            }
        }
    }
}
}
    unlink(fifo_cli);
    close(fd_cli); //fechar fifo cliente
    close(fd_ctrl); //fechar fifo do controlador

    return 0;
}