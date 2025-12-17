#include "utils.h"
#include "controlador.h"

//Informacoes das threads Telemetria
TELEM_DATA telem_data[MAX_VEICULOS]; //array com os dados para cada thread (um por veiculo)
pthread_t telem_thread[MAX_VEICULOS]; //Identificadores das threads
int telem_ativa[MAX_VEICULOS]; //flag para indicar se a thread esta ativa (1) ou nao (0)


//Le a varivel de ambiente NVEICULOS
int ler_nveiculos() {
    char *v = getenv("NVEICULOS");

    //Se não existir ou tiver valor invalido, fecha o programa e avisa o utilizador
    if (v == NULL) {
        printf("[ERRO] Variável de ambiente NVEICULOS não definida.\n");
        printf("Use: export NVEICULOS=<numero_de_veiculos>\n");
        exit(1);
    }

    int n = atoi(v);

    if (n < 1 || n > MAX_VEICULOS) {
        printf("[ERRO] Valor inválido para NVEICULOS (%d).\n", n);
        printf("O número de veículos deve estar entre 1 e %d.\n", MAX_VEICULOS);
        exit(1);
    }

    return n;
}

// Envia uma estrutura RESPOSTA para o FIFO do cliente identificado pelo pid
void enviar_resposta(int pid, RESPOSTA *r) {
    char fifo_cli[64];
    sprintf(fifo_cli, CLI_FIFO, pid); //constroi o nome do fifo

    int fd = open(fifo_cli, O_WRONLY);
    if (fd == -1) {  //cliente pode ter terminado
        return;
    }
    write(fd, r, sizeof(RESPOSTA));
    close(fd);
}

//Remove um utilizador da lista (quando termina ou sai do programa)
void remover_utilizador(TDATA *td, int pid) {
    UTILIZADOR *u = td->utilizadores;

    for (int i = 0; i < MAX_UTILIZADORES; i++) {
        if (u[i].pid == pid) {
            u[i].pid = -1;
            u[i].username[0] = '\0';
            return;
        }
    }
}

//Se desligar, avisa todos os clientes que estao ativos
void notificar_todos_clientes_terminar(TDATA *td) {

    RESPOSTA r;
    r.cmd = CMD_TERMINAR;
    r.res = 1;
    strcpy(r.msg, "Controlador vai terminar. Cliente será encerrado.");

    UTILIZADOR *u = td->utilizadores;

    for (int i = 0; i < MAX_UTILIZADORES; i++) {
        if (u[i].pid != -1) {  // utilizador ativo
            enviar_resposta(u[i].pid, &r);
        }
    }
}

//Função auxiliar para procurar um cliente pelo seu username
int encontrar_utilizador(TDATA *td, const char *username){
    UTILIZADOR *u = td->utilizadores;

    for(int i = 0; i < MAX_UTILIZADORES; i++){
        if(u[i].pid != -1 && strcmp(u[i].username, username) == 0)
            return i;
    }
    return -1; //Se encontrou retorna o indice da lista, se não retorna -1;
}

//Função para procurar uma posição livre na lista
int encontrar_slot_livre(TDATA *td) {
    UTILIZADOR *u = td->utilizadores;

    for (int i = 0; i < MAX_UTILIZADORES; i++)
        if (u[i].pid == -1)
            return i;
    return -1;  //Se encontrou retorna o indice da primeira posicao livre, senão retona -1;
}

