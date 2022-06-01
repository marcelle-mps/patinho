#include <iostream>
#include "sculptor.h"
#include "sculptor.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main()
{

    //Define o tamanho total
    Sculptor draw(60, 60, 60);

    //Define a cor como laranja
    draw.setColor(0.5, 0.3, 0, 1);

    //Patas
    draw.putBox(25, 26, 35, 36, 2, 30);
    draw.putBox(24, 27, 35, 39, 2, 2);
    draw.putBox(35, 36, 35, 36, 2, 30);
    draw.putBox(34, 37, 35, 39, 2, 2);
    
    //Define a cor como branco
    draw.setColor(1, 1, 1, 1);

    //Corpo
    draw.putEllipsoid(30, 35, 41, 20, 30, 20);
    draw.putSphere(30, 35, 41, 15);
    draw.cutBox(0, 60, 0, 60, 45, 60);

    //Define a cor como laranja
    draw.setColor(0.5, 0.3, 0, 1);
  
    //Bico
    draw.putBox(28, 32, 5, 15, 54, 54);
  
    //Define a cor como branco
    draw.setColor(1, 1, 1, 1);
  
    //Pescoço
    draw.putBox(29, 31, 9, 11, 40, 55);
    draw.putBox(30, 30, 8, 12, 40, 55);
    draw.putBox(28, 32, 10, 10, 40, 55);

    //Cabeça
    draw.putSphere(30, 12, 55, 4);

    //Define a cor como preto
    draw.setColor(0, 0, 0, 1);

    //Olhos
    draw.putVoxel(28, 10, 58);
    draw.putVoxel(31, 10, 58);

    //Define a cor como turquesa
    draw.setColor(0, 0.3, 1, 0.4);

    //Água
    draw.putBox(0, 60, 0, 60, 0, 30);

    //Bolhas
    draw.cutSphere(10, 10, 5, 3);
    draw.cutSphere(8, 4, 10, 3);
    draw.cutSphere(14, 5, 15, 3);
    draw.cutVoxel(8, 4, 15);
    draw.cutVoxel(10, 10, 12);
    draw.cutSphere(14, 50, 15, 3);
    draw.cutVoxel(8, 49, 15);
    draw.cutVoxel(10, 55, 12);
    
    //draw.cutEllipsoid(10, 10, 5, 3, 4, 5);

    draw.writeOFF((char*)"patinho.off");

    return 0;
}
