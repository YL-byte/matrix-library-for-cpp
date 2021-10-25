#include <iostream>
#include <stdexcept>
#include "matrix.cpp"

int main(){
    Matrix M(4, 4), S(4, 1);

    float M_arr[16] = {
        2, 2, 3, 3,
        2, 3, 1, 0,
        1, 2, 0 ,0,
        1, 0 ,1 ,0
    };

    float S_arr[5] = {
        3,
        1,
        2,
        3
    };

    M = M_arr;
    S = S_arr;

    Matrix J = joinMatrices(M, S);
    int r_M = M.rank();
    int r_J = J.rank();
    printf("Try To Solve M*X = S For X\n");
    if(r_J > r_M){
        printf("There Is No Solution.\n");
    }
    else if (r_J == r_M && r_J == J.rows){
        printf("The Solution To The Following System Of Equations:\n");
        J.printMatrix();
        J.reducedRowEchelonForm_();
        printf("Is:\n");
        Matrix X = J.subMatrix(0, 4, 4, 5);
        X.printMatrix();
        X.freeMatrix_();
        printf("Another Way To Solve The Matrix Is By Multiplying Both Sides By M^-1 From The Left:\n");
        Matrix M_inv = M.inverse();
        M_inv.printMatrix();
        Matrix X1 = M_inv * S;
        X1.printMatrix();
        X1.freeMatrix_();

    }
    else {
        printf("There Are Infinite Solutions:\n");
        J.printMatrix();
    }

    S.freeMatrix_();
    M.freeMatrix_();
    J.freeMatrix_();
}
