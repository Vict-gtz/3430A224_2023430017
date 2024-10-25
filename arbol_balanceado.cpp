#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

#define TRUE 1
#define FALSE 0

enum {IZQUIERDO, DERECHO};


struct Nodo {
    int dato;
    int FE;
    Nodo *izquierdo;
    Nodo *derecho;
    Nodo *padre;
};

typedef Nodo *pNodo;
typedef Nodo *Arbol;


/* Funciones de edicion */
void Insertar(Arbol* a, int dat);
void Eliminar(Arbol* a, int dat);
bool Buscar(Arbol a, int dat);

/* Funciones de equilibrado */
void PreOrden(Arbol a, std::ofstream &fp);
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechoDerecho(Arbol* raiz, pNodo nodo);
void Rotaizquierdoizquierdo(Arbol* raiz, pNodo nodo);
void RotaDerechoizquierdo(Arbol* raiz, pNodo nodo);
void RotaizquierdoDerecho(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares */
void Podar(Arbol* a);
void menu();
void GenerarGrafo(Arbol);
void MostrarArbol(Arbol a);

Nodo* minValueNodo(Nodo* nodo) {
    Nodo* current = nodo;
    while (current && current->izquierdo != NULL) {
        current = current->izquierdo;
    }
    return current;
}


/* Funciones de edicion */
void Insertar(Arbol *a, int dat) {
    pNodo padre = NULL;
    pNodo actual = *a;

    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    if (actual != NULL)
        return;

    if (padre == NULL) {
        *a = new Nodo{dat, 0, NULL, NULL, NULL};
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    } else if (dat > padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
}

void Eliminar(Arbol *a, int dat) {
    if (*a == NULL) {
        return;  // Si el árbol está vacío, no se hace nada
    }

    if (dat < (*a)->dato) {
        // Se busca en subarbol izquierdo por tamaño de dato
        Eliminar(&(*a)->izquierdo, dat);
    } else if (dat > (*a)->dato) {
        // Se busca en subarbol derecho por tamaño de dato
        Eliminar(&(*a)->derecho, dat);
    } else {
        // Se encontró el nodo a Eliminar
        if ((*a)->izquierdo == NULL && (*a)->derecho == NULL) {
            delete *a;  // Se elimina el nodo
            *a = NULL;  
        } else if ((*a)->izquierdo == NULL) {
            pNodo temp = *a; 
            *a = (*a)->derecho; 
            delete temp;  
        } else if ((*a)->derecho == NULL) {
            pNodo temp = *a;
            *a = (*a)->izquierdo;  
            delete temp;
        } else {
            pNodo temp = minValueNodo((*a)->derecho); 
            (*a)->dato = temp->dato;  
            Eliminar(&(*a)->derecho, temp->dato);  
        }
    }
}

bool Buscar(Arbol a, int dat) {
    if (a == nullptr) {
        return false;  // El valor no esta en el arbol
    }

    if (a->dato == dat) {
        return true;  // El valor si esta en el arbol
    }

    if (dat < a->dato) {
        return Buscar(a->izquierdo, dat);  // Buscar en el subarbol izquierdo
    } else {
        return Buscar(a->derecho, dat);  // Buscar en el subarbol derecho
    }
}


/* Funciones de equilibrado */

void PreOrden(Arbol a, std::ofstream &fp) {
    if (a) {
        fp << a->dato << ";\n";
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << ";\n";
            PreOrden(a->izquierdo, fp);
        }
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << ";\n";
            PreOrden(a->derecho, fp);
        }
    }
}

void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        }
        else{
            if (rama == IZQUIERDO){
                nodo->FE += 1;
            } 
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaizquierdoDerecho(a, nodo);
            else
                Rotaizquierdoizquierdo(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechoizquierdo(a, nodo);
            else
                RotaDerechoDerecho(a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void RotaizquierdoDerecho(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        }
        else {
            Padre->izquierdo = R;
        }
    }
    else
        *raiz = R;

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
        case -1: Q->FE = 0; P->FE = 1; break;
        case 0: Q->FE = 0; P->FE = 0; break;
        case 1: Q->FE = -1; P->FE = 0; break;
    }

    R->FE = 0;
}

void RotaDerechoizquierdo(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    }
    else
        *a = R;

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

