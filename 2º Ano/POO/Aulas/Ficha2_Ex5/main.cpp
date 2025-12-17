#include <iostream>

using namespace std;

int & seleciona(int &a, int &b, char c){

    if(c == 'm'){
        if(a < b){
            return a;
        }else{
            return b;
        }
    }else if(c == 'M'){
        if(a > b){
            return a;
        }else{
            return b;
        }
    }else if(c == 'p'){
        return a;
    }else if(c == 'u'){
        return b;
    }else{
        throw c;
    }
}

int main() {

    int a = 5, b = 10;

 try{

     seleciona(a, b, 'm') = 0;
     cout << "a = " << a << " b = " << b;

     a = 5, b = 10;

     seleciona(a, b, 'M') -= 3;
     cout << "\na = " << a << " b = " << b;

 } catch(char c){

  cout << "Erro: " << c << endl;
  cout << "Insira um valor valido!\n";

 }
    return 0;
}
