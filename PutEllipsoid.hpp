#ifndef PUTELLIPSOID_HPP
#define PUTELLIPSOID_HPP

#include "figurageometrica.hpp"

class PutEllipsoid : public FiguraGeometrica {
    int x, y, z, rx, ry, rz;
    float r, g, b, a;
public:
    PutEllipsoid(int x, int y, int z, int rx, int ry, int rz, float r, float g, float b, float a);
    void draw(Sculptor &s);
};

#endif // PUTELLIPSOID_HPP
