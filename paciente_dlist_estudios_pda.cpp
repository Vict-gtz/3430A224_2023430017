#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct pacientes {
    int numero_lista;
    int prioridad;
    string nombre;
    string apellido;
    int edad;
    double imc;
    double a1c;
};

void create_newfile() {
    std::ofstream newFile("pacientes.csv");
    newFile << "Nº,Prioridad,Nombre,Apellido,Edad,IMC,A1C\n";
    newFile.close();
}

void read_file() {
    std::ifstream csvFile("pacientes.csv"); // Abrir csv

    if (!csvFile) { // Crea archivo si no existe
        create_newfile();
        std::cerr << "El archivo 'pacientes.csv' ha sido creado\n";
        return;
    }

    // Leer línea por línea (se salta la primera)
    std::string line;
    getline(csvFile, line);

    while (getline(csvFile, line)) {
        stringstream ss(line);
        pacientes pacientes;
        string field;

        getline(ss, field, ',');
        pacientes.numero_lista = stoi(field); // Nº

        getline(ss, field, ',');
        pacientes.prioridad = stoi(field); // Prioridad

        getline(ss, pacientes.nombre, ','); // Nombre

        getline(ss, pacientes.apellido, ','); // Apellido

        getline(ss, field, ',');
        pacientes.edad = stoi(field); // Edad

        getline(ss, field, ',');
        pacientes.imc = stod(field); // IMC

        getline(ss, field, ',');
        pacientes.a1c = stod(field); // A1C

        // Imprimir registro leído
        std::cout << "Nº: " << pacientes.numero_lista 
                  << ", Prioridad: " << pacientes.prioridad
                  << ", Nombre: " << pacientes.nombre 
                  << ", Apellido: " << pacientes.apellido 
                  << ", Edad: " << pacientes.edad 
                  << ", IMC: " << pacientes.imc 
                  << ", A1C: " << pacientes.a1c << std::endl;
    }

    csvFile.close();
}

void menu() {
    int respuesta = 0;

    while (true) {
        cout << "\n\n\n------------[Menú]------------" << endl;
        cout << "1 -> Agregar un Paciente." << endl;
        cout << "2 -> Organizar prioridad." << endl;
        cout << "3 -> Buscar por IMC." << endl;
        cout << "4 -> Buscar por A1C." << endl;//eliminar o editar por los buscar
        cout << "5 -> Eliminar todos los datos." << endl;
        cout << "6 -> Mostrar datos." << endl;
        cout << "7 -> Salir." << endl;

        // Devolverse si está mala la respuesta
        cin >> respuesta;
        if (respuesta < 1 || respuesta > 6) {
            cout << "[Seleccione una opción entre las disponibles (escribir número)]" << endl;
            continue; 
        }


        //caso de respuesta correcta
        switch (respuesta) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5://reset datos
                create_newfile();
                cout << "Se han reseteado los datos." << endl;
                break;
            case 6://mostrar lista
                read_file();
                break;
            case 7://fin programa
                return;
        }
    }
}

int main() {
    menu(); //multiples opciones

    cout << "El programa ha finalizado" << endl;
    return 0;
}
