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
            cout << "XX El nodo ya se encuentra en el árbol [" << data << "] XX" << endl;
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

    // Busca si un valor esta en el arbol o no
    bool search(Node* node, int data) const {
        if (node == nullptr) {
            return false;  // El valor no esta en el arbol
        }

        if (node->info == data) {
            return true;  // El valor si esta en el arbol
        }

        if (data < node->info) {
            return search(node->left, data);  // Buscar en el subarbol izquierdo
        } else {
            return search(node->right, data);  // Buscar en el subarbol derecho
        }
    }

    Node* deleteNode(Node* root, int data) {
        if (root == nullptr) {
            return root;  // Base case: if the tree is empty
        }

        // Recorrer el arbol para encontrar el nodo que se desea eliminar
        if (data < root->info) {
            root->left = deleteNode(root->left, data);  // Buscar en el subarbol izquierdo
        } else if (data > root->info) {
            root->right = deleteNode(root->right, data);  // Buscar en el subarbol derecho
        } else {
            // Caso 1: Nodo con un solo hijo o sin hijos
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Caso 2: Nodo con dos hijos
            // Buscar el sucesor inorden (el nodo más pequeño en el subarbol derecho)
            Node* temp = minValueNode(root->right);

            // Copiar el valor del sucesor inorden al nodo actual
            root->info = temp->info;

            // Eliminar el sucesor inorden
            root->right = deleteNode(root->right, temp->info);
        }

        return root;
    }

    // Encontrar el valor mínimo en un subárbol
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }


public:
    Arbol() : root(nullptr) {}

    // Metodo publico para borrar un nodo en el arbol
    void deleteValue(int data) {
        root = deleteNode(root, data);
    }

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

    bool search(int data) const {
        return search(root, data);
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
        cout << "4 -> Buscar nodo <-" << endl; //eliminar o reemplazar
        cout << "5 -> Insertar valor al arbol <-" << endl;
        cout << "6 -> Finalizar <-" << endl;

        cout << "\nxx Ingrese una de las opciones entregadas xx : ";

        if (!(cin >> opcion)) { // Booleano, si es true entonces ingresará acá
            cin.clear(); // Limpia bool
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
            continue;
        } // (Sin esto el código corría infinitamente)

        // Se realizan opciones dependiendo lo que eligió el usuario
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
                cout << "\n\n++ Que quieres hacer con este valor?\n1 -> Eliminarlo <-\n2 -> Reemplazarlo <-" << endl;
                while (!(opcionn == 1 || opcionn ==2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[1 o 2]: ";
                    cin >> opcionn;
                }
                if (opcionn == 1) {
                    arbol.deleteValue(trabajando);  // Llamar a la función pública para eliminar el nodo
                    cout << "-> Nodo eliminado con éxito <-" << endl; // Y agrega un aviso de que se elimino
                    break; 
                } else {
                    arbol.deleteValue(trabajando); 
                    //acá no agregué el break; para que pase directo a preguntar el valor que se va a agregar en el case 5
                }
            }
            case 5: { // Agregar valores al árbol
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

                arbol.insert(valor_nuevo); // Agrega el valor al arbol
                break;
            }
            case 6: {
                cout << "Programa finalizado" << endl; // Finaliza programa
                return 0;
            }
        }
    }
}