//Comandos cliente
void comando_login(PEDIDO *p, TDATA *td) {
    RESPOSTA r;
    r.cmd = CMD_LOGIN;

    //Verifica se existe algum utilizador com o mesmo username
    int dup = encontrar_utilizador(td, p->username);
    if (dup != -1) {
        r.res = 0;
        strcpy(r.msg, "Username já existe");
        enviar_resposta(p->pid_cliente, &r);
        return;
    }

    //procura uma posição livre na lista
    int pos = encontrar_slot_livre(td);
    if (pos == -1) {
        r.res = 0;
        strcpy(r.msg, "Limite máximo de utilizadores atingido");
        enviar_resposta(p->pid_cliente, &r);
        return;
    }

    //Guarda utilizador na tabela;
    UTILIZADOR *u = td->utilizadores;
    strcpy(u[pos].username, p->username);
    u[pos].pid = p->pid_cliente;

    //Envia resposta ao utilizador do sucesso do login
    r.res = 1;
    sprintf(r.msg, "Login aceite! Bem-vindo %s!", p->username);
    enviar_resposta(p->pid_cliente, &r);
}

// Cria um novo serviço que será iniciado futuramente pela thread do tempo.
void comando_agendar(PEDIDO *p, TDATA *td) {
    RESPOSTA r;
    r.cmd = CMD_AGENDAR;

    int *tempo = td->tempo; //tempo atual da simulação
    int *total_servicos = td->total_servicos;
    SERVICO *servicos = td->servicos;

    if (p->hora <= *tempo) { //se a hora já passou, avisa o cliente
        r.res = 0;
        sprintf(r.msg, "Hora %d passou", p->hora);
        enviar_resposta(p->pid_cliente, &r);
        return;
    }

    if (*total_servicos >= MAX_SERVICOS) { //Se a tabela de serviços atingiu o limite, avisa o cliente
        r.res = 0;
        strcpy(r.msg, "Limite de serviços atingido");
        enviar_resposta(p->pid_cliente, &r);
        return;
    }

    //Preencher a tabela serviços com a nova entrada
    SERVICO *s = &servicos[*total_servicos];
    s->id = *total_servicos + 1;
    s->hora =p->hora;
    s->distancia = p->distancia;
    s->ativo = 1;
    s->execucao = 0;
    s->pid_veiculo = -1;
    s->pid_cliente = p->pid_cliente;

    strcpy(s->username, p->username);
    strcpy(s->local, p->local);

    (*total_servicos)++;

    //Resposta ao cliente
    r.res = 1;
    sprintf(r.msg, "Serviço %d agendado", s->id);
    enviar_resposta(p->pid_cliente, &r);
}

//Função para enviar ao cliente todos os seus serviços agendados
void comando_consultar(PEDIDO *p, TDATA *td)
{
    RESPOSTA r;
    r.res = 1;
    r.cmd = CMD_CONSULTAR;

    int *total_servicos = td->total_servicos;
    SERVICO *servicos = td->servicos;

    strcpy(r.msg, "Lista de Servicos:");
    enviar_resposta(p->pid_cliente, &r);

    for (int i = 0; i < *total_servicos; i++) {
        SERVICO *s = &servicos[i];
        //Verifica os serviços do cliente e envia um de cada vez, para não ultrapassar o limite do buffer do FIFO
        if (s->ativo && strcmp(s->username, p->username) == 0) {
            r.cmd = CMD_CONSULTAR;
            sprintf(r.msg, "ID:%d | H:%d | L:%s", s->id, s->hora, s->local);
            enviar_resposta(p->pid_cliente, &r);
        }
    }
    r.msg[0] = '\0';
    r.cmd = CMD_CONSULTAR;
    enviar_resposta(p->pid_cliente, &r);
}

