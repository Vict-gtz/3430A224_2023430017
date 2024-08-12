#include <iostream>

double square(double x)
{
    return x*x;
}

void print_square(double(x))
{
    std::cout<< "El cuadrado de " << x << " es " << square(x) << '\n';
}

int main()
{
    print_square(14);
    print_square(3);
    print_square(1);
    print_square(2);
    print_square(921493248);
}