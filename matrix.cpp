#include <iostream>
#include <stdexcept>
#define PRECISION 0.000001 //We need to define it so that we can take number in the interval (-PRECISION, PRECISION) as 0
using namespace std;

//Function declaration - Part 1

class Matrix;
float det_rec(float **matrix, int n);
void changeZeros(Matrix M);

float return_min(float a, float b){
    return (a <= b) * a + (a > b) * b;
}

float return_max(float a, float b){
    return (a >= b) * a + (a < b) * b;
}

float distance(float a, float b){
    return (a - b) * (a >= b) + (b - a) * (a < b);
}

class Matrix{

    public:
        int rows;
        int columns;
        float **matrix;
        Matrix *all_matrices = NULL;
        int number_of_matrices = 0;

        Matrix operator +(Matrix secondMatrix){
            if(columns != secondMatrix.columns || rows != secondMatrix.rows){
                printf("A.shape must match B.shape\n");
                throw("Logic");
            }
            Matrix newMatrix(rows, columns);
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                        newMatrix.matrix[row_index][column_index] = matrix[row_index][column_index] + secondMatrix.matrix[row_index][column_index];
                }
            }
            changeZeros(newMatrix);
            return newMatrix;
        }

        Matrix operator * (float scalar){
            Matrix newMatrix(rows, columns);
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                    newMatrix.matrix[row_index][column_index] = matrix[row_index][column_index] * scalar;
                }
            }
            changeZeros(newMatrix);
            return newMatrix;
        }

        void operator *= (float scalar){
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                    matrix[row_index][column_index] *= scalar;
                }
            }
            changeZeros_();
        }

        void operator += (Matrix leftMatrix){
            if(columns != leftMatrix.columns || rows != leftMatrix.rows){
                printf("Matrices Shapes Must Be Equal.\n");
                throw("Logic");
            }

            //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < leftMatrix.columns; column_index++){
                    matrix[row_index][column_index] += leftMatrix.matrix[row_index][column_index];
                }
            }
            changeZeros_();
        }

        Matrix operator*(Matrix leftMatrix){
            if(columns != leftMatrix.rows){
                printf("A.columns Must Be Equal To B.rows.\n");
                throw("Logic");
            }

            Matrix newMatrix(rows, leftMatrix.columns);
            //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < leftMatrix.columns; column_index++){
                    float value = 0;
                    for (int i = 0; i < columns; i++){
                        value += matrix[row_index][i] * leftMatrix.matrix[i][column_index];
                    }
                    newMatrix.matrix[row_index][column_index] = value;
                }
            }
            changeZeros(newMatrix);
            return newMatrix;
        }

        void operator = (float arr[]){
            for (int i = 0; i < columns * rows; i++){
                int column_index = i % columns;
                int row_index = i / columns;
                matrix[row_index][column_index] = arr[i];
            }
        }

        bool operator == (Matrix leftMatrix){
            if (rows != leftMatrix.rows || columns != leftMatrix.columns){
                return false;
            }
             for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                    if (matrix[row_index][column_index] != leftMatrix.matrix[row_index][column_index]){
                        return false;
                    }
                }
             }
            return true;
        }

        void inverse_(){
            Matrix inverMatrix = inverse();
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                    matrix[row_index][column_index] = inverMatrix.matrix[row_index][column_index];
                }
            }
            inverMatrix.freeMatrix_();
        }


        Matrix(int aRows, int aColumns){
            rows = aRows;
            columns = aColumns;
            matrix = (float**) malloc(sizeof(float*) * rows);
            for (int row_index = 0; row_index < rows; row_index++){
                matrix[row_index] = (float*) malloc(sizeof(float) * columns);
            }
            number_of_matrices++;
        }

        void populateWithRisingIntegers_(float starting_value = 0){
            for (int row_index = 0; row_index < rows; row_index++){
                for(int column_index = 0; column_index < columns; column_index++){
                    matrix[row_index][column_index] = starting_value + row_index * columns + column_index;
                }
            }
        }

        void populateWithDiagonalValue_(float value = 1){
            for (int row_index = 0; row_index < rows; row_index++){
                for(int column_index = 0; column_index < columns; column_index++){
                    if(row_index == column_index){
                        matrix[row_index][column_index] = value;
                    }
                    else{
                        matrix[row_index][column_index] = 0;
                    }
                }
            }
        }

        void populateWithValue_(float value = 0){
            for (int row_index = 0; row_index < rows; row_index++){
                for(int column_index = 0; column_index < columns; column_index++){
                    matrix[row_index][column_index] = value;
                }
            }
        }

        void add_(Matrix A){
            if(A.columns != columns || A.rows != rows){
                printf("A.shape must match B.shape\n");
                throw("Logic");
            }

            //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                    matrix[row_index][column_index] += A.matrix[row_index][column_index];
                }
            }
            changeZeros_();
        }

        void scalar_(float scalar){
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                    matrix[row_index][column_index] *= scalar;
                }
            }
            changeZeros_();
        }

        void printMatrix(char space = ' '){
            changeZeros_();
            for (int row_index = 0; row_index < rows; row_index++){
                for(int column_index = 0; column_index < columns; column_index++){
                    printf("%.2f%c", matrix[row_index][column_index], space);
                }
                printf("\n");
            }
            printf("\n");
        }

        void freeMatrix_(){
             for (int row_index = 0; row_index < rows; row_index++){
                free(matrix[row_index]);
            }
            free(matrix);
        }

        void changeZeros_(){
            //Change -0.00 to 0.00
            for (int row_index = 0; row_index < rows; row_index++){
                for (int column_index = 0; column_index < columns; column_index++){
                    if(matrix[row_index][column_index] == -0){
                        matrix[row_index][column_index] = 0;
                    }
                }
            }
        }

        Matrix transpose(){
            Matrix transposedMatrix = Matrix(columns, rows);
             for (int row_index = 0; row_index < rows; row_index++){
                for(int column_index = 0; column_index < columns; column_index++){
                    transposedMatrix.matrix[column_index][row_index] = matrix[row_index][column_index];
                }
            }
            changeZeros(transposedMatrix);
            return transposedMatrix;
        }

        void transpose_(){
             float **current_matrix = (float **)malloc(sizeof(float *) * rows);
             //Create Copy Of Current Matrix and free current matrix
             for (int row_index = 0; row_index < rows; row_index++){
                current_matrix[row_index] = (float *)malloc(sizeof(float) * columns);
                for (int column_index = 0; column_index < columns; column_index++){
                    current_matrix[row_index][column_index] = matrix[row_index][column_index];
                }
                free(matrix[row_index]);
             }

             //Change rows and columns
             int temp = rows;
             rows = columns;
             columns = temp;

             matrix = (float **)realloc(matrix, sizeof(float *) * rows);
             for (int row_index = 0; row_index < rows; row_index++){
                matrix[row_index] = (float *)malloc(sizeof(float) * columns);
                for (int column_index = 0; column_index < columns; column_index++){
                    matrix[row_index][column_index] = current_matrix[column_index][row_index];
                }
             }
             for (int old_row_index = 0; old_row_index < columns; old_row_index++){
                free(current_matrix[old_row_index]);
             }
             free(current_matrix);
             changeZeros_();
        }

        Matrix copyMatrix(){
            Matrix newMatrix(rows, columns);
            for (int row_index = 0; row_index < rows; row_index++){
                for(int column_index = 0; column_index < columns; column_index++){
                    newMatrix.matrix[row_index][column_index] = matrix[row_index][column_index];
                }
            }
            return newMatrix;
        }

        float det(){
            if(columns != rows){
                printf("Matrix must be square to calculate determinant.\n");
                throw;
            }
            float result = det_rec(matrix, rows);
            return result;
        }

        void reducedRowEchelonForm_(){
            int leading_entry_row_index = 0; //What Row are we at
            int leading_entry_column_index = 0; //What Column are we at

            while (leading_entry_column_index < columns && leading_entry_row_index < rows){
                int chosen_row = -1, chosen_column = -1;
                for (int row_index = leading_entry_row_index; row_index < rows; row_index++){
                    for (int column_index = leading_entry_column_index; column_index < columns; column_index++){
                        if(distance(matrix[row_index][column_index], 0) > PRECISION){
                            if(chosen_row == -1 || column_index < chosen_column){
                                chosen_row = row_index;
                                chosen_column = column_index;
                            }
                        }
                    }
                }

                //It means we are done because all rows below are zeros
                if(chosen_row == -1){
                    break;
                }

                leading_entry_column_index = chosen_column;
                swap_rows(chosen_row, leading_entry_row_index);
                float scalar_to_norm_row = 1 / matrix[leading_entry_row_index][leading_entry_column_index];
                //printf("SHOULDCHANGGERE\n");
                scalar_row(leading_entry_row_index, scalar_to_norm_row);

                for (int row_below_index = leading_entry_row_index + 1; row_below_index < rows; row_below_index++){
                    //If it equals zero we don't need to do anything
                    if (matrix[row_below_index][leading_entry_column_index] != 0){
                        float scalar_to_norm_row = -1 / matrix[row_below_index][leading_entry_column_index];
                        scalar_row(row_below_index, scalar_to_norm_row);
                        add_rows(row_below_index, leading_entry_row_index);
                    }
                }
                leading_entry_row_index++;
            }
            //Start making all entries above the leading entry to 0
            for (int row_index = rows - 1; row_index >= 0; row_index--){
                int leading_entry_column = 0;
                while (distance(matrix[row_index][leading_entry_column], 0) < PRECISION && leading_entry_column < columns){
                    leading_entry_column++;
                }
                if(leading_entry_column < columns){
                    for (int above_row_index = row_index - 1; above_row_index >= 0; above_row_index--){
                        if(matrix[above_row_index][leading_entry_column] != 0){
                            float scalar_to_norm_row = -1 * matrix[above_row_index][leading_entry_column];
                            add_rows(above_row_index, row_index, scalar_to_norm_row);
                        }
                    }
                }
            }
            changeZeros_();
        }

        Matrix inverse(){
            if(columns != rows){
                printf("Matrix must be square to have inverse.\n");
                throw;
            }

            if (distance(det(), 0) < PRECISION){
                printf("Singuar matrix does not have an inverse.\n");
                throw;
            }

            Matrix inverseMatrix = copyMatrix();

            inverseMatrix.columns *= 2;

            //We will get the inverse by taking the matrix and joining the identity matrix to the left of it and then making the rref
            //Expand each row by twice the number of columns
            for (int row_index = 0; row_index < rows; row_index++){
                inverseMatrix.matrix[row_index] = (float *) realloc(inverseMatrix.matrix[row_index], sizeof(float) * columns * 2);
                for (int column_index = columns; column_index < 2 * columns; column_index++){
                    if (column_index == row_index + columns){
                        inverseMatrix.matrix[row_index][column_index] = 1;
                    }
                    else {
                        inverseMatrix.matrix[row_index][column_index] = 0;
                    }
                }
            }
            inverseMatrix.reducedRowEchelonForm_();
            //Return each row to the original number of columns
            for (int row_index = 0; row_index < rows; row_index++){
                for(int column_index = 0; column_index < columns * 2; column_index++){
                    inverseMatrix.matrix[row_index][column_index] = inverseMatrix.matrix[row_index][column_index + columns];
                }
                inverseMatrix.matrix[row_index] = (float *)realloc(inverseMatrix.matrix[row_index], sizeof(float) * columns);
            }
            inverseMatrix.columns /= 2;
            changeZeros(inverseMatrix);
            return inverseMatrix;

        }

        void swap_rows(int row_a, int row_b){
            for (int i = 0; i < columns; i++){
                float temp = matrix[row_a][i];
                matrix[row_a][i] = matrix[row_b][i];
                matrix[row_b][i] = temp;
            }
        }

        void add_rows(int row_a, int row_b, float scalar = 1){
            for (int i = 0; i < columns; i++){
                matrix[row_a][i] += matrix[row_b][i] * scalar;
            }
        }

        void scalar_row(int row, float scalar){
            for (int i = 0; i < columns; i++){
                matrix[row][i] *= scalar;
            }
        }

        void swap_columns(int column_a, int column_b){
            for (int i = 0; i < rows; i++){
                float temp = matrix[i][column_a];
                matrix[i][column_a] = matrix[i][column_b];
                matrix[i][column_b] = temp;
            }
        }

        void add_columns(int column_a, int column_b, float scalar = 1){
            for (int i = 0; i < rows; i++){
                matrix[i][column_a] += matrix[i][column_b] * scalar;
            }
        }

        void scalar_columns(int column, float scalar){
            for (int i = 0; i < rows; i++){
                matrix[i][column] *= scalar;
            }
        }

};

