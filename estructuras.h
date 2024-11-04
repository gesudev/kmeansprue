typedef struct
{
    float *data;
} punto;

typedef struct
{
    int filas;
    punto *data;
} centroides;

typedef struct
{
    punto *puntos;
    int cardinalidad;
} gruposCentroides;

typedef struct
{
    gruposCentroides *grupos;
} clasesEquivalencia;

typedef struct
{
    punto **data;
    int filas;
    int columnas;
} matrix;