//Comando para cancelar um ou todos os serviços de um cliente (PEDIDO do Cliente)
void comando_cancelar(PEDIDO *p, TDATA *td) {

    RESPOSTA r;
    int id = p->id_servico;

    int *total_servicos = td->total_servicos;
    SERVICO *servicos = td->servicos;

    r.cmd = CMD_CANCELAR;

    //Se o id for 0, cancela todos os serviços do cliente
    if (id == 0) {
        int conta = 0;

        for (int i = 0; i < *total_servicos; i++) {
            SERVICO *s = &servicos[i];
            //cancela apenas os serviços agendados do cliente
            if (s->ativo && !s->execucao && strcmp(s->username, p->username) == 0) {
                cancelar_servico(s->id, td);
                conta++;
            }
        } //Envia a resposta ao cliente
        if (conta == 0){
            r.res = 0;
            strcpy(r.msg, "Não tem serviços a cancelar");
        }
        else{
            r.res = 1;
            sprintf(r.msg, "Foram cancelados %d serviços", conta);
        }
        enviar_resposta(p->pid_cliente, &r);
        return;
    }

    //Cancelar apenas um serviço
    int idx = id - 1;
    //Verifica se o id é invalido, se está ativo, e se pertence ao utilizador
    if (idx >= *total_servicos || servicos[idx].ativo == 0 || strcmp(servicos[idx].username, p->username) != 0) {
        r.res = 0;
        strcpy(r.msg, "Não tens nenhum serviço com esse ID");
        r.cmd = CMD_CANCELAR;
        enviar_resposta(p->pid_cliente, &r);
        return;
    }

    //Como apenas pode cancelar serviços agendados, se tiver em execução, avisa o cliente
    if (servicos[idx].execucao == 1) {
        r.res = 0;
        strcpy(r.msg, "Não pode cancelar um serviço em execução");
        enviar_resposta(p->pid_cliente, &r);
        return;
    }

    //Se passar pelas validações chama a função para cancelar o serviço e avisa o cliente do sucesso da operação
    cancelar_servico(id, td);
    r.res = 1;
    sprintf(r.msg, "Serviço %d cancelado.", id);
    enviar_resposta(p->pid_cliente, &r);
}

//Termina o cleinte, verifica se pode sair e cancela serviços agendados
void comando_terminar(PEDIDO *p, TDATA *td) {
    RESPOSTA r;
    int cancelados = 0;
    r.cmd = CMD_TERMINAR;

    int *total_servicos = td->total_servicos;
    SERVICO *servicos = td->servicos;

    for(int i = 0; i < *total_servicos; i++){
        SERVICO *s = &servicos[i];
        //Verifica se tem alguma viagem em execução, tiver avisa o cliente que não pode sair
        if(s->execucao == 1 && strcmp(s->username, p->username) == 0){
            r.res = 0;
            strcpy(r.msg, "Nao pode terminar, tem um servico em execucao");
            enviar_resposta(p->pid_cliente, &r);
            return;
        }
    }

    for(int i = 0; i < *total_servicos; i++){
        SERVICO *s = &servicos[i];
        //Se não tiver a executar nenhuma viagem, cancela os serviços agendados (se tiver)
        if(s->ativo && strcmp(s->username, p->username) == 0){
            cancelar_servico(s->id, td);
            cancelados++;
        }
    }

    //Avisa o cliente que pode encerrar, e se tinha viagens agendadas, notifica quantas foram cancelas
    if(cancelados > 0){
        sprintf(r.msg, "Cliente vai encerrar. (%d serviços cancelados)", cancelados);
    }else{
        strcpy(r.msg, "Cliente vai encerrar");
    }
    remover_utilizador(td, p->pid_cliente); //remove o utilizador da tabela
    r.res = 1;
    enviar_resposta(p->pid_cliente, &r);
}

//Comandos para os pedidos do cliente
void tratar_pedido_cliente(PEDIDO *p, TDATA *td) {
    switch (p->cmd) {

        case CMD_LOGIN:
            comando_login(p, td);
            break;

        case CMD_AGENDAR:
            comando_agendar(p, td);
            break;

        case CMD_CONSULTAR:
            comando_consultar(p, td);
            break;

        case CMD_CANCELAR:
            comando_cancelar(p, td);
            break;

        case CMD_TERMINAR:
            comando_terminar(p, td);
            break;

        default: {
            RESPOSTA r;
            r.cmd = p->cmd;
            r.res = 0;
            strcpy(r.msg, "Comando inválido");
            enviar_resposta(p->pid_cliente, &r);
        }
    }
}

