#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root = nullptr;

    // Metodo recursivo privado para insertar un nodo en el arbol binario de busqueda
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            // Crear un nuevo nodo si se encuentra una posicion vacia
            return createNode(data);
        }

        if (data < node->info) {
            // Insertar en el subarbol izquierdo
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            // Insertar en el subarbol derecho
            node->right = insertNode(node->right, data);
        } else {
            // El dato ya esta en el arbol
            cout << "El nodo ya se encuentra en el árbol: " << data << endl;
        }

        return node;
    }

    // Metodo recursivo privado para imprimir el arbol en preorden
    void printPreOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->info << " "; // Imprimir el dato del nodo actual
        printPreOrder(node->left);  // Recorrer el subarbol izquierdo
        printPreOrder(node->right); // Recorrer el subarbol derecho
    }

    // En inorden
    void printInOrder(Node *node) const {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        cout << node->info << " ";
        printInOrder(node->right);
    }

    // Y en posorden
    void printPosOrder(Node *node) const {
        if (node == nullptr) {
            return;
        }
        printPosOrder(node->left);
        printPosOrder(node->right);
        cout << node->info << " ";
    }

public:
    Arbol() : root(nullptr) {}

    // Metodo publico para insertar un nodo en el arbol
    void insert(int data) {
        root = insertNode(root, data);
    }

    // Metodo publico para imprimir el arbol en preorden, inorden y posorden
    void printPreOrder() const {
        printPreOrder(root);
        cout << endl;
    }

    void printInOrder() const {
        printInOrder(root);
        cout << endl;
    }

    void printPosOrder() const {
        printPosOrder(root);
        cout << endl;
    }

};

int main() {
    Arbol arbol;

    // Insertar numeros en el arbol usando el metodo insert
    arbol.insert(120);
    arbol.insert(87);
    arbol.insert(140);
    arbol.insert(43);
    arbol.insert(99);
    arbol.insert(130);
    arbol.insert(22);
    arbol.insert(65);
    arbol.insert(93);
    arbol.insert(135);
    arbol.insert(56);


    // Menu con diversas opciones para el usuario
    while (true) {
        int opcion = 0;
        string empt;

        cout << "\n\n[ ---------- Menu ------------ ]" << endl;
        cout << "1 -> Mostrar arbol en preorden <-" << endl;
        cout << "2 -> Mostrar arbol en inorden <-" << endl;
        cout << "3 -> Mostrar arbol en posorden <-" << endl;
        cout << "4 -> Elegir elemento a editar <-" << endl;
        cout << "5 -> Finalizar <-" << endl;

        cout << "\nxx Ingrese una de las opciones entregadas xx : ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1: {
                // Imprimir el arbol en preorden
                cout << "++ Recorrido en preorden: " << endl;
                arbol.printPreOrder();
                cin >> empt; // Esto es para que no salga el menu antes de siquiera poder leer lo que entrega la opcion
                break;
            }
            case 2: {
                // Imprimir el arbol en inorden
                cout << "++ Recorrido en inorden: " << endl;
                arbol.printInOrder();
                cin >> empt;
                break;
            }
            case 3: {
                // Imprimir el arbol en posorden
                cout << "++ Recorrido en posorden: " << endl;
                arbol.printPosOrder();
                cin >> empt;
                break;
            }
            case 4: {
                cin >> empt;
                break;
            }
            case 5: {
                cout << "Programa finalizado" << endl; // Finaliza programa
                return 0;
            }
        }
    }
}