#include <iostream>
#include <string>

using namespace std;

int main() {

    int idade;
    string nome;
    nome = "Novo nome";
    cout << "string: " << nome;
    nome += " concatenar";
    cout << "\nString: " << nome << "\nNum de caracteres: " << nome.length() << endl;
    cout << "Nome: ";
  //  cin >> nome;  //só consegue ler o primeiro nome
   getline(cin, nome);

    do {
        cout << "Idade: ";
        cin >> idade;

        if (idade <= 0 || cin.fail()) { //verificar se a idade é correta ou se não é um inteiro
            cin.clear(); //limpar o erro;
            cin.ignore(1000, '\n'); //Ver a documentacao para indicar o maior numero possivel
            cout << "Valor para idade incorreto!!! Insira um valor valido!!" << endl;
            idade = -1;
        }
    } while (idade <= 0);

    cout << "\nNome: " << nome << "\nIdade: " << idade << endl << endl;

    int num_caracteres = 0, i = 0;

    for(i = 0; nome[i] == ' '; i++);

    while(i < nome.length()){
        if(nome[i] != ' '){
            cout << nome[i] << endl;
            num_caracteres++;
            i++;

        }else if(nome[i] == ' ' && nome[i + 1] == ' '){
            i++;

        }else{
            cout << nome[i] << endl;
            i++;
        }
    }

    cout << "\nNumero de carateres: " << num_caracteres;

    return 0;
}
