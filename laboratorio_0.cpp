#include <iostream>
#include <string>

using namespace std;

bool par_or_not(int value) {
    return value % 2 == 0; //ver si es par o no
}

int stringlength(string str) {
    return str.length(); //.len
}

int main() {
    int value;
    cout << "Ingrese un número: ";
    cin >> value; //lee dato usuario

    cout << "Usted ha escrito el número " << value << '\n'; //print

    if (par_or_not(value)) {
        cout << value << " es un número par." << '\n';
    } else {
        cout << value << " es un número impar." << '\n';
    }

    string text;
    cout << '\n' << "Ingrese un texto: ";
    cin >> text;
    
    cout << "La longitud del primer texto ingresado es de " << stringlength(text) << " caracter/es" << '\n';
}
