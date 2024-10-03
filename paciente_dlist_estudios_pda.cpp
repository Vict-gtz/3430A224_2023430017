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

int main() {
    read_file(); // Lee el archivo y procesa los datos directamente
    return 0;
}
