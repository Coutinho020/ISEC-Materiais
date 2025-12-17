#include <iostream>
#include "Cofre.h"

int main() {
    try {
        std::cout << "A criar cofre com codigo 1234..." << std::endl;
        Cofre cofre(1234);

        std::cout << "\nA testar abertura com codigo errado (4321)..." << std::endl;
        if (cofre.abre(4321))
            std::cout << "Abriu" << std::endl;
        else
            std::cout << "Nao abriu" << std::endl;

        std::cout << "\nA testar abertura com codigo correcto (1234)..." << std::endl;
        if (cofre.abre(1234))
            std::cout << "Abriu" << std::endl;
        else
            std::cout << "Nao abriu" << std::endl;

        std::cout << "\nA colocar objectos no cofre..." << std::endl;
        try {
            Valioso item1("Relogio", 1000);
            Valioso item2("Fio de ouro", 2000);

            if (cofre.colocar(item1, 1))
                std::cout << "Objecto 1 colocado com sucesso" << std::endl;
            if (cofre.colocar(item2, 2))
                std::cout << "Objecto 2 colocado com sucesso" << std::endl;

            std::cout << "\nA listar objectos:" << std::endl;
            std::cout << cofre.listarItens();

            std::cout << "\nA retirar objecto da posicao 1..." << std::endl;
            Valioso itemRetirado = cofre.retira(1);
            if (!itemRetirado.semValor())
                std::cout << "Objecto retirado: " << itemRetirado.obtemDescricao() << std::endl;

            std::cout << "\nA listar objectos:" << std::endl;
            std::cout << cofre.listarItens();
        } catch (const std::invalid_argument &e) {
            std::cout << "Erro ao manipular items: " << e.what() << std::endl;
        }

        std::cout << "\nA fechar o cofre..." << std::endl;
        if (cofre.fecha())
            std::cout << "Cofre fechado" << std::endl;

        std::cout << "\nA tentar alterar codigo (devera falhar pois esta fechado)..." << std::endl;
        if (cofre.alteraCodigo(1234, 5678))
            std::cout << "Código alterado" << std::endl;
        else
            std::cout << "Falha na alteracao do codigo" << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cout << "Erro ao criar cofre: " << e.what() << std::endl;
    }

    return 0;
}
