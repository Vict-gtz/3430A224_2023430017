#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;


void mostrar_pilas(const vector<stack<string>> &pilas) {
    cout << "\n[Pilas actuales:]\n------------------------------";
    for (int i = 0; i < pilas.size(); ++i) {
        cout << "\n> Pila " << i + 1 << ": ";

        // Crea un vector para así mostrar los datos en orden inverso
        vector<string> vector_temp;
        stack<string> temp = pilas[i];//almacenandolo en una pila temporal

        while (!temp.empty()) {
            vector_temp.push_back(temp.top());//y despuès almacenando esos datos temporales en el vector
            temp.pop();
        }

        if (vector_temp.empty()) {
            cout << "[Vacía]";
        } else {
            for (int w = vector_temp.size() - 1; w >= 0; --w) {
                cout << vector_temp[w] << " ";
            }
        }
    }
    cout << "\n------------------------------" << endl;
}

// Se mueve un contenedor de una pila a otra manualmente por el usuario
void mover_contenedor(vector<stack<string>> &pilas, int origen, int destino) {
    if (origen < 1 || origen > 4 || destino < 1 || destino > 4) {
        cout << "XX[El valor debe ser entre 1 y 4]XX";
        return;
    }
    origen--; destino--; // Ajustar a índice 0
    if (pilas[origen].empty()) {
        cout << "XX[La pila está vacía]XX\n";
        return;
    }
    if (pilas[destino].size() >= 4) {
        cout << "XX[La pila está llena]XX\n";
        return;
    }

    string contenedor = pilas[origen].top();
    pilas[origen].pop();
    pilas[destino].push(contenedor);
    cout << "Contenedor modificado excitosamente\n" << endl;
}

void agregar_contenedor(vector<stack<string>> &pilas, int pila, const string &contenedor) {
    if (pila < 1 || pila > 4) {
        cout << "\n\nXX[El valor debe ser entre 1 y 4]XX";
        return;
    }
    pila--; // Ajustar a índice 0
    if (pilas[pila].size() >= 4) {
        cout << "\n\nXX[La pila está llena]XX\n";
        return;
    }

    pilas[pila].push(contenedor);
    cout << "\nSe ha agregado el contenedor '" << contenedor << "' a la pila Nº" << pila + 1 << endl;
}

void eliminar_contenedor(vector<stack<string>> &pilas, int pila) {
    if (pila < 1 || pila > 4) {
        cout << "XX[El valor debe ser entre 1 y 4]XX";
        return;
    }
    pila--; // Ajustar a índice 0
    if (pilas[pila].empty()) {
        cout << "\nLa pila está vacía, no hay contenedores para eliminar.\n";
        return;
    }

    string contenedor = pilas[pila].top();
    pilas[pila].pop();
    cout << "\nSe ha eliminado el contenedor: " << contenedor << " de la Pila " << pila + 1 << endl;
}

// Menú
void menu() {
    vector<stack<string>> pilas(4);  // 4 pilas de contenedores
    int opcion = 0;

    while (opcion != 4) {
        cout << "\n  ----= [Menú] =----\n";
        cout << "1 -> Agregar contenedor\n";
        cout << "2 -> Mover contenedor\n";
        cout << "3 -> Eliminar contenedor\n";
        cout << "4 -> Finalizar\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        //multiples opciones
        switch (opcion) {
            case 1: {
                int pila;
                string contenedor;
                cout << "+ Seleccione la pila [1-4]: ";
                cin >> pila;
                cout << "+ Ingrese el nombre del contenedor: ";
                cin >> contenedor;
                agregar_contenedor(pilas, pila, contenedor);
                mostrar_pilas(pilas);
                break;
            }
            case 2: {
                int origen, destino;
                cout << "Seleccione la pila de origen (1-4): ";
                cin >> origen;
                cout << "Seleccione la pila de destino (1-4): ";
                cin >> destino;
                mover_contenedor(pilas, origen, destino);
                mostrar_pilas(pilas);
                break;
            }
            case 3: {
                int pila;
                cout << "Seleccione la pila (1-4): ";
                cin >> pila;
                eliminar_contenedor(pilas, pila);
                mostrar_pilas(pilas);
                break;
            }
            case 4: {
                cout << "Saliendo del programa...\n";
                break;
            }
        }
    }
}

int main() {
    menu();
}