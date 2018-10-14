#include <stdlib.h>
#include "mex.h"
#include "math.h"

#define inf 2000000000
#define ABS(x) ((x) < 0 ? (-(x)) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ERROR_MALLOC(x) if (x == NULL) printf("Fuja para as colinas!\n");

double **double2Dmalloc(int M, int N, int valor);
void double2Dfree(double **A, int M);
int ***int3Dmalloc(int M, int N, int L, int valor);
int **int2Dmalloc(int M, int N, int valor);
void int2Dfree(int **A, int M);
void int3Dfree(int ***A, int M, int N);
double DT (int **A, int **V, double *X, double *Y, double *Z, double *Lab, int Nvox, int M, int N, int q, int ***O, int ***S, int imprimir, int imprimirPts);
void inicializa(double *X, double *Y, double *Lab, int Nvox, int **A, int **V);
void step1 (int **A, int **V, int M, int N);
void step2 (int **A, int **V, int M, int N);

int *quadrado;

void mexFunction(
    int nlhs,              // Number of left hand side (output) arguments
    mxArray *plhs[],       // Array of left hand side arguments
    int nrhs,              // Number of right hand side (input) arguments
    const mxArray *prhs[]  // Array of right hand side arguments
)
{
    double *X, *Y, *Z, *Lab, *dim_in, *Vretorno, *Entrada;
    int ***O, ***S;

    int Nvox, M, N, q;
    int i, j, k, u, nq, imprimir, imprimirPts;

    //Obter coordenadas
    X = mxGetPr(prhs[0]);
    Y = mxGetPr(prhs[1]);
    Lab = mxGetPr(prhs[2]);
    // Obter o numero de voxels
    Nvox = (int) mxGetM(prhs[0]);
    //Obter dimensoes do cubo
    dim_in = mxGetPr(prhs[3]);
    M = (int)dim_in[0];
    N = (int)dim_in[1];
    q = (int)dim_in[2];
    imprimir = (int)dim_in[3];
    imprimirPts = (int)dim_in[4];

    ///////////////// imagem entrada
    Entrada = mxGetPr(prhs[4]);
    O = int3Dmalloc(M, N, 3, 0);

    if (imprimirPts != 0)
        S = int3Dmalloc(M, N, 3, 255);

    u = 0;
    for (k = 0; k < 3; k++)
    {
        for (i = 0; i < M; i++)
        {
            for (j = 0; j < N; j++)
            {
                O[i][j][k] = (int)Entrada[u++];
            }
        }
    }

    ///////////////////////////////

    nq = 70000;

    quadrado = (int *) malloc(nq * sizeof(int));
    ERROR_MALLOC(quadrado);

    for (i = 0; i < nq; i++)
        quadrado[i] = i * i;

    // problema

    int **A = int2Dmalloc(M, N, inf);
    int **V = int2Dmalloc(M, N, 0);

    double dist = DT(A, V, X, Y, Z, Lab, Nvox, M, N, q, O, S, imprimir, imprimirPts);

    const mwSize outDims1[1] = {(const mwSize)1};

    plhs[0] = (mxArray *) mxCreateNumericArray(1, outDims1, mxDOUBLE_CLASS, mxREAL);
    Vretorno = mxGetPr(plhs[0]);

    Vretorno[0] = (double)dist;

    if (imprimir != 0)
    {
        //Retornar Original
        const mwSize outDims2[3] = {(const mwSize)M, (const mwSize) N, (const mwSize) 3};

        plhs[1] = (mxArray *) mxCreateNumericArray(3, outDims2, mxDOUBLE_CLASS, mxREAL);
        Vretorno = mxGetPr(plhs[1]);

        u = 0;
        for (k = 0; k < 3; k++)
            for (j = 0; j < N; j++)
                for (i = 0; i < M; i++)
                    Vretorno[u++] = (double)O[i][j][k];

        if (imprimirPts != 0)
        {
            plhs[2] = (mxArray *) mxCreateNumericArray(3, outDims2, mxDOUBLE_CLASS, mxREAL);
            Vretorno = mxGetPr(plhs[2]);

            u = 0;
            for (k = 0; k < 3; k++)
                for (j = 0; j < N; j++)
                    for (i = 0; i < M; i++)
                        Vretorno[u++] = (double)S[i][j][k];
        }
    }

    int2Dfree(A, M);
    int2Dfree(V, M);
    int3Dfree(O, M, N);
    if (imprimirPts != 0)
        int3Dfree(S, M, N);
    free(quadrado);
}

