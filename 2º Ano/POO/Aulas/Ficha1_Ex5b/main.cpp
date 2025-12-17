#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits> // para usar numeric_limits

using namespace std;
const int MAX_NUMS = 10;
const string extenso[MAX_NUMS] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez"};

int main() {

    // ofstream fteste("teste.txt");
   // fteste << "qualquer coisa para dentro do ficheiro" << endl;
   // fteste.close();

    string nome_ficheiro;
    cout << "Indique o nome do ficheiro: ";
    cin >> nome_ficheiro;
    cin.ignore(9999, '\n');

    ifstream ifs(nome_ficheiro);

    if(!ifs)
        cout << "Ficheiro inexistente, vou usar a consola..." << endl;

    while(true) {
        int num;
        string linha, input;

        if (!ifs) {
            cout << "Digite um numero [1-10] ou por extenso ('fim' para fim): ";
            getline(cin, linha);
        } else {
            if (!getline(ifs, linha))
                break;
        }
        istringstream iss(linha);

        if (!(iss >> num)) {
            //cin.clear
            //cin >> input
            if (linha == "fim")
                break;

            num = 1;
            while (num <= MAX_NUMS && linha != extenso[num-1])
                num++;
        }

        if (num >= 1 && num <= MAX_NUMS)
            cout << num << " <=> " << extenso[num-1] << endl;
        else
            cout << "numero invalido" << endl;

        if (!ifs) {
            cout << "Premir Enter..." << endl;
            getline(cin, linha);

        }
    }

    return 0;
}