//Comandos do controlador
//Listar utilizadores ativos e o estado dos seus serviços
void listar_utilizadores(TDATA *td) {

    printf("=== UTILIZADORES ===\n");

    for (int i = 0; i < MAX_UTILIZADORES; i++) {
        UTILIZADOR *u = &td->utilizadores[i];

        if (u->pid != -1) {   // Utilizador ligado
            int tem_servicos = 0;
            int em_viagem = 0;

            // Verificar todos os serviços
            for (int j = 0; j < *td->total_servicos; j++) {
                SERVICO *s = &td->servicos[j];

                // Apenas serviços deste utilizador
                if (strcmp(s->username, u->username) == 0) {
                    if (s->ativo)
                        tem_servicos = 1;

                    if (s->ativo && s->execucao == 1)
                        em_viagem = 1;
                }
            }
            if (em_viagem) {  //Em viagem
                printf("%s — EM VIAGEM\n", u->username);
            } else if (tem_servicos) {  // Tem serviços ativos, mas nenhum em execução
                printf("%s — À ESPERA DE CARRO\n", u->username);
            } else {
                printf("%s — SEM SERVIÇOS\n", u->username);  // Ligado, mas sem serviços marcados
            }
        }
    }
}

// Listar o estado da frota, se em viagem (percentagem da viagem), senão mostra Livre
void listar_frota(TDATA *td){
    printf("=== FROTA ===\n");

    for(int i = 0; i < *td->nveic; i++){
        VEICULO *v = &td->frota[i];
        if(v->ativo){
           printf("Veiculo %d | servico = %d | %d%%\n", i+1, v->servico_id, v->percentagem);
        }else{
        printf("Veiculo %d | LIVRE\n", i+1);
        }
    }
}

// Listar todos os serviços que estão agendados e em execução
void listar_servicos(TDATA *td){
    printf("=== Servicos ===\n");

    for(int i = 0; i < *td->total_servicos; i++){
        SERVICO *s = &td->servicos[i];
        if(s->ativo){
            if(s->execucao){
                printf("ID: %d | USER: %s | H: %d | L: %s | Estado: Em Viagem\n", s->id, s->username, s->hora, s->local);
            }else{
                printf("ID: %d | USER: %s | H: %d | L: %s | Estado: Agendado\n", s->id, s->username, s->hora, s->local);
            }
        }
    }
 }

//Lança um processo veiculo associado ao servico idx e ao veiculo idv
void lancar_processo_veiculo(int idx, int idv, TDATA *td) {

    int canal[2];
    if (pipe(canal) == -1) {  //cria pipe telemetria
        printf("[ERRO] Nao foi possivel criar pipe para telemetria.\n");
        return;
    }

    SERVICO *s = &td->servicos[idx]; //serviço a executar
    VEICULO *v = &td->frota[idv]; //veiculo atribuido

    int pid = fork(); //cria processo filho
    if (pid < 0) {
        printf("[ERRO] fork falhou ao lançar serviço %d.\n", s->id);
        close(canal[0]);
        close(canal[1]);
        return;
    }

    if (pid == 0) {
        close(1);
        dup(canal[1]);
        close(canal[0]);
        close(canal[1]);

        // preparar argumentos
        char dist_str[16];
        sprintf(dist_str, "%d", s->distancia);

        //exec
        execl("./veiculo", "veiculo", s->local, dist_str, NULL);

        printf("[ERRO] Nao foi possivel executar a aplicacao veiculo.\n");
        exit(7);
    }

    //Pai
    close(canal[1]); // controlador só vai ler do pipe

    //guardar pid no serviço e no veiculo
    pthread_mutex_lock(td->ptrinco);
    s->pid_veiculo = pid;
    v->pid = pid;
    pthread_mutex_unlock(td->ptrinco);

    printf("[CONTROLADOR] Veículo %d lançado para serviço %d\n", idv + 1, s->id);

    // Preencher dados para a thread de telemetria do veiculo
    telem_data[idv].canal_fd = canal[0];
    telem_data[idv].id_veiculo = idv;
    telem_data[idv].servico = s;
    telem_data[idv].veiculo = v;
    telem_data[idv].trinco = td->ptrinco;
    telem_data[idv].total_veiculos_ativos = td->total_veiculos_ativos;
    telem_data[idv].km_total = td->km_total;

    // Criar thread de telemetria para este veículo
    pthread_create(&telem_thread[idv], NULL, thread_telemetria, (void *) &telem_data[idv]);
    telem_ativa[idv] = 1;
}