double **double2Dmalloc(int M, int N, int valor)
{
    int i, j;
    double **A = (double **) malloc (M * sizeof(double*));
    ERROR_MALLOC(A);

    for(i = 0; i < M; i++)
    {
        A[i] = (double *) malloc (N * sizeof(double));
        ERROR_MALLOC(A[i]);

        for(j = 0; j < N; j++)
        {
            A[i][j] = valor;
        }
    }
    return A;
}

void double2Dfree(double **A, int M)
{
    int i;
    for(i = 0; i < M; i++)
    {
        free(A[i]);
    }
    free(A);
}

int ***int3Dmalloc(int M, int N, int L, int valor)
{
    int i, j, k;
    int ***A = (int ***)malloc(M * sizeof(int **));
    ERROR_MALLOC(A);
    for(i = 0; i < M; i++)
    {
        A[i] = (int **) malloc (N * sizeof(int*));
        ERROR_MALLOC(A[i]);
        for(j = 0; j < N; j++)
        {
            A[i][j] = (int *) malloc (L * sizeof(int));
            ERROR_MALLOC(A[i][j]);
            for(k = 0; k < L; k++)
            {
                A[i][j][k] = valor;
            }
        }
    }
    return A;
}

int **int2Dmalloc(int M, int N, int valor)
{
    int i, j;
    int **A = (int **) malloc (M * sizeof(int*));
    ERROR_MALLOC(A);

    for(i = 0; i < M; i++)
    {
        A[i] = (int *) malloc (N * sizeof(int));
        ERROR_MALLOC(A[i]);

        for(j = 0; j < N; j++)
        {
            A[i][j] = valor;
        }
    }
    return A;
}

void int2Dfree(int **A, int M)
{
    int i;
    for(i = 0; i < M; i++)
    {
        free(A[i]);
    }
    free(A);
}

void int3Dfree(int ***A, int M, int N)
{
    int i, j;
    for(i = 0; i < M; i++)
    {
        for(j =0 ; j < N; j++)
        {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);
}

double DT (int **A, int **V, double *X, double *Y, double *Z, double *Lab, int Nvox, int M, int N, int q, int ***O, int ***S, int imprimir, int imprimirPts)
{
    inicializa(X, Y, Lab, Nvox, A, V);

    step1(A, V, M, N);
    step2(A, V, M, N);

    int i, j, k, u, label;
    int somas[q][3];
    int qtds[q];
    double dist = 0;

    //Inicializar Matrizes
    for (i = 0; i < q; i++)
    {
        for (j = 0; j < 3; j++)
        {
            somas[i][j] = 0;
        }
        qtds[i] = 0;
    }

    // Calcular as quantidades e somas

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            label = V[i][j];
            for (k = 0; k < 3; k++)
            {
                somas[label][k] += O[i][j][k];
            }
            qtds[label]++;
        }
    }


    // Calcular as medias
    for (label = 0; label < q; label++)
    {
        for (j = 0; j < 3; j++)
        {
            if (qtds[label])
                somas[label][j] /= qtds[label];
        }
    }

    // Transformar O em Voronoi
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            label = V[i][j];
            for (k = 0; k < 3; k++)
            {
                dist += quadrado[abs(O[i][j][k] - somas[label][k])];
                O[i][j][k] = somas[label][k];
            }
        }
    }
    dist /= (double) (3 * M * N);
    dist = sqrt(dist);


    if(imprimir != 0)
    {
        if (imprimirPts != 0)
        {
            for (u = 0; u < Nvox; u++)
            {
                for (k = 0; k < 3; k++)
                    S[(int)X[u]][(int)Y[u]][k] = O[(int)X[u]][(int)Y[u]][k];
            }
        }

        if (imprimir == 2)
        {
            for (i = 0; i < M; i++)
            {
                for (j = 1; j < N; j++)
                {
                    if(V[i][j] != V[i][j-1])
                    {
                        for (k = 0; k < 3; k++)
                        {
                            O[i][j][k] = 255;
                            O[i][j-1][k] = 255;
                        }
                    }
                }
            }

            for (j = 0; j < N; j++)
            {
                for (i = 1; i < M; i++)
                {
                    if(V[i][j] != V[i-1][j])
                    {
                        for (k = 0; k < 3; k++)
                        {
                            O[i][j][k] = 255;
                            O[i-1][j][k] = 255;
                        }
                    }
                }
            }
        }
    }

    return dist;
}

