#include "sculptor.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx; ny = _ny; nz = _nz;

    v = new Voxel**[nx];
    for(int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for(int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
            for(int k = 0; k < nz; k++) {
                v[i][j][k].isOn = false;
            }
        }
    }
}

Sculptor::~Sculptor() {
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float alpha) {
    this->r = r; this->g = g; this->b = b; this->a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z) {
    if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z) {
    if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].isOn = false;
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for(int i = x0; i <= x1; i++) {
        for(int j = y0; j <= y1; j++) {
            for(int k = z0; k <= z1; k++) {
                putVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for(int i = x0; i <= x1; i++) {
        for(int j = y0; j <= y1; j++) {
            for(int k = z0; k <= z1; k++) {
                cutVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for(int i = -radius; i <= radius; i++) {
        for(int j = -radius; j <= radius; j++) {
            for(int k = -radius; k <= radius; k++) {
                if((i*i + j*j + k*k) <= (radius * radius)) {
                    putVoxel(xcenter + i, ycenter + j, zcenter + k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for(int i = -radius; i <= radius; i++) {
        for(int j = -radius; j <= radius; j++) {
            for(int k = -radius; k <= radius; k++) {
                if((i*i + j*j + k*k) <= (radius * radius)) {
                    cutVoxel(xcenter + i, ycenter + j, zcenter + k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for(int i = -rx; i <= rx; i++) {
        for(int j = -ry; j <= ry; j++) {
            for(int k = -rz; k <= rz; k++) {
                if((i*i)/(float)(rx*rx) + (j*j)/(float)(ry*ry) + (k*k)/(float)(rz*rz) <= 1.0) {
                    putVoxel(xcenter + i, ycenter + j, zcenter + k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for(int i = -rx; i <= rx; i++) {
        for(int j = -ry; j <= ry; j++) {
            for(int k = -rz; k <= rz; k++) {
                if((i*i)/(float)(rx*rx) + (j*j)/(float)(ry*ry) + (k*k)/(float)(rz*rz) <= 1.0) {
                    cutVoxel(xcenter + i, ycenter + j, zcenter + k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char* filename) {
    std::ofstream outfile;
    outfile.open(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    outfile << "OFF" << std::endl;

    int numVertices = 0;
    int numFaces = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    numVertices += 8;
                    numFaces += 6;
                }
            }
        }
    }
    outfile << numVertices << " " << numFaces << " 0" << std::endl;

    int vertexIndex = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    outfile << std::fixed << std::setprecision(2);
                    outfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    outfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }
            }
        }
    }

    vertexIndex = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].isOn) {
                    outfile << "4 " << vertexIndex + 0 << " " << vertexIndex + 3 << " " << vertexIndex + 2 << " " << vertexIndex + 1 << " "
                            << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    outfile << "4 " << vertexIndex + 4 << " " << vertexIndex + 5 << " " << vertexIndex + 6 << " " << vertexIndex + 7 << " "
                            << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    outfile << "4 " << vertexIndex + 0 << " " << vertexIndex + 1 << " " << vertexIndex + 5 << " " << vertexIndex + 4 << " "
                            << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    outfile << "4 " << vertexIndex + 0 << " " << vertexIndex + 4 << " " << vertexIndex + 7 << " " << vertexIndex + 3 << " "
                            << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    outfile << "4 " << vertexIndex + 3 << " " << vertexIndex + 7 << " " << vertexIndex + 6 << " " << vertexIndex + 2 << " "
                            << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    outfile << "4 " << vertexIndex + 1 << " " << vertexIndex + 2 << " " << vertexIndex + 6 << " " << vertexIndex + 5 << " "
                            << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    vertexIndex += 8;
                }
            }
        }
    }

    outfile.close();
}
