#include <iostream>
#include <string>

//overloading vs namespaces

using namespace std;

namespace espaco1{

    int faz(int a, int b){
        return a + b;
    }
}

namespace espaco2{

    int faz(int a, int b, int c){
        return a * b * c;
    }

    int faz(int c, int d){
        return c * d;
    }
}

int main() {

    cout << espaco1::faz(4,5) << endl;
    cout << espaco2::faz(2,3, 4) << endl;
    cout << espaco2::faz(10,5) << endl;

    return 0;
}