//Verfica se há serviços na hora atual, se sim lança um veiculo para os executar
void verifica_lancar_veiculo(TDATA *td) {

    while (1) {

        int idx_servico = -1;
        int idx_veiculo = -1;

        pthread_mutex_lock(td->ptrinco);

        int tempo_atual = *td->tempo;
        int total = *td->total_servicos;
        int ativos = *td->total_veiculos_ativos;
        int capacidade = *td->nveic;

        SERVICO *serv = td->servicos;
        VEICULO *frota = td->frota;

        for (int i = 0; i < total; i++) {

            SERVICO *s = &serv[i];
            //procura por servicos agendados, que não estão em execução, agendados para a hora atual
            if (s->ativo && !s->execucao && s->hora == tempo_atual) {

                if (ativos == capacidade) { //Se não houverem veiculos livres neste momento cancela a viagem e notifica o cliente
                    printf("[CONTROLADOR] Sem veículos livres para serviço %d. Serviço será cancelado.\n", s->id);

                    RESPOSTA r;
                    r.cmd = CMD_CANCELAR;
                    r.res = 1;
                    sprintf(r.msg, "O serviço %d foi cancelado : Sem veiculos", s->id);
                    enviar_resposta(s->pid_cliente, &r);

                    //Remove o serviço da tabela
                    s->ativo = 0;
                    s->execucao = 0;
                    s->pid_veiculo = -1;
                } else {
                    // Encontrar veículo livre
                    for (int j = 0; j < capacidade; j++) {
                        if (frota[j].ativo == 0) {
                            idx_servico = i;
                            idx_veiculo = j;

                            // Atualizar tabelas dos serviço e do veiculo
                            s->execucao = 1;
                            frota[j].ativo = 1;
                            frota[j].servico_id = s->id;
                            frota[j].pid = -1;
                            frota[j].percentagem = 0;
                            (*td->total_veiculos_ativos)++;
                            break;
                        }
                    }
                }
                // tratamos apenas um serviço por iteração do while
                break;
            }
        }

        pthread_mutex_unlock(td->ptrinco);

        // Nada para lançar neste momento -> sair
        if (idx_servico == -1 || idx_veiculo == -1) {
            break;
        }
        // Se existir, lançar o veiculo
        lancar_processo_veiculo(idx_servico, idx_veiculo, td);
    }
}

//Função para cancelar um serviço, tanto agendado como em execução
void cancelar_servico(int id, TDATA *td) {

    int total = *td->total_servicos;
    SERVICO *svec = td->servicos;
    VEICULO *frota = td->frota;

    //Se o id recebido for 0, cancela todos os serviços(agendados e em execução)
    if (id == 0) {

        for (int i = 0; i < total; i++) {
            if (svec[i].ativo) {
                cancelar_servico(svec[i].id, td);
            }
        }

        printf("[CONTROLADOR] Todos os serviços foram cancelados.\n");
        return;
    }

    int idx = id - 1;

    //verifica se o id é valido
    if (idx < 0 || idx >= total || svec[idx].ativo == 0) {
        printf("[ERRO] Serviço %d não existe\n", id);
        return;
    }

    SERVICO *s = &svec[idx];
    //Se não estiver em execução, atualizar as tabelas do serviço e notificar o cliente
    if (s->execucao == 0) {

        s->ativo = 0;
        s->pid_veiculo = -1;

        printf("[CONTROLADOR] Serviço %d cancelado antes de iniciar.\n", id);

        RESPOSTA r;
        r.cmd = CMD_CANCELAR;
        r.res = 1;
        sprintf(r.msg, "O seu serviço %d foi cancelado pelo controlador.", id);
        enviar_resposta(s->pid_cliente, &r);

        return;
    }

    //Se estiver em execução envia um sinal ao veiculo para terminar o processo
    union sigval sv;
    sv.sival_int = id;

    sigqueue(s->pid_veiculo, SIGUSR1, sv);
}

