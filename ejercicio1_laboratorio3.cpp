#include <iostream>
#include <stack>

using namespace std;

void agregar_valor(stack<int> &stack, int maximo_cantidad) {
  int valor_usuario;

  if (stack.size() < maximo_cantidad) {
    cout << "\nEl valor a agregar será...: ";
    cin >> valor_usuario; // Lee el valor para hacer push

    stack.push(valor_usuario);
    cout << "\nSe ha agregado el valor.";
  } else {
    cout << "\nLa pila está llena.";
  }
}

void mostrar_valores(stack<int> &stack) {
  std::stack<int> temp = stack; // Hacer una copia temporal
  while (!temp.empty()) {
    cout << temp.top() << " ";
    temp.pop();
  }
  cout << endl;
}

void menu() {
  int maximo_cantidad;
  cout << "\n[Cantidad máxima de valores de pila: ]" << endl;
  cin >> maximo_cantidad;

  stack<int> stack;
  int respuesta = 0;
  
  // Opciones del menú
  while (true) {
    cout << "\n\n\n------------[Menú]------------" << endl;
    cout << "1 -> Agregar valor." << endl; // push
    cout << "2 -> Eliminar valor." << endl; // pop
    cout << "3 -> Mostrar valores." << endl;
    cout << "4 -> Salir.\n" << endl;

    // Devolverse si está mala la respuesta
    cin >> respuesta;
    if (respuesta < 1 || respuesta > 4) {
      cout << "[Seleccione una opción entre las disponibles (escribir número)]" << endl;
      continue; 
    }

    // Caso de respuesta correcta
    switch (respuesta) {
      case 1: {
        agregar_valor(stack, maximo_cantidad);
        break;
      }
      case 2: {
        if (!stack.empty()) {
          stack.pop();
          cout << "Se ha eliminado el primer elemento de la pila" << endl;
        } else {
          cout << "[La pila está vacía]" << endl;
        }
        break;
      }
      case 3: {
        if (!stack.empty()) {
          mostrar_valores(stack);
        } else {
          cout << "\nLa pila se encuentra vacía." << endl;
        }
        break;
      }
      case 4: {
        return; // Fin del programa
      }
    }
  }
}

int main() {
  menu();
}