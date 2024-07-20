#ifndef FIGURAGEOMETRICA_HPP
#define FIGURAGEOMETRICA_HPP

#include "sculptor.hpp"

class FiguraGeometrica {
public:
    virtual ~FiguraGeometrica() {}
    virtual void draw(Sculptor &s) = 0; // Método virtual puro
};

#endif // FIGURAGEOMETRICA_HPP