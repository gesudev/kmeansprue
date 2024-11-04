#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "kmeans.c"
#include "time.h"

int main()
{

    srand(time(NULL));

    // imagenkmeans(char nombre[], char out[], int kGrupos, int limite)
    imagenkmeans("..\\pruebakmeans.bmp", "kmenas.bmp", 15, 20); // en vscode
}