void inicializa(double *X, double *Y, double *Lab, int Nvox, int **A, int **V)
{
    int u;

    for (u = 0; u < Nvox; u++)
    {
        A[(int)X[u]][(int)Y[u]] = 0;
        V[(int)X[u]][(int)Y[u]] = (int)Lab[u];
    }
}

void step1 (int **A, int **V, int M, int N)
{
    int i, j;
    int x, d, label;
    for(i = 0; i < M; i++)
    {
        //FORWARD
        x = -1;
        label = V[i][0];
        for(j = 0 ; j < N; j++)
        {
            if (A[i][j] == 0)
            {
                x = j;
                label = V[i][j];
            }
            else if(x > 0)
            {
                V[i][j] = label;
                A[i][j] = quadrado[ABS(j - x)];
            }
        }
        //BACKWARD
        x = -1;
        label = V[i][N - 1];
        for(j = N - 1; j >= 0; j--)
        {
            if (A[i][j] == 0)
            {
                x = j;
                label = V[i][j];
            }
            else if(x > 0)
            {
                d = quadrado[ABS(j - x)];
                if (d < A[i][j])
                {
                    V[i][j] = label;
                    A[i][j] = d;
                }
                else if (d == A[i][j])
                    V[i][j] = label;

            }
        }
    }
}

//Algoritmo 4
void step2 (int **A, int **V, int M, int N)
{
    int i, j, a, b, m, n;
    int *buff = (int *) malloc(M * sizeof(int));
    ERROR_MALLOC(buff);
    int *buffV = (int *) malloc(M * sizeof(int));
    ERROR_MALLOC(buffV);

    for (j = 0; j < N; j++)
    {
        for (i = 0; i < M; i++)
        {
            buff[i] = A[i][j];
            buffV[i] = V[i][j];
        }
        //FORWARD
        a = 0;
        for (i = 1; i < M; i++)
        {
            if (a > 0) a--;
            if (buff[i] > buff[i - 1])
            {
                b = (buff[i] - buff[i - 1]) / 2;
                if (b >= M - i) b = (M - 1)- i;
                for (n = a; n <= b; n++)
                {
                    m = buff[i - 1] + quadrado[ABS(n + 1)];
                    if (buff[i + n] < m) break;
                    if (A[i + n][j] > m)
                    {
                        A[i + n][j] = m;
                        V[i + n][j] = buffV[i - 1];
                    }
                    else if (m == A[i + n][j])
                        V[i + n][j] = buffV[i - 1];
                }
                a = b;
            }
            else
            {
                a = 0;
            }
        }

        //BACKWARD
        a = 0;
        for (i = M - 2; i >= 0; i--)
        {
            if (a > 0) a--;
            if (buff[i] > buff[i + 1])
            {
                b = (buff[i] - buff[i + 1]) / 2;
                if (i - b < 0) b = i;
                for (n = a; n <= b; n++)
                {
                    m = buff[i + 1] + quadrado[ABS(n + 1)];
                    if (buff[i - n] < m) break;
                    if (A[i - n][j] > m)
                    {
                        A[i - n][j] = m;
                        V[i - n][j] = buffV[i + 1];
                    }
                    else if (m == A[i - n][j])
                        V[i - n][j] = buffV[i + 1];
                }
                a = b;
            }
            else
            {
                a = 0;
            }
        }
    }
    free(buff);
    free(buffV);
}
