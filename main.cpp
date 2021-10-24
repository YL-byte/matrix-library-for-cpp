#include <iostream>
#include <stdexcept>
#include "matrix.cpp"

int main(){
    Matrix A(5, 4), B(3, 3), C(4, 4);
    A.populateWithDiagonalValue_();
    B.populateWithRisingIntegers_(2);
    C.populateWithDiagonalValue_(2);
    A.matrix[0][1] = 1;
    A.matrix[1][0] = 1;
    A.matrix[3][2] = 1;
    A.matrix[0][2] = 0;
    A.matrix[0][3] = 4;

    printf("Matrix C:\n");
    C.printMatrix();
    Matrix CR = reducedRowEchelonForm(C);
    printf("Reduced Row Echelon Form C:\n");
    CR.printMatrix();
    printf("Matrix C Det: %f\n", C.det());

    Matrix BR = reducedRowEchelonForm(B);
    printf("Matrix B:\n");
    B.printMatrix();
    printf("Reduced Row Echelon Form B:\n");
    BR.printMatrix();
    printf("Matrix B Det: %f\n", B.det());

    Matrix AR = reducedRowEchelonForm(A);
    printf("Matrix A:\n");
    A.printMatrix();
    printf("Reduced Row Echelon Form A:\n");
    AR.printMatrix();
    printf("Matrix A Det: %f", A.det());

    A.freeMatrix_();
    B.freeMatrix_();
    C.freeMatrix_();

    AR.freeMatrix_();
    BR.freeMatrix_();
    CR.freeMatrix_();

}
