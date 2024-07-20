#ifndef PUTSPHERE_HPP
#define PUTSPHERE_HPP

#include "figurageometrica.hpp"

class PutSphere : public FiguraGeometrica {
    int x, y, z, radius;
    float r, g, b, a;
public:
    PutSphere(int x, int y, int z, int radius, float r, float g, float b, float a);
    void draw(Sculptor &s);
};

#endif // PUTSPHERE_HPP
