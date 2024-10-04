#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath> 
#include <queue>
#include <list>

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

    while (getline(csvFile, line)) {//aquì si hay espacios vacìos en el archivo se muere, aviso
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

// buscar el paciente más cercano a A1C ingresado
pacientes buscar_paciente(double valor_usuario, string opcion_user) {
    //abrir archivo
    std::ifstream csvFile("pacientes.csv"); 

    std::string line;
    getline(csvFile, line);

    pacientes paciente_cercano;
    double diferencia_minima = 1000; // Inicia con un número grande para comparar

    while (getline(csvFile, line)) {
        stringstream ss(line);
        pacientes paciente;
        string field;

        getline(ss, field, ',');
        paciente.numero_lista = stoi(field); // Nº

        getline(ss, field, ',');
        paciente.prioridad = stoi(field); // Prioridad

        getline(ss, paciente.nombre, ','); // Nombre

        getline(ss, paciente.apellido, ','); // Apellido

        getline(ss, field, ',');
        paciente.edad = stoi(field); // Edad

        getline(ss, field, ',');
        paciente.imc = stod(field); // IMC

        getline(ss, field, ',');
        paciente.a1c = stod(field); // A1C

        double diferencia = 0;
        if (opcion_user == "I") {
            // Calcular la diferencia entre el IMC ingresado y el IMC del paciente
            diferencia = std::abs(paciente.imc - valor_usuario);
        } else {
            // Calcular la diferencia entre el A1C ingresado y el A1C del paciente
            diferencia = std::abs(paciente.a1c - valor_usuario);
        }

        // Actualizar el paciente más cercano si la diferencia es menor
        if (diferencia < diferencia_minima) {
            diferencia_minima = diferencia;
            paciente_cercano = paciente;
        }
    }

    csvFile.close();
    return paciente_cercano; // Retornar el paciente más cercano encontrado
}

int caso_cuatro() {
    double a1c_user; // Permite decimales
    cout << "Ingrese un índice de A1C [0 ≤ x ≤ 12]: ";
    string imc_opcion = "A"; 

    while (true) {
        cin >> a1c_user;

        if (cin.fail() || a1c_user < 0 || a1c_user > 12) { // Valores erroneos
            caso_cuatro();
        } else { // Valores apropiados
            break; 
        }
    }

    // Buscar paciente cercano al A1C ingresado por el usuario
    pacientes paciente_encontrado = buscar_paciente(a1c_user, imc_opcion);

    // Mostrar los datos del paciente encontrado
    if (paciente_encontrado.numero_lista != 0) {
        cout << "\n\n\n------------[Se ha encontrado al paciente:]------------" << endl;
        cout << "Nº: " << paciente_encontrado.numero_lista 
        << ", Prioridad: " << paciente_encontrado.prioridad
        << ", Nombre: " << paciente_encontrado.nombre 
        << ", Apellido: " << paciente_encontrado.apellido 
        << ", Edad: " << paciente_encontrado.edad 
        << ", IMC: " << paciente_encontrado.imc 
        << ", A1C: " << paciente_encontrado.a1c << endl;
        //lógica editar/borrar/editar paciente
        return paciente_encontrado.numero_lista;
    } else {
        cout << "No se encontraron pacientes en el archivo." << endl;
        return 0;
    }
}

int caso_tres() {
    int imc_user; 
    cout << "Ingrese un índice de IMC [< 50 de preferencia]: ";
    cin >> imc_user;
    string imc_opcion = "I"; // Falta el punto y coma
    // Buscar paciente cercano al IMC ingresado por el usuario
    pacientes paciente_encontrado = buscar_paciente(imc_user, imc_opcion);

    // Mostrar los datos del paciente encontrado
    if (paciente_encontrado.numero_lista != 0) {
        cout << "\n\n\n------------[Se ha encontrado al paciente:]------------" << endl;
        cout << "Nº: " << paciente_encontrado.numero_lista 
        << ", Prioridad: " << paciente_encontrado.prioridad
        << ", Nombre: " << paciente_encontrado.nombre 
        << ", Apellido: " << paciente_encontrado.apellido 
        << ", Edad: " << paciente_encontrado.edad 
        << ", IMC: " << paciente_encontrado.imc 
        << ", A1C: " << paciente_encontrado.a1c << endl;
        //lógica editar/borrar/editar paciente
        return paciente_encontrado.numero_lista;
    } else {
        cout << "No se encontraron pacientes en el archivo." << endl;
        return 0;
    }
}

void eliminar_paciente(int num_paciente) {
    std::ifstream csvFile("pacientes.csv");

    std::queue<string> fila; // Cola para almacenar las líneas que no se eliminan
    string line;
    bool eliminado = false;

    // Leer header
    getline(csvFile, line);
    fila.push(line);

    while (getline(csvFile, line)) {
        stringstream ss(line);
        string field;
        int numero_lista;

        // Extraer el número de lista de la línea
        getline(ss, field, ',');
        numero_lista = stoi(field);

        // Si el número de lista no coincide con el `num_paciente`, se agrega a la cola
        if (numero_lista != num_paciente) {
            fila.push(line);
        } else {
            eliminado = true; // Se ha eliminado el paciente
        }
    }

    csvFile.close();

    // Reescribir las líneas que quedan en el archivo, sin el paciente eliminado
    std::ofstream csvFileOut("pacientes.csv");
    while (!fila.empty()) {
        csvFileOut << fila.front() << "\n";
        fila.pop(); // Quitar la línea de la cola
    }
    csvFileOut.close();

    if (eliminado) {
        cout << "[ El paciente con número de lista " << num_paciente << " ha sido eliminado. ]\n";
    }
}

void opciones_busqueda(int num_paciente) {
    int respuesta = 0;

    while (true) {
        cout << "\n\n\n------------[Opciones paciente]------------" << endl;
        cout << "1 -> Eliminar paciente" << endl;
        cout << "2 -> Retroceder." << endl;

        // Devolverse si está mala la respuesta
        cin >> respuesta;
        if (respuesta < 1 || respuesta > 2) {
            cout << "[Seleccione una opción entre las disponibles (escribir número)]" << endl;
            continue; 
        }

        //caso de respuesta correcta
        switch (respuesta) {
            case 1: {
                eliminar_paciente(num_paciente);
                return;
            }
            case 2:{
                return;
            }
        }
    }
}

void organizar_prioridad() {
    std::ifstream csvFile("pacientes.csv"); 

    if (!csvFile) {
        cerr << "Error al abrir el archivo CSV.\n";
        return;
    }

    std::list<pacientes> lista_pacientes; // Lista para almacenar los pacientes
    std::string line;
    
    // Leer la cabecera
    getline(csvFile, line);
    
    while (getline(csvFile, line)) {
        stringstream ss(line);
        pacientes paciente;
        string field;

        // Leer los campos del paciente desde el archivo CSV
        getline(ss, field, ',');
        paciente.numero_lista = stoi(field); // Nº

        getline(ss, field, ',');
        paciente.prioridad = stoi(field); // Prioridad (original, que vamos a recalcular)

        getline(ss, paciente.nombre, ','); // Nombre

        getline(ss, paciente.apellido, ','); // Apellido

        getline(ss, field, ',');
        paciente.edad = stoi(field); // Edad

        getline(ss, field, ',');
        paciente.imc = stod(field); // IMC

        getline(ss, field, ',');
        paciente.a1c = stod(field); // A1C

        // --------- Cálculo de la prioridad -------------
        // Mi idea es que se le de mayor prioridad a las edades avanzadas antes que al peso, pero que tengan una importancia similar.
        double prioridad_A = ((paciente.edad * 0.6) + (paciente.imc * 0.4)) * 0.4;
        double prioridad_B = 0;

        // Pero que el a1c sea la parte más importante para ver la prioridad si es que la tienes en medio u alta, si es baja entonces no importará mucho.
        if (paciente.a1c < 5.7) {
            prioridad_B = paciente.a1c * 0.2;
        } else if (paciente.a1c >= 5.7 && paciente.a1c < 6.5) {
            prioridad_B = paciente.a1c * 0.5;
        } else {
            prioridad_B = paciente.a1c * 0.6;
        }

        double prioridad_real = prioridad_A + prioridad_B;

        // Actualizar la prioridad del paciente
        paciente.prioridad = static_cast<int>(round(prioridad_real));

        // Agregar paciente actualizado a la lista
        lista_pacientes.push_back(paciente);
    }

    csvFile.close(); // Cerrar el archivo de lectura

    // --------- Ordenar la lista de pacientes según la prioridad -------------
    lista_pacientes.sort([](const pacientes &a, const pacientes &b) {
        return a.prioridad > b.prioridad; // Orden descendente de prioridad
    });

    // Reescribir el archivo con los pacientes en orden y actualizando los números de lista
    std::ofstream csvFileOut("pacientes.csv");
    
    // Escribir la cabecera
    csvFileOut << "Nº,Prioridad,Nombre,Apellido,Edad,IMC,A1C\n";

    // Actualizar el numero_lista según el nuevo orden y reescribir los datos
    int nuevo_numero_lista = 1;
    for (auto &paciente : lista_pacientes) {
        paciente.numero_lista = nuevo_numero_lista++; // Actualizar número de lista

        csvFileOut << paciente.numero_lista << "," 
                   << paciente.prioridad << ","
                   << paciente.nombre << ","
                   << paciente.apellido << ","
                   << paciente.edad << ","
                   << paciente.imc << ","
                   << paciente.a1c << "\n";
    }

    csvFileOut.close();
    cout << "---------Las prioridades de los pacientes han sido reorganizadas y ordenadas.---------";
}


void menu() {
    int respuesta = 0;

    while (true) {
        cout << "\n\n\n------------[Menú]------------" << endl;
        cout << "1 -> Agregar un Paciente." << endl;
        cout << "2 -> Organizar prioridad." << endl;//lista
        cout << "3 -> Buscar por IMC." << endl;
        cout << "4 -> Buscar por A1C." << endl;//eliminar -> pop (cola)
        cout << "5 -> Eliminar todos los datos." << endl;
        cout << "6 -> Mostrar datos." << endl;
        cout << "7 -> Salir.\n" << endl;

        // Devolverse si está mala la respuesta
        cin >> respuesta;
        if (respuesta < 1 || respuesta > 7) {
            cout << "[Seleccione una opción entre las disponibles (escribir número)]" << endl;
            continue; 
        }

        //caso de respuesta correcta
        switch (respuesta) {
            case 1:
                break;
            case 2: {//prioridad
                organizar_prioridad();
                break;
            }
            case 3: {//busqueda IMC
                int num_paciente = caso_tres();
                opciones_busqueda(num_paciente);
                break;
            }
            case 4: {//busqueda a1c
                int num_paciente = caso_cuatro();
                opciones_busqueda(num_paciente);
                break;
            }
            case 5: {//reset datos
                create_newfile();
                cout << "Se han reseteado los datos." << endl;
                break;
            }
            case 6: {//mostrar lista
                read_file();
                break;
            }
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