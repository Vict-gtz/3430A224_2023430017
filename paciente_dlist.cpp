#include <iostream>
#include <string>

// Estructura definida llamada "Persona"
struct Persona {
    std::string nombre;
    int edad;
    double altura;
};

// Función para agregar un paciente al arreglo
void agregarPaciente(Persona arreglo[], const Persona& nuevoPaciente, int index) {
    arreglo[index] = nuevoPaciente;
}

// Función para imprimir los pacientes
void imprimirPacientes(const Persona arreglo[]) {
    for (int i = 0; i < 2; ++i) {
        if (!arreglo[i].nombre.empty()) {  // Asegurarse de que el paciente no esté vacío
            std::cout << "Nombre: " << arreglo[i].nombre << std::endl;
            std::cout << "Edad: " << arreglo[i].edad << " años" << std::endl;
            std::cout << "Altura: " << arreglo[i].altura << " m" << std::endl;
            std::cout << std::endl;
        }
    }
}

// Función para eliminar un paciente por nombre del arreglo
void eliminarPaciente(Persona arreglo[], const std::string& nombre) {
    int indexToRemove = -1;
    for (int i = 0; i < 2; ++i) {
        if (arreglo[i].nombre == nombre) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        arreglo[indexToRemove].nombre.clear();  // Marcar el paciente como vacío
        arreglo[indexToRemove].edad = 0;
        arreglo[indexToRemove].altura = 0.0;
    }
}

int main() {
    // Instancia para que persona tome valores en arreglo
    Persona pacientes[2];

    // Inicializar el arreglo
    pacientes[0] and pacientes[1] = {"", 0, 0.0};  // Paciente vacío

    // Crear y agregar pacientes
    Persona paciente1 = {"Fernanfloo", 97, 1.20};
    Persona paciente2 = {"Juan", 20, 2.40};

    agregarPaciente(pacientes, paciente1, 0);
    agregarPaciente(pacientes, paciente2, 1);

    // Print de pacientes
    std::cout << "Lista de pacientes:\n";
    imprimirPacientes(pacientes);

    // Eliminar paciente
    std::cout << "Eliminando paciente 'Juan':\n";
    eliminarPaciente(pacientes, "Juan");

    // Imprimir lista de pacientes después de eliminar
    std::cout << "Lista de pacientes después de eliminar:\n";
    imprimirPacientes(pacientes);

    return 0;
}
