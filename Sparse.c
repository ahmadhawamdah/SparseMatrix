#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"

int main (int argc, char *argv[]) {
    
    FILE *pIn, *pOut;
    int size, NNZA, NNZB;
    size = NNZA = NNZB = 0;
    int row, col;
    double val;
    row = col = 0;
    val = 0;
    
    Matrix C, D, E, F, G, H, I, J;
    
    pIn = fopen("int.txt", "r");
    pOut = fopen("out.txt", "w");
//    pIn = fopen(argv[1], "r");
//    pOut = fopen(argv[2], "w");

    fscanf(pIn, "%d %d %d", &size, &NNZA, &NNZB);
    
    if (pIn == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    if (pOut == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    
    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);
    
    for (int i = 0; i < NNZA; i++) {
        fscanf(pIn, "%d ", &row);
        fscanf(pIn, "%d ", &col);
        fscanf(pIn, "%lf ", &val);
        changeEntry(A, row, col, val);
    }
    
    for (int i = 0; i < NNZB; i++) {
        fscanf(pIn, "%d ", &row);
        fscanf(pIn, "%d ", &col);
        fscanf(pIn, "%lf ", &val);
        changeEntry(B, row, col, val);
    }
    fprintf(pOut, "YO AM HERE! \n");
     fprintf(pOut, "A has %d non-zero entries:", NNZA);
    fprintf(pOut, "A has %d non-zero entries:", NNZA);
    printMatrix(pOut, A);
    fprintf(pOut, "\n\n");
    
    
    fprintf(pOut, "B has %d non-zero entries:", NNZB);
    printMatrix(pOut, B);
    fprintf(pOut, "\n\n");
    
    
    fprintf(pOut, "(1.5)*A =");
    C = scalarMult(1.5, A);
    printMatrix(pOut, C);
    fprintf(pOut, "\n\n");
    
    
    fprintf(pOut, "A+B =");
    D = sum(A, B);
    printMatrix(pOut, D);
    fprintf(pOut, "\n\n");
    
    
    fprintf(pOut, "A+A =");
    J = sum(A, A);
    printMatrix(pOut, J);
    fprintf(pOut, "\n\n");
    
    
    fprintf(pOut,"B-A =");
    E = diff(B, A);
    printMatrix(pOut, E);
    fprintf(pOut,"\n\n");
    
    fprintf(pOut,"A-A =");
    F = diff(A, A);
    printMatrix(pOut, F);
    fprintf(pOut,"\n\n");
    
    
    fprintf(pOut,"Transpose(A) =");
    G = transpose(A);
    printMatrix(pOut, G);
    fprintf(pOut,"\n\n");
    
    fprintf(pOut,"A*B =");
    H = product(A, B);
    printMatrix(pOut, H);
    fprintf(pOut,"\n\n");
    
    
    fprintf(pOut,"B*B =");
    I = product(B, B);
    printMatrix(pOut, I);

    
    fclose(pIn);
    fclose(pOut);
}
