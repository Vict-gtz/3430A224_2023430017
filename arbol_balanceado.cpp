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

void Insertar(Arbol* a, int dat);
void Borrar(Arbol* a, int dat);

/*
int Buscar(Arbol a, int dat);//
int EsHoja(pNodo r);//
int NumeroNodos(Arbol a, int* c);//
int AlturaArbol(Arbol a, int* altura);//
int Altura(Arbol a, int dat);//
void PreOrden(Arbol, std::ofstream &fp);//
*/

// Funciones de equilibrado:
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechoDerecho(Arbol* raiz, pNodo nodo);
void Rotaizquierdoizquierdo(Arbol* raiz, pNodo nodo);
void RotaDerechoizquierdo(Arbol* raiz, pNodo nodo);
void RotaizquierdoDerecho(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares: */
void Podar(Arbol* a);

/*
void auxContador(Arbol a, int*);//
void auxAltura(Arbol a, int, int*);//
*/

void menu();
void GenerarGrafo(Arbol);

/////////////

Nodo* minValueNodo(Nodo* nodo) {
        Nodo* current = nodo;
        while (current && current->izquierdo != NULL) {
            current = current->izquierdo;
        }
        return current;
    }

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

void Borrar(Arbol *a, int dat) {
    if (*a == NULL) {
        return;  // Si el árbol está vacío, no se hace nada
    }

    if (dat < (*a)->dato) {
        // Se busca en subarbol izquierdo por tamaño de dato
        Borrar(&(*a)->izquierdo, dat);
    } else if (dat > (*a)->dato) {
        // Se busca en subarbol derecho por tamaño de dato
        Borrar(&(*a)->derecho, dat);
    } else {
        // Se encontró el nodo a borrar
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
            Borrar(&(*a)->derecho, temp->dato);  
        }
    }
}

void Equilibrar(Arbol *a, pNodo nodo, int rama, int nuevo) {
  int salir = FALSE;

  while (nodo && !salir) {
    if (nuevo) {
      if (rama == IZQUIERDO) {
        nodo->FE -= 1;
      } else {
        nodo->FE += 1;
      }
    } else {
      if (rama == IZQUIERDO) {
        nodo->FE += 1;
      } else {
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

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}

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

/////////////

void menu() {
        cout << "\n\n[ ---------- Menu ------------ ]" << endl;
        cout << "1 -> Mostrar arbol <-" << endl;
        cout << "2 -> Buscar nodo <-" << endl; // Borrar o reescribir
        cout << "3 -> Insertar valor al arbol <-" << endl;
        cout << "4 -> Generar grafo <-" << endl;
        cout << "5 -> Finalizar <-" << endl;

        cout << "\nxx Ingrese una de las opciones entregadas xx : ";
}

int main() {
    Arbol arbol = NULL;

    // Insertar numeros en el arbol usando el metodo insert
    Insertar(&arbol, 120);
    Insertar(&arbol, 87);
    Insertar(&arbol, 140);
    Insertar(&arbol, 43);
    Insertar(&arbol, 99);
    Insertar(&arbol, 130);
    Insertar(&arbol, 22);
    Insertar(&arbol, 65);
    Insertar(&arbol, 93);
    Insertar(&arbol, 135);
    Insertar(&arbol, 56);


    // Menu con diversas opciones para el usuario
    while (true) {
        int opcion = 0;
        string empt;

        //Mostrar menu
        menu(); 

        if (!(cin >> opcion)) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        } 

        // Opcion segun usuario
        switch (opcion) {
            // Mostrar arbol
            case 1: {
                cout << "++ Arbol en preorden: ";
                //PreOrden(arbol);
                cin >> empt; 
                break;
            }
            // Borrar / Reescribir
            case 2: {
                /*
                int trabajando = 0;
                int opcionn = 0;
                arbol.printInOrder(); // Muestra el árbol al usuario

                // Pregunta el valor que quiere utilizar
                cout << "++ Con que valor quieres trabajar? :";
                while (true) {
                    if (cin >> trabajando) {
                        // Verifica si el valor existe en el árbol
                        if (arbol.search(trabajando)) {
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
                cout << "\n\n++ Que quieres hacer con este valor?\n1 -> Borrarlo <-\n2 -> Reemplazarlo <-" << endl;
                while (!(opcionn == 1 || opcionn ==2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[1 o 2]: ";
                    cin >> opcionn;
                }
                if (opcionn == 1) {
                    arbol.deleteValue(trabajando);  // Llamar a la función pública para Borrar el nodo
                    cout << "-> Nodo eliminado con éxito <-" << endl; // Y agrega un aviso de que se elimino
                    break; 
                } else {
                    arbol.deleteValue(trabajando); 
                    //acá no agregué el break; para que pase directo a preguntar el valor que se va a agregar en el case 5
                }
                */
            }
            // Insertar valor
            case 3: { // Agregar valores al árbol
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
            //Generar grafo
            case 4: {
                GenerarGrafo(arbol); 
                cout << "Se ha creado grafo.txt" << endl;
                break;
            }
            // Finalizar
            case 5: {
                Podar(&arbol); // Muere arbol
                cout << "Programa finalizado" << endl; 
                return 0;
            }
        }
    }
}