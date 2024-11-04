#include "estructuras.h"

void punto_print(punto M, int dimension)
{
    int i;
    printf("(");
    for (i = 0; i < dimension; i++)
    {
        if (i != dimension - 1)
        {
            printf("%.2f, ", M.data[i]);
        }
        else
        {
            printf("%.2f ", M.data[i]);
        }
    }
    printf(")");
}

punto restaPuntos(punto a, punto b, int dimension)
{
    punto temp;
    float *data;
    data = malloc(dimension * sizeof(float));
    int i;
    for (i = 0; i < dimension; i++)
    {
        data[i] = a.data[i] - b.data[i];
    }
    temp.data = data;
    return temp;
}

punto puntoNDimensional(int dimension)
{
    punto temp;

    float *data;
    data = malloc(dimension * sizeof(float));

    int i;
    int superior = 255;
    int inferior = 0;
    float valorAleatorio;

    for (i = 0; i < dimension; i++)
    {
        valorAleatorio = (float)(rand() % ((superior - inferior) * 100)) / 100 + inferior;
        data[i] = valorAleatorio;
    }
    temp.data = data;
    return temp;
}

float distanciaEuclideanaPuntos(punto a, punto b, int dimension)
{
    int i;
    float suma = 0;
    suma = 0;
    for (i = 0; i < dimension; i++)
    {
        suma = suma + pow((a.data[i] - b.data[i]), 2);
    }
    return sqrt(suma);
}

centroides centroidesReales_init(int filas, int dimensionPunto)
{
    centroides temp;
    temp.filas = filas;

    punto *m;

    m = malloc(filas * sizeof(punto));

    int i;
    for (i = 0; i < filas; i++)
    {
        m[i] = puntoNDimensional(dimensionPunto);
    }

    temp.data = m;
    return temp;
}
void centroides_print(centroides M, int dimension)
{
    printf("\n");
    int i;
    for (i = 0; i < M.filas; i++)
    {
        punto_print(M.data[i], dimension);
    }
    printf("\n");
}

void matrix_print(matrix M, int dimension)
{
    printf("\n");
    int i, j;
    for (i = 0; i < M.filas; i++)
    {
        for (j = 0; j < M.columnas; j++)
        {
            punto_print(M.data[i][j], dimension);
        }
        printf("\n");
    }
}

punto gruposCentroidesMedia(gruposCentroides grupos, int dimension)
{
    punto temp;
    float *m;
    m = malloc(dimension * sizeof(float));
    if (grupos.cardinalidad >= 1)
    {
        int i;
        int k;
        float suma;

        for (i = 0; i < dimension; i++)
        {
            suma = 0;
            for (k = 0; k < grupos.cardinalidad; k++)
            {
                suma = suma + grupos.puntos[k].data[i];
            }
            m[i] = (int)(suma / grupos.cardinalidad);
        }
    }
    temp.data = m;
    return temp;
}

centroides actualizarCentroides(int kClases, clasesEquivalencia clases, int dimension)
{
    centroides temp;
    temp.filas = kClases;
    punto *m;
    m = malloc(kClases * sizeof(punto));
    int i;
    for (i = 0; i < kClases; i++)
    {

        m[i] = gruposCentroidesMedia(clases.grupos[i], dimension);
    }

    temp.data = m;
    return temp;
}

int centroDistanciaMin(punto puntoCompara, int kCentros, centroides centros, int dimension)
{
    float *distancias;
    distancias = malloc(kCentros * sizeof(float));
    int i;
    for (i = 0; i < kCentros; i++)
    {
        distancias[i] = distanciaEuclideanaPuntos(puntoCompara, centros.data[i], dimension);
    }
    int iesimo;
    iesimo = 0;
    int min = distancias[0];
    for (int i = 0; i < kCentros; i++)
    {
        if (min > distancias[i])
        {
            min = distancias[i];
            iesimo = i;
        }
    }
    return iesimo;
}

clasesEquivalencia clasificarMatrix(matrix matriz, int kCentros, centroides centros, int dimension)
{
    // printf("inicio cala\n");
    clasesEquivalencia temp;
    int i;
    int j;
    gruposCentroides *m;
    m = malloc(kCentros * sizeof(gruposCentroides));
    for (i = 0; i < kCentros; i++)
    {
        m[i].cardinalidad = 0;
        m[i].puntos = malloc(matriz.filas * matriz.columnas * sizeof(punto));
    }
    int clase;
    int posicion;
    for (i = 0; i < matriz.filas; i++)
    {

        for (j = 0; j < matriz.columnas; j++)
        {
            // printf("i %i y j %i \t", i, j);
            clase = centroDistanciaMin(matriz.data[i][j], kCentros, centros, dimension);
            // printf("%i \n", clase);

            posicion = m[clase].cardinalidad;
            m[clase].puntos[posicion] = matriz.data[i][j];
            m[clase].cardinalidad++;
        }
    }
    temp.grupos = m;
    return temp;
}

void sumaPuntosClases(clasesEquivalencia particion, int kcentros, centroides centros, int dimension)
{
    int i;

    for (i = 0; i < kcentros; i++)
    {
        printf("El suma del grupo asociado al centro ");
        punto_print(centros.data[i], dimension);
        printf(" es:\t ");

        punto_print(gruposCentroidesMedia(particion.grupos[i], dimension), dimension);

        printf("\n");
    }
}
