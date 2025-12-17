#include "ArmarioFichas.h"
#include <sstream>

using namespace std;

ArmarioFichas::ArmarioFichas() : nrClientes(0), clientes(nullptr){}

ArmarioFichas::ArmarioFichas(const ArmarioFichas &outro) : nrClientes(outro.nrClientes), clientes(nullptr){
    if(nrClientes < 1){
        nrClientes = 0;
        return;
    }
    clientes = new Cliente*[outro.nrClientes];
    for(int i = 0; i < nrClientes; i++){
        clientes[i] = new Cliente(*outro.clientes[i]);
    }
}

ArmarioFichas &ArmarioFichas::operator=(ArmarioFichas outro){
    swap(nrClientes, outro.nrClientes);
    swap(clientes, outro.clientes);
    return *this;
}

int ArmarioFichas::procuraCliente(int nif) const{
    for(int i = 0; i < nrClientes; i++){
        if(clientes[i]->obtemNIF()==1)
            return i;
    }
    return -1;
}

bool ArmarioFichas::adicionarCliente(const string &nome, int nif) {
    if(nome.empty() || nif < 0 || procuraCliente(nif) != -1)
        return false;

    Cliente **novoClientes = new Cliente*[nrClientes + 1];
    for(int i = 0; i < nrClientes; i++){
        novoClientes[i] = clientes[i];
    }
    novoClientes[nrClientes] = new Cliente(nome, nif);
    nrClientes++;
    delete [] clientes;
    clientes = novoClientes;
    return true;
}

bool ArmarioFichas::removerCliente(int nif) {
    //TODO: Fazer mais tarde!!!
    return false;
}

bool ArmarioFichas::registaConsulta(int nif) {
    int i = procuraCliente(nif);
    if(i == -1)
        return false;

    clientes[i]->novaConsulta();
    return true;
}

string ArmarioFichas::getLista() const {
    ostringstream oss;

    oss << "Listagem de Consultas: " << endl;

    for(int i = 0; i < nrClientes; i++){
        oss << clientes[i]->obtemDesc() << "\n";
    }

    return oss.str();
}

void ArmarioFichas::esvaziar() {
    for(int i = 0; i < nrClientes; i++)
        delete clientes[i];

    delete [] clientes;
    clientes = nullptr;
    nrClientes = 0;
}

ArmarioFichas::~ArmarioFichas() {
    for(int i = 0; i < nrClientes; i++)
        delete clientes[i];

    delete [] clientes;
}

ArmarioFichas::InfoCliente ArmarioFichas::getInfoCliente(int nif) {
    int i = procuraCliente(nif);
    if(i == -1)
        return InfoCliente("", 0, false);

    return InfoCliente(clientes[i]->obtemNome(), clientes[i]->obtemNumConsultas(), true);
}