//Cancelar todos os serviços, utilizado quando o controlador termina e existem serviços agendados e em execução
void cancelar_todos_os_servicos(TDATA *td) {

    int total = *td->total_servicos;
    SERVICO *svec = td->servicos;

    for (int i = 0; i < total; i++) {
        if (svec[i].ativo) {
            cancelar_servico(svec[i].id, td);
        }
    }
}

// thread responsável por avançar o tempo simulado e lançar serviços na fora certa;
void *thread_tempo(void * data) {

    TDATA *td = (TDATA *) data;

    while (td->continua) {

        sleep(1);

        pthread_mutex_lock(td->ptrinco);
        (*td->tempo)++;  //incrementa o tempo simulado do sistema
        pthread_mutex_unlock(td->ptrinco);
        verifica_lancar_veiculo(td); //chama a função para verificar se neste momento exite algum veiculo a ser lançado
    }

    pthread_exit(NULL);
}

//Thread responsavel por ler pedidos enviados pelo cliente
void *thread_pedidos(void *data) {

    TDATA *td = (TDATA *) data;
    int fd, n;
    PEDIDO p;

    //Abre o FIFO do controlador
    fd = open(CTRL_FIFO, O_RDWR);

    if (fd == -1) {
        printf("[CONTROLADOR] Erro ao abrir FIFO\n");
        pthread_exit(NULL);
    }

    while (td->continua) {

        n = read(fd, &p, sizeof(PEDIDO));
        if (n == sizeof(PEDIDO)) {

            pthread_mutex_lock(td->ptrinco);
            tratar_pedido_cliente(&p, td);  //intrepreta e executa o comando
            pthread_mutex_unlock(td->ptrinco);
        }
    }

    close(fd);
    pthread_exit(NULL);
}

