#include <iostream>
#include "math/vec3.h"

void runMathTests();
void runFrameBufferTests();

int main() {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);

    Vec3 c = a+b;

    std::cout << "Result: "
    << c.x << ", "
    << c.y << ", "
    << c.z << std::endl;

    Vec3 d(1,0,0);
    Vec3 e(0,1,0);

    Vec3 f = Vec3::cross(d,e);

    std::cout << f.x << " " << f.y << " " << f.z << std::endl;

    runMathTests();   
    runFrameBufferTests();
    
    return 0;
}