void Rotaizquierdoizquierdo(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo B = Q->derecho;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void RotaDerechoDerecho(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo B = Q->izquierdo;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;
    
    if (B){
        B->padre = P;
    } 
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}


/* Funciones auxiliares */

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}

void menu() {
        cout << "\n\n[ ---------- Menu ------------ ]" << endl;
        cout << "1 -> Mostrar arbol <-" << endl;
        cout << "2 -> Buscar nodo <-" << endl; // Eliminar o reescribir
        cout << "3 -> Insertar valor al arbol <-" << endl;
        cout << "4 -> Generar grafo <-" << endl;
        cout << "5 -> Finalizar <-" << endl;

        cout << "\nxx Ingrese una de las opciones entregadas xx : ";
}

void GenerarGrafo(Arbol ArbolInt) {
    std::ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "nodo [style=filled fillcolor=yellow];\n";

    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
    PreOrden(ArbolInt, fp);

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void MostrarArbol(Arbol a) {
    if (a) {
        cout << a->dato << " ";
        MostrarArbol(a->izquierdo);
        MostrarArbol(a->derecho);
    }
}


/* Corre el codigo */

int main() {
    Arbol arbol = NULL;

    // Insertar numeros en el arbol usando metodo Insertar
    Insertar(&arbol, 60);
    Insertar(&arbol, 40);
    Insertar(&arbol, 90);
    Insertar(&arbol, 75);
    Insertar(&arbol, 68);
    Insertar(&arbol, 97);
    Insertar(&arbol, 45);

    // Menu con diversas opciones para el usuario
    while (true) {
        int opcion = 0;

        // Mostrar menu
        menu(); 

        // Le pide opcion al usuario
        if (!(cin >> opcion)) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        } 

        // Opcion segun usuario
        switch (opcion) {
            case 1: {
                // Mostrar arbol

                cout << "++ Valores del arbol: ";
                MostrarArbol(arbol);
                break;
            }
            case 2: {
                // Eliminar / Reescribir
                int trabajando = 0;
                int opcionn = 0;

                // Pregunta el valor que quiere utilizar
                cout << "\n++ Con que valor quieres trabajar? [";
                MostrarArbol(arbol);
                cout << "] :";

                while (true) {
                    if (cin >> trabajando) {
                        // Verifica si el valor existe en el árbol
                        if (Buscar(arbol, trabajando)) {
                            break;  // Valor correcto: continua
                        } else {
                            cout << "XX El valor no está en el árbol, intente otra vez XX: ";
                        }
                    } else {  // Valor incorrecto: limpia buffer y vuelve a pedir
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "xx Ingrese un valor numérico válido xx: ";
                    }
                }

                // Pregunta qué quiere hacer con este valor
                cout << "\n\n++ Que quieres hacer con este valor?\n1 -> Eliminarlo <-\n2 -> Reemplazarlo <-" << endl;

                while (!(opcionn == 1 || opcionn ==2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[1 o 2]: ";
                    cin >> opcionn;
                }

                if (opcionn == 1) {
                    Eliminar(&arbol, trabajando);  // Llamar a la función para eliminar el nodo
                    cout << "-> Nodo eliminado con éxito <-" << endl; // Y agrega un aviso de que se elimino
                    break; 
                } else {
                    Eliminar(&arbol, trabajando); // Tambien llama, pero no tiene el brak, por lo cual se agrega valor en caso 3
                }
            }
            case 3: { 
                // Insertar valor
                int valor_nuevo = 0;

                cout << "\n++ Valor nuevo a agregar al arbol: ";

                while (true) {
                    if (cin >> valor_nuevo) { // Valor correcto ingresado
                        break;
                    } else { // Valor incorrecto: limpia buffer y pregunta otra vez
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "xx Ingrese un valor numérico válido xx: ";
                    }
                }

                Insertar(&arbol, valor_nuevo); // Agrega el valor al arbol
                break;
            }
            case 4: {
                //Generar grafo
                
                GenerarGrafo(arbol); 
                cout << "Se ha creado grafo.txt" << endl;
                break;
            }
            case 5: {
                // Finalizar

                Podar(&arbol); // Muere arbol
                cout << "Programa finalizado" << endl; 
                return 0;
            }
        }
    }
}