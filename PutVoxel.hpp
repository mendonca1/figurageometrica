#ifndef PUTVOXEL_HPP
#define PUTVOXEL_HPP

#include "figurageometrica.hpp"

class PutVoxel : public FiguraGeometrica {
    int x, y, z;
    float r, g, b, a;
public:
    PutVoxel(int x, int y, int z, float r, float g, float b, float a);
    void draw(Sculptor &s);
};

#endif // PUTVOXEL_HPP
