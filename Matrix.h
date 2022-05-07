#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#define DATA_TYPE int
using namespace std;

class Matrix{
    private:
        int rows;
        int columns;
        DATA_TYPE **matrix;
        const int PRECISION = 0.000001; //We need to define it so that we can take number in the interval (-PRECISION, PRECISION) as 0

    public:
        DATA_TYPE return_min(DATA_TYPE a, DATA_TYPE b);
        DATA_TYPE return_max(DATA_TYPE a, DATA_TYPE b);
        DATA_TYPE distance(DATA_TYPE a, DATA_TYPE b);
        int getRows();
        int getColumns();
        DATA_TYPE** getMatrix();
        //Constructors and Destructors
        Matrix(int aRows = 0, int aColumns = 0);
        Matrix(const Matrix&) = default;
        ~Matrix() = default;
        Matrix& operator=(const Matrix& other) = default;

        //Operator overloading
        Matrix operator +(Matrix secondMatrix);
        Matrix operator -(Matrix secondMatrix);
        Matrix operator * (DATA_TYPE scalar);
        Matrix operator / (DATA_TYPE scalar);
        void operator *= (DATA_TYPE scalar);
        void operator *= (Matrix rightMatrix);
        void operator /= (DATA_TYPE scalar);
        void operator += (Matrix leftMatrix);
        void operator -= (Matrix leftMatrix);
        Matrix operator*(Matrix rightMatrix);
        void operator = (DATA_TYPE arr[]);
        bool operator == (Matrix leftMatrix);

        //Functions
        void inverse_();
        void populateWithRisingIntegers_(DATA_TYPE starting_value = 0);
        void populateWithDiagonalValue_(DATA_TYPE value = 1);
        void populateWithValue_(DATA_TYPE value = 0);
        void populateWithRandomNumbers_(DATA_TYPE min_value = 0, DATA_TYPE max_value = 1, int seed = (unsigned) time(0));
        void add_(Matrix A);
        void scalar_(DATA_TYPE scalar);
        void printMatrix(char space = ' ');
        void freeMatrix_();
        void changeZeros_();
        void changeNegatives_(DATA_TYPE new_value = 0);
        Matrix transpose();
        void transpose_();
        void reshape_(int new_rows, int new_columns);
        Matrix reshape(int new_rows, int new_columns);
        Matrix copyMatrix();
        DATA_TYPE det();
        int rank();
        Matrix reducedRowEchelonForm();
        void reducedRowEchelonForm_();
        Matrix inverse();
        void swap_rows(int row_a, int row_b);
        void add_rows(int row_a, int row_b, DATA_TYPE scalar = 1);
        void scalar_row(int row, DATA_TYPE scalar);
        void swap_columns(int column_a, int column_b);
        void add_columns(int column_a, int column_b, DATA_TYPE scalar = 1);
        void scalar_columns(int column, DATA_TYPE scalar);
        void joinRight_(Matrix rightMatrix);
        void unionBelow(Matrix bottomMatrix);
        Matrix subMatrix(int start_row_index = 0, int end_row_index = 0, int start_column_index = 0, int end_column_index = 0);
        void subMatrix_(int start_row_index = 0, int end_row_index = 0, int start_column_index = 0, int end_column_index = 0);
        Matrix pooling(int pooling_rows = 3, int pooling_columns = 3, int stride_rows = 1, int stride_columns = 1);
        void convolution_(Matrix convolutionMatrix, int stride_rows = 1, int stride_columns = 1, bool normalize = true);
        void pooling_(int pooling_rows = 3, int pooling_columns = 3, int stride_rows = 1, int stride_columns = 1);
        Matrix unionMatrices(Matrix upperMatrix, Matrix lowerMatrix);
        Matrix joinMatrices(Matrix leftMatrix, Matrix rightMatrix);
        void changeZeros(Matrix M);
        Matrix dot(Matrix A, Matrix B);
        Matrix add(Matrix A, Matrix B);
        Matrix scalar(Matrix A, DATA_TYPE scalar);
        DATA_TYPE det_rec(DATA_TYPE **matrix, int n);
        Matrix reducedRowEchelonForm(Matrix M);
        Matrix convolution (Matrix sourceMatrix, Matrix convolutionMatrix, int stride_rows = 1, int stride_columns = 1, bool normalize = true);

};
#endif
