#include <iostream>
#include "sculptor.hpp"
#include "putvoxel.hpp"
#include "putbox.hpp"
#include "putsphere.hpp"
#include "putellipsoid.hpp"
#include <vector>

int main() {
  Sculptor sculptor(50, 50, 50);

  // Adicione as figuras geométricas ao vetor
  std::vector<FiguraGeometrica*> figs;
  figs.push_back(new PutVoxel(10, 10, 10, 1.0, 0.0, 0.0, 1.0)); // Vermelho
  figs.push_back(new PutBox(5, 15, 5, 15, 5, 15, 0.0, 1.0, 0.0, 1.0)); // Verde
  figs.push_back(new PutSphere(25, 25, 25, 10, 0.0, 0.0, 1.0, 1.0)); // Azul
  figs.push_back(new PutEllipsoid(35, 35, 35, 5, 10, 5, 1.0, 1.0, 0.0, 1.0)); // Amarelo

  // Desenhe todas as figuras
  for (auto fig : figs) {
      fig->draw(sculptor);
  }

  // Libere a memória alocada
  for (auto fig : figs) {
      delete fig;
  }

  sculptor.writeOFF("output.off");

  return 0;
}