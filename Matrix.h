#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#define DATA_TYPE float
using namespace std;

class Matrix{
    private:
        int rows;
        int columns;
        float **matrix;
        const int PRECISION = 0.000001; //We need to define it so that we can take number in the interval (-PRECISION, PRECISION) as 0

    public:
        float return_min(float a, float b);
        float return_max(float a, float b);
        float distance(float a, float b);
        int getRows();
        int getColumns();
        float** getMatrix();
        //Constructors and Destructors
        Matrix(int aRows = 0, int aColumns = 0);
        Matrix(const Matrix&) = default;
        ~Matrix() = default;
        Matrix& operator=(const Matrix& other) = default;

        //Operator overloading
        Matrix operator +(Matrix secondMatrix);
        Matrix operator -(Matrix secondMatrix);
        Matrix operator * (float scalar);
        Matrix operator / (float scalar);
        void operator *= (float scalar);
        void operator *= (Matrix rightMatrix);
        void operator /= (float scalar);
        void operator += (Matrix leftMatrix);
        void operator -= (Matrix leftMatrix);
        Matrix operator*(Matrix rightMatrix);
        void operator = (float arr[]);
        bool operator == (Matrix leftMatrix);

        //Functions
        void inverse_();
        void populateWithRisingIntegers_(float starting_value = 0);
        void populateWithDiagonalValue_(float value = 1);
        void populateWithValue_(float value = 0);
        void populateWithRandomNumbers_(float min_value = 0, float max_value = 1, int seed = (unsigned) time(0));
        void add_(Matrix A);
        void scalar_(float scalar);
        void printMatrix(char space = ' ');
        void freeMatrix_();
        void changeZeros_();
        void changeNegatives_(float new_value = 0);
        Matrix transpose();
        void transpose_();
        void reshape_(int new_rows, int new_columns);
        Matrix reshape(int new_rows, int new_columns);
        Matrix copyMatrix();
        float det();
        int rank();
        Matrix reducedRowEchelonForm();
        void reducedRowEchelonForm_();
        Matrix inverse();
        void swap_rows(int row_a, int row_b);
        void add_rows(int row_a, int row_b, float scalar = 1);
        void scalar_row(int row, float scalar);
        void swap_columns(int column_a, int column_b);
        void add_columns(int column_a, int column_b, float scalar = 1);
        void scalar_columns(int column, float scalar);
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
        Matrix scalar(Matrix A, float scalar);
        float det_rec(float **matrix, int n);
        Matrix reducedRowEchelonForm(Matrix M);
        Matrix convolution (Matrix sourceMatrix, Matrix convolutionMatrix, int stride_rows = 1, int stride_columns = 1, bool normalize = true);

};
#endif