//Overloading existing types with matrix type
Matrix operator *(float scalar, Matrix M){
    Matrix newMatrix(M.rows, M.columns);
    for (int row_index = 0; row_index < M.rows; row_index++){
        for (int column_index = 0; column_index < M.columns; column_index++){
            newMatrix.matrix[row_index][column_index] = M.matrix[row_index][column_index] * scalar;
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

//Matrix Function declaration - Part 2
Matrix dot(Matrix A, Matrix B);
Matrix scalar(Matrix A, float scalar);
Matrix add(Matrix A, Matrix B);

void changeZeros(Matrix M){
    //Change -0.00 to 0.00
    for (int row_index = 0; row_index < M.rows; row_index++){
        for (int column_index = 0; column_index < M.columns; column_index++){
            if(M.matrix[row_index][column_index] == -0){
                M.matrix[row_index][column_index] = 0;
            }
        }
    }
}

Matrix dot(Matrix A, Matrix B){
    if(A.columns != B.rows){
        printf("A.columns Must Be Equal To B.rows.\n");
        throw("Logic");
    }

    Matrix newMatrix(A.rows, B.columns);
    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < A.rows; row_index++){
        for (int column_index = 0; column_index < B.columns; column_index++){
            float value = 0;
            for (int i = 0; i < A.columns; i++){
                value += A.matrix[row_index][i] * B.matrix[i][column_index];
            }
            newMatrix.matrix[row_index][column_index] = value;
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

Matrix add(Matrix A, Matrix B){
    if(A.columns != B.columns || A.rows != B.rows){
        printf("A.shape must match B.shape\n");
        throw("Logic");
    }

    Matrix newMatrix(A.rows, A.columns);
    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < A.rows; row_index++){
        for (int column_index = 0; column_index < B.columns; column_index++){
            newMatrix.matrix[row_index][column_index] = A.matrix[row_index][column_index] + B.matrix[row_index][column_index];
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

Matrix scalar(Matrix A, float scalar){
    Matrix newMatrix(A.rows, A.columns);
    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < A.rows; row_index++){
        for (int column_index = 0; column_index < A.columns; column_index++){
            newMatrix.matrix[row_index][column_index] = A.matrix[row_index][column_index]  * scalar;
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

float det_rec(float **matrix, int n){
    //The det of a 1x1 matrix is the value of the only entry in the matrix
    if(n == 1){
        return **matrix;
    }
    float current_det = 0;
    int reduce_row_index = 0;
    for (int reduce_column_index = 0; reduce_column_index < n; reduce_column_index++){
        //Generate smaller matrix relevant to the current index
        float **smaller_matrix = (float**)malloc(sizeof(float*) * (n - 1));
        for (int i = 0; i < n - 1; i++){
            smaller_matrix[i] = (float*)malloc(sizeof(float) * (n - 1));
        }
        //populate smaller matrix
        for (int row_index = 1; row_index < n; row_index++){
            int small_matrix_col_index = 0;
            for (int column_index = 0; column_index < n; column_index++){
                if (column_index != reduce_column_index){
                    smaller_matrix[row_index - 1][small_matrix_col_index] = matrix[row_index][column_index];
                    small_matrix_col_index++;
                }
            }
        }
        //Get determinant for smaller matrix
        float smaller_det = det_rec(smaller_matrix, n - 1);
        int sign = 1;
        if (reduce_column_index % 2 == 1){
            sign = -1;
        }
        current_det += sign * smaller_det * matrix[reduce_row_index][reduce_column_index];
        //Free smaller matrix
        for (int i = 0; i < n - 1; i++){
            free(smaller_matrix[i]);
        }
        free(smaller_matrix);
    }
    return current_det;
}

Matrix reducedRowEchelonForm(Matrix M){
    Matrix reducedMatrix = M.copyMatrix();
    int leading_entry_row_index = 0; //What Row are we at
    int leading_entry_column_index = 0; //What Column are we at

    while (leading_entry_column_index < reducedMatrix.columns && leading_entry_row_index < reducedMatrix.rows){
        int chosen_row = -1, chosen_column = -1;
        for (int row_index = leading_entry_row_index; row_index < reducedMatrix.rows; row_index++){
            for (int column_index = leading_entry_column_index; column_index < reducedMatrix.columns; column_index++){
                if(distance(reducedMatrix.matrix[row_index][column_index], 0) > PRECISION){
                    if(chosen_row == -1 || column_index < chosen_column){
                        chosen_row = row_index;
                        chosen_column = column_index;
                    }
                }
            }
        }

        //It means we are done because all rows below are zeros
        if(chosen_row == -1){
            break;
        }

        leading_entry_column_index = chosen_column;
        reducedMatrix.swap_rows(chosen_row, leading_entry_row_index);
        float scalar_to_norm_row = 1 / reducedMatrix.matrix[leading_entry_row_index][leading_entry_column_index];
        //printf("SHOULDCHANGGERE\n");
        reducedMatrix.scalar_row(leading_entry_row_index, scalar_to_norm_row);

        for (int row_below_index = leading_entry_row_index + 1; row_below_index < reducedMatrix.rows; row_below_index++){
            //If it equals zero we don't need to do anything
            if (reducedMatrix.matrix[row_below_index][leading_entry_column_index] != 0){
                float scalar_to_norm_row = -1 / reducedMatrix.matrix[row_below_index][leading_entry_column_index];
                reducedMatrix.scalar_row(row_below_index, scalar_to_norm_row);
                reducedMatrix.add_rows(row_below_index, leading_entry_row_index);
            }
        }
        leading_entry_row_index++;
    }
    //Start making all entries above the leading entry to 0
    for (int row_index = reducedMatrix.rows - 1; row_index >= 0; row_index--){
        int leading_entry_column = 0;
        while (distance(reducedMatrix.matrix[row_index][leading_entry_column], 0) < PRECISION && leading_entry_column < reducedMatrix.columns){
            leading_entry_column++;
        }
        if(leading_entry_column < reducedMatrix.columns){
            for (int above_row_index = row_index - 1; above_row_index >= 0; above_row_index--){
                if(reducedMatrix.matrix[above_row_index][leading_entry_column] != 0){
                    float scalar_to_norm_row = -1 * reducedMatrix.matrix[above_row_index][leading_entry_column];
                    reducedMatrix.add_rows(above_row_index, row_index, scalar_to_norm_row);
                }
            }
        }
    }

    //Change -0.00 to 0.00
    for (int row_index = 0; row_index < reducedMatrix.rows; row_index++){
        for (int column_index = 0; column_index < reducedMatrix.columns; column_index++){
            if(reducedMatrix.matrix[row_index][column_index] == -0){
                reducedMatrix.matrix[row_index][column_index] = 0;
            }
        }
    }
    changeZeros(reducedMatrix);
    return reducedMatrix;
}