//Thread responsavel por ler mensagens vindas do processo veiculo
void *thread_telemetria(void *data) {

    TELEM_DATA *t = (TELEM_DATA *) data;
    char buffer[60];
    int n;

    do {
        //ler mensagem do veiculo atraves do pipe anonimo
        n = read(t->canal_fd, buffer, sizeof(buffer) - 1);
        if (n > 0) {

            buffer[n] = '\0';

            pthread_mutex_lock(t->trinco);

             if (buffer[n-1] == '\n')
                buffer[n-1] = '\0';

            printf("[VEICULO %d] %s\n", t->id_veiculo + 1, buffer);

            int perc;
            char local[20];

            //Mensagem inicial
            if (sscanf(buffer, "[VEICULO] Cheguei ao local (%s)", local) == 1) {

                RESPOSTA r;
                r.cmd = CMD_INFO;
                r.res = 1;
                strcpy(r.msg, buffer);  //reeinviar mensagem ao cliente
                enviar_resposta(t->servico->pid_cliente, &r);
            }
            //Mensagem de x% concluida (atualizar a tabela de veiculos)
            else if (sscanf(buffer, "[VEICULO] %d%% concluido", &perc) == 1) {
                t->veiculo->percentagem = perc;
            }
            //Se a viagem for cancelada pelo controlador
            else if (strcmp(buffer, "[VEICULO] Viagem cancelada a meio") == 0) {

                //Inserir os km com base na percentagem
                int perc = t->veiculo->percentagem;
                int total = t->servico->distancia;
                int km_parciais = (total * perc) / 100;
                (*t->km_total) += km_parciais;

                //Libertar serviço e o veiculo
                t->servico->execucao = 0;
                t->servico->ativo = 0;

                t->veiculo->ativo = 0;
                t->veiculo->percentagem = 0;
                t->veiculo->servico_id = -1;
                t->veiculo->pid = -1;

                (*t->total_veiculos_ativos)--;

                RESPOSTA r;
                r.cmd = CMD_INFO;
                r.res = 1;
                strcpy(r.msg, buffer);
                enviar_resposta(t->servico->pid_cliente, &r);
            }
            //A viagem foi concluida
            else if (strcmp(buffer, "[VEICULO] Viagem concluida") == 0) {
                //Libertar serviço e veiculo
                t->servico->execucao = 0;
                t->servico->ativo = 0;

                t->veiculo->ativo = 0;
                t->veiculo->percentagem = 0;
                t->veiculo->servico_id = -1;
                t->veiculo->pid = -1;

                //Adicionar os km feitos
                (*t->km_total) += t->servico->distancia;
                (*t->total_veiculos_ativos)--;

                RESPOSTA r;
                r.cmd = CMD_INFO;
                r.res = 1;
                strcpy(r.msg, buffer);
                enviar_resposta(t->servico->pid_cliente, &r);
            }

            pthread_mutex_unlock(t->trinco);
        }

    } while (n > 0);

    waitpid(t->servico->pid_veiculo, NULL, 0); //Esperar pelo processo veiculo
    close(t->canal_fd); //fechar pipe

    //Marcar thread como terminada
    pthread_mutex_lock(t->trinco);
    telem_ativa[t->id_veiculo] = 0;
    pthread_mutex_unlock(t->trinco);

    pthread_exit(NULL);
}

void naofaznada(int s, siginfo_t *si, void *uc) {
    // Não faz nada, só serve para acordar threads bloqueadas
}

//Processa comandos introduzidos no terminal do Controlador
void processar_comando(char *linha, TDATA *td) {

    int id;

    if (strcmp(linha, "hora") == 0){
        printf("Tempo = %d\n", *td->tempo);

    }else if (strcmp(linha, "listar") == 0){
        listar_servicos(td);

    }else if (strcmp(linha, "frota") == 0){
        listar_frota(td);

    }else if (strcmp(linha, "utiliz") == 0){
        listar_utilizadores(td);

    }else if (strcmp(linha, "km") == 0){
        printf("Total de km percorridos: %d\n", *td->km_total);

    }else if (sscanf(linha, "cancelar %d", &id) == 1) {
        cancelar_servico(id, td);

    }else if (strcmp(linha, "terminar") == 0){
        //Apenas imprime a mensagem; tratamento do encerramento é feito dentro do main
        printf("[CONTROLADOR] Comando terminar recebido. A encerrar o sistema...\n");
    }else
        printf("Comando desconhecido.\n");
}


