#include <iostream>

using namespace std;

/*

//alinea a

int multiplica(){
    return 1;
}

int multiplica(int n1){
    return n1;
}

int multiplica(int n1, int n2){
    return n1 * n2;
}

int multiplica(int n1, int n2, int n3){
    return n1 * n2 * n3;
}

*/

int multiplica(int n1 = 1, int n2 = 1, int n3 = 1){
    return n1 * n2 * n3;
}

int main() {

    cout << "\n" << multiplica() << "\n" << multiplica(5);
    cout << endl << multiplica(2,3) << endl << multiplica(2,3,4);

    return 0;
}
