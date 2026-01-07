#include "Simulador.h"
#include <fstream>
#include <string>

using namespace std;

Simulador::Simulador() : ativo(true), instante(0), jardimInicializado(false){}

void Simulador::lerComandos() {

    string linha;

    cout << "\t|-------------------------------------------------------|\n";
    cout << "\t|-------- Bem Vindo ao Simulador do Jardim -------------|\n";
    cout << "\t|-------------------------------------------------------|\n";

        do {
            cout << "\n> ";
            getline(cin, linha);

            Comando cmd = parser.parse(linha, &jardim, jardimInicializado);

            executa(cmd);

        } while(ativo);
}

void Simulador::executa(const Comando &cmd) {

    switch (cmd.tipo) {

        case ComandoTipo::CMD_JARDIM: {
            int l = stoi(cmd.tokens[1]);
            int c = stoi(cmd.tokens[2]);

            if (jardim.inicializa(l, c)) {
                jardim.print();
                jardimInicializado = true;
            } else {
                cout << "[ERRO] Dimensoes invalidas para o Jardim" << endl;
            }
            break;
        }

        case ComandoTipo::CMD_FIM: {
            cout << "[INFO] A sair do Simulador" << endl;
            ativo = false;
            break;
        }

        case ComandoTipo::CMD_AVANCA: {

            if(cmd.numTokens == 1 || (cmd.numTokens == 2 && stoi(cmd.tokens[1]) == 1)){
                avancaUmInstante();
            }else{
                int n = stoi(cmd.tokens[1]);
                for(int i = 0; i < n; i++){
                    avancaUmInstante();
                }
            }
            break;
        }

        case ComandoTipo::CMD_EXECUTA: {
            if (!executaFicheiro(cmd.tokens[1])) {
                cout << "[INFO] Execucao do ficheiro " << cmd.tokens[1] << " falhada\n";
            }
            break;
        }

        case ComandoTipo::CMD_GRAVA: {
            if (!jardimInicializado) {
                cout << "[ERRO] Ainda nao existe jardim para gravar.\n";
                break;
            }

            const string& nome = cmd.tokens[1];
            copias[nome] = Snapshot(jardim, instante, jardimInicializado);

            cout << "[INFO] Copia '" << nome << "' gravada com sucesso.\n";
            break;
        }

        case ComandoTipo::CMD_RECUPERA: {
            const string& nome = cmd.tokens[1];

            auto it = copias.find(nome);
            if (it == copias.end()) {
                cout << "[ERRO] Nao existe nenhuma copia com o nome '" << nome << "'.\n";
                break;
            }

            jardim = it->second.jardim;
            instante = it->second.instante;
            jardimInicializado = it->second.jardimInicializado;

            copias.erase(it);

            cout << "[INFO] Copia '" << nome << "' recuperada e removida.\n";
            jardim.print();
            break;
        }

        case ComandoTipo::CMD_APAGA: {
            const string& nome = cmd.tokens[1];

            auto it = copias.find(nome);
            if (it == copias.end()) {
                cout << "[ERRO] Nao existe nenhuma copia com o nome '" << nome << "'.\n";
                break;
            }

            copias.erase(it);
            cout << "[INFO] Copia '" << nome << "' apagada.\n";
            break;
        }

        case ComandoTipo::CMD_MOVE: {
            char dir = cmd.tokens[0][0];

            if (!jardim.getJardineiro().estaNoJardim()) {
                cout << "[ERRO] Jardineiro fora do jardim. Use 'entra <pos>'\n";
                break;
            }

            if (!jardim.getJardineiro().podeMover()) {
                cout << "[ERRO] Limite de movimentos atingido neste instante\n";
                break;
            }

            if (!jardim.moverJardineiro(dir)) {
                cout << "[ERRO] Movimento invalido (fora dos limites)\n";
                break;
            }
            jardim.print();
            break;
        }

        case ComandoTipo::CMD_ENTRA : {
            Posicao novaPos;
            Posicao::converteLetras(cmd.tokens[1], novaPos);

            if (!jardim.PosicaoValida(novaPos.getLinhas(), novaPos.getColunas())) {
                cout << "[ERRO] Posicao '" << cmd.tokens[1] << "' fora dos limites do jardim\n";
                break;
            }

            if(!jardim.entraJardineiro(novaPos)){
                cout << "[ERRO] Limite de entradas atingido neste instante\n";
                break;
            }
            jardim.print();
            break;
        }

        case ComandoTipo::CMD_SAI : {
            if (!jardim.getJardineiro().estaNoJardim()) {
                cout << "[AVISO] Jardineiro ja esta fora do jardim.\n";
                break;
            }

            if (!jardim.saiJardineiro()) {
                cout << "[ERRO] Limite de saidas atingido neste instante\n";
                break;
            }

            jardim.print();
            break;
        }

        case ComandoTipo::CMD_PLANTA : {
            Posicao pos;
            Posicao::converteLetras(cmd.tokens[1], pos);

            char tipo = cmd.tokens[2][0];

            if (!jardim.PosicaoValida(pos.getLinhas(), pos.getColunas())) {
                cout << "[ERRO] Posicao '" << cmd.tokens[1] << "' fora dos limites do jardim\n";
                break;
            }

            if (!jardim.getJardineiro().podePlantar()) {
                cout << "[ERRO] Limite de plantacoes atingida neste instante\n";
                break;
            }

            if (!jardim.adicionarPlanta(pos, tipo)) {
                cout << "[ERRO] Nao foi possivel plantar em '" << cmd.tokens[1] << "' (ja existe planta)\n";
                break;
            }

            cout << "[INFO] Planta adicionada com sucesso em '" << cmd.tokens[1] << "'\n";
            jardim.print();
            break;
        }

        case ComandoTipo::CMD_COLHE : {
            Posicao pos;
            Posicao::converteLetras(cmd.tokens[1], pos);

            if (!jardim.PosicaoValida(pos.getLinhas(), pos.getColunas())) {
                cout << "[ERRO] Posicao '" << cmd.tokens[1] << "' fora dos limites do jardim.\n";
                break;
            }

            if (!jardim.getJardineiro().podeColher()) {
                cout << "[ERRO] Limite de colheitas neste turno atingido.\n";
                break;
            }

            if (!jardim.removerPlanta(pos)) {
                cout << "[ERRO] Nao existe nenhuma planta em '" << cmd.tokens[1] << "'.\n";
                break;
            }

            cout << "[INFO] Planta colhida com sucesso em '" << cmd.tokens[1] << "'.\n";
            jardim.print();
            break;
        }

        case ComandoTipo::CMD_LARGA : {
            if (!jardim.jardineiroLargaFerramenta()) {
                cout << "[ERRO] O jardineiro nao tem nenhuma ferramenta na mao.\n";
                break;
            }
            cout << "[INFO] Ferramenta largada. Agora esta de volta ao inventario.\n";
            break;
        }

        case ComandoTipo::CMD_PEGA : {
            int nr = stoi(cmd.tokens[1]);

            if (!jardim.jardineiroPegaFerramenta(nr)) {
                cout << "[ERRO] Nao existe nenhuma ferramenta com numero de serie " << nr << " no inventario.\n";
                break;
            }
            cout << "[INFO] Ferramenta com numero " << nr << " agora esta na mao do jardineiro.\n";
            break;
        }

        case ComandoTipo::CMD_COMPRA : {
            char tipo = cmd.tokens[1][0];

            if(!jardim.jardineiroCompraFerramenta(tipo)){
                cout << "[ERRO] Nao foi possivel comprar a ferramenta " << tipo << "\n";
            }
            cout << "[INFO] Ferramenta '" << tipo << "' comprada e adicionada ao inventario.\n";
            break;
        }

        case ComandoTipo::CMD_LPLANTAS : {

            cout << jardim.listarPlantas();
            break;
        }

        case ComandoTipo::CMD_LPLANTA : {
            Posicao pos;
            Posicao::converteLetras(cmd.tokens[1], pos);

            cout << jardim.listarPlanta(pos);
            break;
        }

        case ComandoTipo::CMD_LAREA : {
            cout << jardim.listarArea();
            break;
        }

        case ComandoTipo::CMD_LSOLO : {
            Posicao centro;
            Posicao::converteLetras(cmd.tokens[1], centro);
            int raio = 0;
            if(cmd.numTokens == 3){
                raio = stoi(cmd.tokens[2]);
            }
            cout << jardim.listarSolo(centro, raio);
            break;
        }

        case ComandoTipo::CMD_LFERR : {
            cout << jardim.listarFerramentasJardineiro();
            break;
        }

        case ComandoTipo::CMD_INVALID : {
            cout << cmd.erro << endl;
            break;
        }

        default:
            // Se chegou aqui, o comando foi validado pelo parser, mas esquecemos o case.
            cout << "[ERRO INTERNO] Tipo de comando valido mas sem logica implementada" << endl;
            break;
    }
}

bool Simulador::executaFicheiro(const string &nomeFicheiro) {

    ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        cout << "[ERRO] Nao foi possivel abrir o ficheiro de comandos: " << nomeFicheiro << endl;
        return false;
    }

    string linha;
    int linhasLidas = 0;

    cout << "[INFO] A executar ficheiro '" << nomeFicheiro << "'..." << endl;

    while(getline(ficheiro, linha)){
        linhasLidas++;

        cout << "\nFICHEIRO> " << linha << endl;

        Comando cmd = parser.parse(linha, &jardim, jardimInicializado);

        if (cmd.tipo == ComandoTipo::CMD_INVALID) {
            std::cout << "[ERRO no ficheiro, linha " << linhasLidas << "] " << cmd.erro << endl;

        } else {
            executa(cmd);
        }

        if(!ativo) {
            cout << "[INFO] Comando 'fim' encontrado e executado no ficheiro." << endl;
            break;
        }
    }
    return true;
}

void Simulador::avancaUmInstante() {
    instante++;
    cout << "\n--- Instante: " << instante << " ---" << endl;

    jardim.avancaInstante();
    jardim.print();
}