// ======= MAIN ========
int main(int argc, char *argv[]) {

    //Argumentos invalidos
    if (argc != 1) {
        printf("[CONTROLADOR] Uso: %s\n", argv[0]);
    return 0;
  }

  //Verifica se já existe algum controlador ativo, se sim encerra o programa
  if (access(CTRL_FIFO, F_OK) == 0) {
        printf("[ERRO] Já existe um controlador em execução.\n");
        exit(1);
    }

    //Ler numero de veiculos da variavel ambiente "NVEICULOS"
    int nveic = ler_nveiculos();

    //Criação do fifo do controlador
    if (mkfifo(CTRL_FIFO, 0640) == -1) {
        printf("[CONTROLADOR] Erro ao criar FIFO");
        exit(1);
    }

    //Estruturas principais do sistema (serviços, utilizadores e frota)
    SERVICO lista_servicos[MAX_SERVICOS];
    UTILIZADOR lista_utilizadores[MAX_UTILIZADORES];
    VEICULO lista_frota[MAX_VEICULOS];

    int total_servicos = 0;  //total de serviços agendados(agendados, em execução, concluidos)
    int total_veiculos_ativos = 0; //total de veiculos em viagem
    int tempo = 0; //tempo simulado
    int km_total = 0; //total de km feitos por todos os veiculos

    // inicializar utilizadores
    for (int i = 0; i < MAX_UTILIZADORES; i++) {
        lista_utilizadores[i].pid = -1;
        lista_utilizadores[i].username[0] = '\0';
    }

    // inicializar frota
    for (int i = 0; i < nveic; i++) {
        lista_frota[i].ativo = 0;
        lista_frota[i].servico_id = -1;
        lista_frota[i].pid = -1;
        lista_frota[i].percentagem = 0;
    }

    //Marcar threads de telemetria como inativas
    for (int i = 0; i < MAX_VEICULOS; i++)
        telem_ativa[i] = 0;

    //Criação e inicialização dos mutex
    pthread_mutex_t trinco;
    pthread_mutex_init(&trinco, NULL);

    //Preparar estrutura TDADA para as THREADS
    TDATA td[2];

    // Configurar TDATA para thread_pedidos
    td[0].continua = 1;
    td[0].ptrinco = &trinco;
    td[0].servicos = lista_servicos;
    td[0].utilizadores = lista_utilizadores;
    td[0].frota = lista_frota;
    td[0].total_servicos = &total_servicos;
    td[0].total_veiculos_ativos = &total_veiculos_ativos;
    td[0].tempo = &tempo;
    td[0].nveic = &nveic;
    td[0].km_total = &km_total;

    // Configurar TDATA para thread_tempo (usa o mesmo estado)
    td[1] = td[0];
    td[1].continua = 1;

    // Instalar handler SIGUSR2 para acordar threads bloqueadas
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = naofaznada;
    sigaction(SIGUSR2, &act, NULL);

    // Criar threads
    pthread_t tid_pedidos, tid_tempo;
    pthread_create(&tid_pedidos, NULL, thread_pedidos, (void *) &td[0]);
    pthread_create(&tid_tempo,   NULL, thread_tempo,   (void *) &td[1]);

    printf("[CONTROLADOR] Iniciado...\n");

    //Ciclo de comandos internos do controlador
    char cmd[32];
    while(1){

        printf("CMD> ");
        fflush(stdout);

        //Ler comandos do controlador
        if(fgets(cmd, sizeof(cmd), stdin) != NULL){

            int tam = strlen(cmd);
            if (tam > 0 && cmd[tam-1] == '\n')
                cmd[tam-1] = '\0';
        }

        pthread_mutex_lock(&trinco);
        processar_comando(cmd, &td[0]); //executar comando
        pthread_mutex_unlock(&trinco);

        //Se receber o comando "terminar sai do ciclo"
        if (strcmp(cmd, "terminar") == 0)
            break;
    }

    //Encerramento seguro do controlador
    pthread_mutex_lock(&trinco);
    cancelar_todos_os_servicos(&td[0]);  //cancelar todos os serviços (agendados e em execução)
    notificar_todos_clientes_terminar(&td[0]); //avisar todos os clientes, para que estes encerrem
    pthread_mutex_unlock(&trinco);

    //Parar threads principais
    td[0].continua = 0;
    td[1].continua = 0;
    pthread_kill(tid_pedidos, SIGUSR2);
    pthread_kill(tid_tempo,   SIGUSR2);

    //Esperar que as threads terminem
    pthread_join(tid_pedidos, NULL);
    pthread_join(tid_tempo,   NULL);

    //Esperar pelas threads ainda ativas
    for (int i=0; i<nveic; i++)
    if (telem_ativa[i])
        pthread_join(telem_thread[i], NULL);

    pthread_mutex_destroy(&trinco);

    unlink(CTRL_FIFO); //remover FIFO do controlador

    printf("[CONTROLADOR] Fim.\n");
    return 0;
}