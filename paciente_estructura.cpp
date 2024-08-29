#include <iostream>

// Estructura definida llamada "Persona"
struct Persona {
    std::string nombre;
    int edad;
    double altura;
};

int main() {
    //Instancia para que persona tome valores
    Persona persona;

    // Agregar información a persona
    persona.nombre = "Juan";
    persona.edad = 20;
    persona.altura = 2.40;

    // acceso a la información y print
    std::cout << "// Nombre: " << persona.nombre << std::endl;
    std::cout << "// Edad: " << persona.edad << " años" << std::endl;
    std::cout << "// Altura: " << persona.altura << "m." << std::endl;
    
    return 0;
}