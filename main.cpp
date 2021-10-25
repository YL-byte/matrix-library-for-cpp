#include <iostream>
#include <stdexcept>
#include "matrix.cpp"

int main(){
    Matrix A(4, 4);
    float A_arr[16] = {
        2, 2, 3, 3,
        2, 3, 1, 0,
        1, 2, 0 ,0,
        5, 0 ,0 ,0
    };

    A = A_arr;
    float det = A.det();
    int r = A.rank();
    Matrix A_INV = A.inverse();
    Matrix A_T = A.transpose();
    Matrix I = A * A_INV;

    printf("The following example matrix properties:\n\trank: %d\n\tdeterminant: %.2f\n\n", r, det);
    A.printMatrix();
    printf("The Inverse of the matrix is:\n");
    A_INV.printMatrix();
    printf("The Transpose of the matrix is:\n");
    A_T.printMatrix();
    printf("The dot product of the matrix with it's inverse is:\n");
    I.printMatrix();

    A.freeMatrix_();
    A_INV.freeMatrix_();
    A_T.freeMatrix_();
    I.freeMatrix_();

    printf("_______New Example_______\n\n");
    Matrix B(3, 3);
    B.populateWithRisingIntegers_();
    det = B.det();
    r = B.rank();
    Matrix B_reduced = B.reducedRowEchelonForm();
    printf("The following example matrix properties:\n\trank: %d\n\tdeterminant: %.2f\n\n", r, det);
    B.printMatrix();
    printf("The reduced row echelon form is:\n");
    B_reduced.printMatrix();
    B.freeMatrix_();
    B_reduced.freeMatrix_();

}
