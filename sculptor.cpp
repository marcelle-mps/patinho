#include "sculptor.h"
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    int i;
    nx=_nx;
    ny=_ny;
    nz=_nz;

    v = new Voxel**[nx];
    v[0] = new Voxel*[nx*ny];
    v[1] = v[0] + ny*sizeof(Voxel**);
    v[0][0]= new Voxel[nx*ny*nz];

    for(i=1; i<nz; i++){
        v[i]=v[i-1]+ny;
    }
    for(i=1; i<nz*ny; i++){
        v[0][i]=v[0][i-1]+nx;
    }
}

Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

void Sculptor::setColor(float _r, float _g, float _b, float alpha){
    r = _r;
    g = _g;
    b = _b;
    a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void  Sculptor::cutVoxel( int x, int y, int z){
    v[x][y][z].isOn = false ;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0; i<x1+1; i++){
        for(j=y0; j<y1+1; j++){
            for(k=z0; k<z1+1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0; i<x1+1; i++){
        for(j=y0; j<y1+1; j++){
            for(k=z0; k<z1+1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    int i, j, k;
    for(i=0; i< nx; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nz; k++){
                if(pow(i-xcenter, 2)+pow(j-ycenter, 2)+pow(k-zcenter, 2)<=pow(radius, 2)){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    int i, j, k;
    for(i=0; i<nx; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nz; k++){
                if(pow(i-xcenter, 2)+pow(j-ycenter, 2)+pow(k-zcenter, 2)<=pow(radius, 2)){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i, j, k;
    for(i=0; i<nx; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nz; k++){
                if(pow(i-xcenter, 2)/pow(rx, 2)+pow(j-ycenter, 2)/pow(ry, 2)+pow(k-zcenter, 2)/pow(rz, 2)<=1){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i, j, k;
    for(i = 0; i < nx; i++){
        for(j = 0; j < ny; j++){
            for(k = 0; k < nz; k++){
                if(pow(i - xcenter, 2)/pow(rx, 2) + pow(j - ycenter, 2)/pow(ry, 2) + pow(k - zcenter, 2)/pow(rz, 2) <= 1){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char* filenome){
    ofstream saida;
    saida.open(filenome);
    int i, j, k, total=0;

    for(i=0; i<nz; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nx; k++){
                if(v[i][j][k].isOn==true){
                    total++;
                }
            }
        }
    }

    saida << "OFF\n";
    saida << total*8 << " " << total*6 << " " << "0\n";

    for(i=0; i<nz; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nx; k++){
                if(v[i][j][k].isOn == true){
                    saida << i-0.5 << " " << j+0.5 << " " << k-0.5 << "\n";
                    saida << i-0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    saida << i+0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    saida << i+0.5 << " " << j+0.5 << " " << k-0.5 << "\n";
                    saida << i-0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                    saida << i-0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    saida << i+0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    saida << i+0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                }
            }
        }
    }
    total=0;
    for(i=0; i<nz; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nx; k++){
                if(v[i][j][k].isOn==true){
                    int aux = 8*total;
                    saida << "4 " << aux << " " << aux+3 << " " << aux+2 << " " << aux+1 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    saida << "4 " << aux+4 << " " << aux+5 << " " << aux+6 << " " << aux+7 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    saida << "4 " << aux << " " << aux+1 << " " << aux+5 << " " << aux+4 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    saida << "4 " << aux << " " << aux+4 << " " << aux+7 << " " << aux+3 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    saida << "4 " << aux+3 << " " << aux+7 << " " << aux+6 << " " << aux+2 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    saida << "4 " << aux+1 << " " << aux+2 << " " << aux+6 << " " << aux+5 << " " << (v[i][j][k].r) << " " << (v[i][j][k].g) << " " << (v[i][j][k].b) << " " << (v[i][j][k].a) << "\n";
                    aux++;
                }
            }
        }
    }
    saida.close();
}
