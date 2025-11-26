#include "Simulador.h"
#include <fstream>
#include <string>

using namespace std;

Simulador::Simulador() : ativo(true), instante(0), jardimInicializado(false)
    , movimentos(0), entradasEsaidas(0), plantacoes(0), colheitas(0){

}

void Simulador::limpaContadoresAcao() {
    movimentos = 0;
    entradasEsaidas = 0;
    plantacoes = 0;
    colheitas = 0;
}

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
                cout << "[ERRO] Dimensoes invalidas para o Jardim." << endl;
            }
            break;
        }

        case ComandoTipo::CMD_FIM: {
            cout << "[INFO] A sair do Simulador." << endl;
            ativo = false;
            break;
        }

        case ComandoTipo::CMD_AVANCA: {

            if(cmd.numTokens == 1 || (cmd.numTokens == 2 && stoi(cmd.tokens[1]) == 1)){
                instante++;
                cout << "\n--- Instante: " << instante << " ---" << endl;
                cout << "[Informacoes sobre a transformacao do Jardim com o avancar do instante]\n";
                jardim.print();
                limpaContadoresAcao();
            }else{
                int n = stoi(cmd.tokens[1]);
                for(int i = 0; i < n; i++){
                    instante++;
                    cout << "\n--- Instante: " << instante << " ---" << endl;
                    cout << "[Informacoes sobre a transformacao do Jardim com o avancar do instante]\n";
                    jardim.print();
                    limpaContadoresAcao();
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
            cout << "[INFO] Comando 'grava' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_RECUPERA: {
            cout << "[INFO] Comando 'recupera' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_APAGA: {
            cout << "[INFO] Comando 'apaga' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_MOVE: {
            if (movimentos >= Settings::Jardineiro::max_movimentos) {
                cout << "[AVISO] Limite de movimentos (" << Settings::Jardineiro::max_movimentos
                     << ") atingido neste instante\n";
                break;
            }

            char dir = cmd.tokens[0][0];

            if(jardim.getJardineiro().move(dir, jardim)){
                movimentos++;
                jardim.print();
             }else{
                cout << "[AVISO] Movimento invalido ou Jardineiro fora do jardim\n";
             }
            break;
        }

        case ComandoTipo::CMD_ENTRA : {
            if (entradasEsaidas >= Settings::Jardineiro::max_entradas_saidas) {
                cout << "[AVISO] Limite de entradas/saidas (" << Settings::Jardineiro::max_entradas_saidas
                     << ") atingido." << endl;
                break;
            }
            Posicao novaPos;
            Posicao::converteLetras(cmd.tokens[1], novaPos);
            if(!jardim.PosicaoValida(novaPos.getLinhas(), novaPos.getColunas())){
                cout << "[ERRO] Posicao '" << cmd.tokens[1] << "' fora dos limites do jardim\n";
                break;
            }
            jardim.getJardineiro().entra(novaPos);
            entradasEsaidas++;
            jardim.print();
            break;
        }

        case ComandoTipo::CMD_SAI : {
            if (entradasEsaidas >= Settings::Jardineiro::max_entradas_saidas) {
                cout << "[AVISO] Limite de entradas/saidas (" << Settings::Jardineiro::max_entradas_saidas << ") atingido." << endl;
                break;
            }
            if(jardim.getJardineiro().sai()){
                entradasEsaidas++;
                jardim.print();
            }else{
                cout << "[AVISO] Jardineiro ja esta fora do jardim\n";
            }
            break;
        }

        case ComandoTipo::CMD_PLANTA : {
            if(plantacoes >= Settings::Jardineiro::max_plantacoes){
                cout << "[AVISO] Limite de plantacoes (" << Settings::Jardineiro::max_plantacoes << ") atingido." << endl;
                break;
            }
            plantacoes++;
            cout << "[INFO] Comando 'planta' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_COLHE : {
            if(colheitas >= Settings::Jardineiro::max_colheitas){
                cout << "[AVISO] Limite de plantacoes (" << Settings::Jardineiro::max_colheitas << ") atingido." << endl;
                break;
            }
            colheitas++;
            cout << "[INFO] Comando 'colhe' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_LARGA : {
            cout << "[INFO] Comando 'larga' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_PEGA : {
            cout << "[INFO] Comando 'pega' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_COMPRA : {
            cout << "[INFO] Comando 'compra' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_LPLANTAS : {
            cout << "[INFO] Comando 'lpantas' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_LPLANTA : {
            cout << "[INFO] Comando 'lpanta' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_LAREA : {
            cout << "[INFO] Comando 'larea' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_LSOLO : {
            cout << "[INFO] Comando 'lsolo' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_LFERR : {
            cout << "[INFO] Comando 'ferr' ainda nao Implementado\n";
            break;
        }

        case ComandoTipo::CMD_INVALID : {
            cout << cmd.erro << endl;
            break;
        }

        default:
            // Se chegou aqui, o comando foi validado pelo parser, mas esquecemos o case.
            cout << "[ERRO INTERNO] Tipo de comando valido mas sem logica implementada." << endl;
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


