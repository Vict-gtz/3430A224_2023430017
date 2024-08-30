    #include <iostream>

    // Estructura definida llamada "Persona"
    struct Persona {
        std::string nombre;
        int edad;
        double altura;
    };

    int main() {
        //Instancia para que persona tome valores en arreglo
        Persona persona[2];

        // Agregar información a persona
        persona[0].nombre = "Fernanfloo";
        persona[0].edad = 97;
        persona[0].altura = 1.20;

        persona[1].nombre = "Juan";
        persona[1].edad = 20;
        persona[1].altura = 2.40;

        // acceso a la información y print

        for (int i = 0; i < 2; ++i){
            std::cout << "// Nombre: " << persona[i].nombre << std::endl;
            std::cout << "// Edad: " << persona[i].edad << " años" << std::endl;
            std::cout << "// Altura: " << persona[i].altura << "m." << std::endl;
            std::cout << std::endl;
        }
        
        return 0;
    }