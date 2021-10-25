#include <iostream>
#include <stdexcept>
#include "matrix.cpp"

int main(){
    Matrix M(4, 4), S(4, 1);

    float M_arr[16] = {
        2, 2, 3, 3,
        2, 3, 1, 0,
        1, 2, 0 ,0,
        5, 0 ,0 ,0
    };

    float S_arr[5] = {
        0,
        0,
        0,
        1
    };

    M = M_arr;
    S = S_arr;
    Matrix U = joinMatrices(M, S);
    printf("The Solution To The Following System Of Equations:\n");
    U.printMatrix();
    U.reducedRowEchelonForm_();
    printf("Is:\n");
    Matrix X = U.subMatrix(0, 4, 4, 5);
    X.printMatrix();

    M.freeMatrix_();
    S.freeMatrix_();
    U.freeMatrix_();
    X.freeMatrix_();
}
