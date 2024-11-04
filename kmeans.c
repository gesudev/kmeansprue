#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "estructuras.c"

int imagenkmeans(char nombre[], char out[], int kGrupos, int limite)
{
    int dimension = 3;

    FILE *img1, *img2;
    int space[54];
    img1 = fopen(nombre, "rb");
    img2 = fopen(out, "wb");

    int i, j;
    for (i = 0; i < 54; i++)
    {
        space[i] = fgetc(img1);
        fputc(space[i], img2);
    }
    int ancho = space[18] + space[19] * 256 + space[20] * 256 * 256 + space[21] * 256 * 256 * 256;
    int alto = space[22] + space[23] * 256 + space[24] * 256 * 256 + space[25] * 256 * 256 * 256;

    punto **imagen;
    imagen = malloc(alto * sizeof(punto *));
    for (i = 0; i < alto; i++)
    {
        imagen[i] = malloc(ancho * sizeof(punto));
    }

    printf("\n alto %i, ancho %i \n", alto, ancho);

    centroides centroidesR;
    centroidesR = centroidesReales_init(kGrupos, dimension);
    centroides_print(centroidesR, dimension);

    int a, b, ce;
    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            punto puntoTem;
            float *datapuntoTemp;
            datapuntoTemp = malloc(dimension * sizeof(float));
            a = fgetc(img1);
            b = fgetc(img1);
            ce = fgetc(img1);

            datapuntoTemp[0] = (float)a;
            datapuntoTemp[1] = (float)b;
            datapuntoTemp[2] = (float)ce;
            puntoTem.data = datapuntoTemp;
            imagen[i][j] = puntoTem;
        }
    }

    matrix matriz;
    matriz.filas = alto;
    matriz.columnas = ancho;
    matriz.data = imagen;
    printf("===================================================");

    clasesEquivalencia primera;
    primera = clasificarMatrix(matriz, kGrupos, centroidesR, dimension);

    int contadorLimite;
    int numeroCentros = kGrupos;
    centroides centroTemp;
    punto *dataCentroTemp;
    dataCentroTemp = malloc(numeroCentros * sizeof(punto));
    centroTemp.data = dataCentroTemp;
    printf("===================================================");
    for (contadorLimite = 0; contadorLimite < limite; contadorLimite++)
    {
        centroTemp = actualizarCentroides(numeroCentros, primera, dimension);
        centroidesR.data = centroTemp.data;
        printf("\n Centroides iteracion %i\n", contadorLimite);
        centroides_print(centroidesR, dimension);
        primera = clasificarMatrix(matriz, numeroCentros, centroidesR, dimension);
    }
    printf("\n Centroides finales\n");
    centroides_print(centroidesR, dimension);
    int clase;
    for (i = 0; i < alto; i++)
    {
        for (j = 0; j < ancho; j++)
        {
            clase = centroDistanciaMin(matriz.data[i][j], kGrupos, centroidesR, dimension);

            a = centroidesR.data[clase].data[0];
            b = centroidesR.data[clase].data[1];
            ce = centroidesR.data[clase].data[2];

            fputc(a, img2);
            fputc(b, img2);
            fputc(ce, img2);
        }
        // printf("\n");
    }

    fclose(img1);
    fclose(img2);
    return 0;
}