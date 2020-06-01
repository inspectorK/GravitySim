#include <iostream>
#include "vect.h"

void run_vectorUnitTests()
{
    const double PI = 3.14159265;
    vect v1 = vect();
    vect v2 = vect(-10, 10);
    vect v3 = vect(10, -10);
    vect v4 = vect(0, 5);

    v2.print();
    std::cout << "\n";
    std::cout << "v2 angle =     " << v2.get_angle() * (180 / PI) << "\n";
    std::cout << "v2 magnitude = " << v2.get_magnitude() << "\n";
    std::cout << "v2 uv mag =    " << v2.get_unitvector().get_magnitude() << "\n";
    std::cout << "\n";
    v2.set_magnitude(5);
    v2.print();
    std::cout << "\n";
    std::cout << "v2 angle =     " << v2.get_angle() * (180 / PI) << "\n";
    std::cout << "v2 magnitude = " << v2.get_magnitude() << "\n";
    std::cout << "v2 uv mag =    " << v2.get_unitvector().get_magnitude() << "\n";
    std::cout << "\n";
    v2.set_angle(PI);
    v2.print();
    std::cout << "\n";
    std::cout << "v2 angle =     " << v2.get_angle() * (180 / PI) << "\n";
    std::cout << "v2 magnitude = " << v2.get_magnitude() << "\n";
    std::cout << "v2 uv mag =    " << v2.get_unitvector().get_magnitude() << "\n";
    std::cout << "\n";

    v2.reset(-10, 10);
    vect addtest = v2 + v3;
    addtest.print();
    std::cout << "\n" << "addtest mag = " << addtest.get_magnitude() << "\n";
    v4.print();
    std::cout << "v4 mag = " << v4.get_magnitude() << "\n";
    vect scalarmult = v4 * 3.0;
    scalarmult.print();
    std::cout << "v4 mag = " << scalarmult.get_magnitude() << "\n";
}