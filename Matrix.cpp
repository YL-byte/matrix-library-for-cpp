#include "Matrix.h"

float Matrix::return_min(float a, float b){
    return (a <= b) * a + (a > b) * b;
}

float Matrix::return_max(float a, float b){
    return (a >= b) * a + (a < b) * b;
}

float Matrix::distance(float a, float b){
    return (a - b) * (a >= b) + (b - a) * (a < b);
}

int Matrix::getRows()
{
    return this->rows;
}

int Matrix::getColumns()
{
    return this->rows;
}

float** Matrix::getMatrix()
{
    return this->matrix;
}

Matrix::Matrix(int aRows, int aColumns){
    rows = aRows;
    columns = aColumns;
    matrix = (float**) malloc(sizeof(float*) * rows);
    for (int row_index = 0; row_index < rows; row_index++){
        matrix[row_index] = (float*) malloc(sizeof(float) * columns);
    }
}

Matrix Matrix::operator +(Matrix secondMatrix){
    if(columns != secondMatrix.columns || rows != secondMatrix.rows){
        throw std::invalid_argument("A.shape must match B.shape\n");
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

Matrix Matrix::operator -(Matrix secondMatrix){
    if(columns != secondMatrix.columns || rows != secondMatrix.rows){
        throw std::invalid_argument("A.shape must match B.shape\n");            }
    Matrix newMatrix(rows, columns);
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
                newMatrix.matrix[row_index][column_index] = matrix[row_index][column_index] - secondMatrix.matrix[row_index][column_index];
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

Matrix Matrix::operator * (float scalar){
    Matrix newMatrix(rows, columns);
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            newMatrix.matrix[row_index][column_index] = matrix[row_index][column_index] * scalar;
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

Matrix Matrix::operator / (float scalar){
    if (distance(scalar, 0) < PRECISION){
        throw std::invalid_argument("Can't Divide By Zero.\n");
    }
    Matrix newMatrix(rows, columns);
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            newMatrix.matrix[row_index][column_index] = matrix[row_index][column_index] / scalar;
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

void Matrix::operator *= (float scalar){
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] *= scalar;
        }
    }
    changeZeros_();
}

void Matrix::operator *= (Matrix rightMatrix){
    if(columns != rightMatrix.rows){
        throw std::invalid_argument("A.columns Must Be Equal To B.rows.\n");
    }
    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < rightMatrix.columns; column_index++){
            float value = 0;
            for (int i = 0; i < columns; i++){
                value += matrix[row_index][i] * rightMatrix.matrix[i][column_index];
            }
            matrix[row_index][column_index] = value;
        }
    }
    changeZeros_();
}

void Matrix::operator /= (float scalar){
    if (distance(scalar, 0) < PRECISION){
        throw std::invalid_argument("Can't Divide By Zero.\n");
    }
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] *= scalar;
        }
    }
    changeZeros_();
}

void Matrix::operator += (Matrix leftMatrix){
    if(columns != leftMatrix.columns || rows != leftMatrix.rows){
        throw std::invalid_argument("Matrices Shapes Must Be Equal.\n");
    }

    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < leftMatrix.columns; column_index++){
            matrix[row_index][column_index] += leftMatrix.matrix[row_index][column_index];
        }
    }
    changeZeros_();
}

void Matrix::operator -= (Matrix leftMatrix){
    if(columns != leftMatrix.columns || rows != leftMatrix.rows){
        throw std::invalid_argument("Matrices Shapes Must Be Equal.\n");
    }

    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < leftMatrix.columns; column_index++){
            matrix[row_index][column_index] -= leftMatrix.matrix[row_index][column_index];
        }
    }
    changeZeros_();
}

Matrix Matrix::operator*(Matrix rightMatrix){
    if(columns != rightMatrix.rows){
        throw std::invalid_argument("A.columns Must Be Equal To B.rows.\n");
    }

    Matrix newMatrix(rows, rightMatrix.columns);
    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < rightMatrix.columns; column_index++){
            float value = 0;
            for (int i = 0; i < columns; i++){
                value += matrix[row_index][i] * rightMatrix.matrix[i][column_index];
            }
            newMatrix.matrix[row_index][column_index] = value;
        }
    }
    changeZeros(newMatrix);
    return newMatrix;
}

void Matrix::operator = (float arr[]){
    for (int i = 0; i < columns * rows; i++){
        int column_index = i % columns;
        int row_index = i / columns;
        matrix[row_index][column_index] = arr[i];
    }
}

bool Matrix::operator == (Matrix leftMatrix){
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

void Matrix::inverse_(){
    Matrix inverMatrix = inverse();
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] = inverMatrix.matrix[row_index][column_index];
        }
    }
    inverMatrix.freeMatrix_();
}

void Matrix::populateWithRisingIntegers_(float starting_value){
    for (int row_index = 0; row_index < rows; row_index++){
        for(int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] = starting_value + row_index * columns + column_index;
        }
    }
}

void Matrix::populateWithDiagonalValue_(float value){
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

void Matrix::populateWithValue_(float value){
    for (int row_index = 0; row_index < rows; row_index++){
        for(int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] = value;
        }
    }
}

void Matrix::populateWithRandomNumbers_(float min_value, float max_value, int seed){
    if (min_value > max_value){
    throw std::invalid_argument("min_value can't be larger than max_value\n");
    }
    srand(seed);
    rand();
    for (int row_index = 0; row_index < rows; row_index++){
        for(int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] = (float)min_value + rand() * (max_value - min_value) / RAND_MAX;
        }
    }
}

void Matrix::add_(Matrix A){
    if(A.columns != columns || A.rows != rows){
        throw std::invalid_argument("A.shape must match B.shape\n");
    }

    //newMatrix[row][col] = SUM(A[row][i] * B[i][col])
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] += A.matrix[row_index][column_index];
        }
    }
    changeZeros_();
}

void Matrix::scalar_(float scalar){
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] *= scalar;
        }
    }
    changeZeros_();
}

void Matrix::printMatrix(char space){
    changeZeros_();
    for (int row_index = 0; row_index < rows; row_index++){
        for(int column_index = 0; column_index < columns; column_index++){
            printf("%.2f%c", matrix[row_index][column_index], space);
        }
        printf("\n");
    }
    printf("\n");
}

void Matrix::freeMatrix_(){
        for (int row_index = 0; row_index < rows; row_index++){
        free(matrix[row_index]);
    }
    free(matrix);
}

void Matrix::changeZeros_(){
    //Change -0.00 to 0.00
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            if(distance(matrix[row_index][column_index], 0) < PRECISION){
                matrix[row_index][column_index] = 0;
            }
        }
    }
}

void Matrix::changeNegatives_(float new_value){
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            if(matrix[row_index][column_index] < 0){
                matrix[row_index][column_index] = new_value;
            }
        }
    }
}

Matrix Matrix::transpose(){
    Matrix transposedMatrix = Matrix(columns, rows);
        for (int row_index = 0; row_index < rows; row_index++){
        for(int column_index = 0; column_index < columns; column_index++){
            transposedMatrix.matrix[column_index][row_index] = matrix[row_index][column_index];
        }
    }
    changeZeros(transposedMatrix);
    return transposedMatrix;
}

void Matrix::transpose_(){
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

void Matrix::reshape_(int new_rows, int new_columns){
        if (new_rows * new_columns != rows * columns){
        throw std::invalid_argument("new_rows * new_columns Must Equal rows * columns\n");
        }
        float *temp_matrix = (float *)malloc(sizeof(float) * rows * columns);
        int i = 0;
        //Create Copy Of Current Matrix and free current matrix
        for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            temp_matrix[i] = matrix[row_index][column_index];
            i++;
        }
        free(matrix[row_index]);
        }

        matrix = (float **)realloc(matrix, sizeof(float *) * new_rows);
        i = 0;
        for (int row_index = 0; row_index < new_rows; row_index++){
        matrix[row_index] = (float *)malloc(sizeof(float) * new_columns);
        for (int column_index = 0; column_index < new_columns; column_index++){
            matrix[row_index][column_index] = temp_matrix[i];
            i++;
        }
        }
        free(temp_matrix);
        rows = new_rows;
        columns = new_columns;
}

Matrix Matrix::reshape(int new_rows, int new_columns){
        if (new_rows * new_columns != rows * columns){
        throw std::invalid_argument("new_rows * new_columns Must Equal rows * columns\n");
        }
        float *temp_matrix = (float *)malloc(sizeof(float) * rows * columns);
        int i = 0;
        //Create Copy Of Current Matrix and free current matrix
        for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            temp_matrix[i] = matrix[row_index][column_index];
            i++;
        }
        }
        Matrix reshapedMatrix(new_rows, new_columns);
        i = 0;
        for (int row_index = 0; row_index < new_rows; row_index++){
        matrix[row_index] = (float *)malloc(sizeof(float) * new_columns);
        for (int column_index = 0; column_index < new_columns; column_index++){
            reshapedMatrix.matrix[row_index][column_index] = temp_matrix[i];
            i++;
        }
        }
        free(temp_matrix);
        return reshapedMatrix;
}

Matrix Matrix::copyMatrix(){
    Matrix newMatrix(rows, columns);
    for (int row_index = 0; row_index < rows; row_index++){
        for(int column_index = 0; column_index < columns; column_index++){
            newMatrix.matrix[row_index][column_index] = matrix[row_index][column_index];
        }
    }
    return newMatrix;
}

float Matrix::det(){
    if(columns != rows){
        throw std::invalid_argument("Matrix must be square to calculate determinant.\n");
    }
    float result = det_rec(matrix, rows);
    return result;
}

int Matrix::rank(){
    Matrix reducedMatrix = reducedRowEchelonForm();
    int r = 0;
    for (int row_index = 0; row_index < rows; row_index++){
        bool is_row_of_zeros = true;
        for(int column_index = 0; column_index < columns; column_index++){
            if(distance(reducedMatrix.matrix[row_index][column_index], 0) > PRECISION){
                is_row_of_zeros = false;
            }
        }
        //The rank is the number of non-zero rows
        if(is_row_of_zeros == true){
            return r;
        }
        r++;
    }
    reducedMatrix.freeMatrix_();
    return r;
}

Matrix Matrix::reducedRowEchelonForm(){
    Matrix reducedMatrix = copyMatrix();
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

    changeZeros(reducedMatrix);
    return reducedMatrix;
}

void Matrix::reducedRowEchelonForm_(){
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

Matrix Matrix::inverse(){
    if(columns != rows){
        throw std::invalid_argument("Matrix must be square to have inverse.\n");
    }

    if (distance(det(), 0) < PRECISION){
        throw std::invalid_argument("Singuar matrix does not have an inverse.\n");
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

void Matrix::swap_rows(int row_a, int row_b){
    for (int i = 0; i < columns; i++){
        float temp = matrix[row_a][i];
        matrix[row_a][i] = matrix[row_b][i];
        matrix[row_b][i] = temp;
    }
}

void Matrix::add_rows(int row_a, int row_b, float scalar){
    for (int i = 0; i < columns; i++){
        matrix[row_a][i] += matrix[row_b][i] * scalar;
    }
}

void Matrix::scalar_row(int row, float scalar){
    for (int i = 0; i < columns; i++){
        matrix[row][i] *= scalar;
    }
}

void Matrix::swap_columns(int column_a, int column_b){
    for (int i = 0; i < rows; i++){
        float temp = matrix[i][column_a];
        matrix[i][column_a] = matrix[i][column_b];
        matrix[i][column_b] = temp;
    }
}

void Matrix::add_columns(int column_a, int column_b, float scalar){
    for (int i = 0; i < rows; i++){
        matrix[i][column_a] += matrix[i][column_b] * scalar;
    }
}

void Matrix::scalar_columns(int column, float scalar){
    for (int i = 0; i < rows; i++){
        matrix[i][column] *= scalar;
    }
}

void Matrix::joinRight_(Matrix rightMatrix){
    if (rows != rightMatrix.rows){
        throw std::invalid_argument("Rows must be equal in order to join.\n");
    }
    int new_columns = columns + rightMatrix.columns;
    for (int row_index = 0; row_index < rows; row_index++){
        matrix[row_index] = (float *)realloc(matrix[row_index], sizeof(float) * new_columns);
        for (int column_index = 0; column_index < rightMatrix.columns; column_index++){
            matrix[row_index][column_index + columns] = rightMatrix.matrix[row_index][column_index];
        }
    }
    columns = new_columns;
}

void Matrix::unionBelow(Matrix bottomMatrix){
    if (columns != bottomMatrix.columns){
        throw std::invalid_argument("Columns must be equal in order to union.\n");
        throw;
    }
    int new_rows = rows + bottomMatrix.rows;
    matrix = (float **)realloc(matrix, sizeof(float *) * new_rows);
    for (int row_index = rows; row_index < new_rows; row_index++){
        matrix[row_index] = (float *)malloc(sizeof(float) * columns);
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] = bottomMatrix.matrix[row_index - rows][column_index];
        }
    }
    rows = new_rows;
}

Matrix Matrix::subMatrix(int start_row_index, int end_row_index, int start_column_index, int end_column_index){
    if(start_row_index < 0){
        printf("Invalid Indices! start_row_index (%d) < 0\n", start_row_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(start_column_index < 0 ){
        printf("Invalid Indices! start_column_index (%d) < 0\n", start_column_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(start_row_index > end_row_index){
        printf("Invalid Indices! start_row_index(%d) > end_row_index(%d)\n", start_row_index, end_row_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(start_column_index > end_column_index){
        printf("Invalid Indices! start_column_index(%d) > end_column_index(%d)\n", start_column_index, end_column_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(end_row_index - start_row_index > rows){
        printf("Invalid Indices! end_row_index - start_row_index(%d) > rows(%d)\n", end_row_index - start_row_index, rows);
        throw std::invalid_argument("Invalid Indices!");
    }
    if( end_column_index - start_column_index > columns){
        printf("Invalid Indices! end_column_index- start_column_index(%d) > columns(%d) \n", end_column_index - start_column_index, columns);
        throw std::invalid_argument("Invalid Indices!");
    }
    int subMatrix_rows = end_row_index - start_row_index;
    int subMatrix_columns = end_column_index - start_column_index;
    Matrix subMatrix(subMatrix_rows, subMatrix_columns);
    for (int row_index = 0; row_index < subMatrix_rows; row_index++){
        for (int column_index = 0; column_index < subMatrix_columns; column_index++){
            subMatrix.matrix[row_index][column_index] = matrix[row_index + start_row_index][column_index + start_column_index];
        }
    }
    return subMatrix;
}

void Matrix::subMatrix_(int start_row_index, int end_row_index, int start_column_index, int end_column_index){
    if(start_row_index < 0){
        printf("Invalid Indices! start_row_index (%d) < 0\n", start_row_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(start_column_index < 0 ){
        printf("Invalid Indices! start_column_index (%d) < 0\n", start_column_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(start_row_index > end_row_index){
        printf("Invalid Indices! start_row_index(%d) > end_row_index(%d)\n", start_row_index, end_row_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(start_column_index > end_column_index){
        printf("Invalid Indices! start_column_index(%d) > end_column_index(%d)\n", start_column_index, end_column_index);
        throw std::invalid_argument("Invalid Indices!");
    }
    if(end_row_index - start_row_index > rows){
        printf("Invalid Indices! end_row_index - start_row_index(%d) > rows(%d)\n", end_row_index - start_row_index, rows);
        throw std::invalid_argument("Invalid Indices!");
    }
    if( end_column_index - start_column_index > columns){
        printf("Invalid Indices! end_column_index- start_column_index(%d) > columns(%d) \n", end_column_index - start_column_index, columns);
        throw std::invalid_argument("Invalid Indices!");
    }
    int subMatrix_rows = end_row_index - start_row_index;
    int subMatrix_columns = end_column_index - start_column_index;
    Matrix subMatrix(subMatrix_rows, subMatrix_columns);
    for (int row_index = 0; row_index < subMatrix_rows; row_index++){
        for (int column_index = 0; column_index < subMatrix_columns; column_index++){
            matrix[row_index][column_index] = matrix[row_index + start_row_index][column_index + start_column_index];
        }
    }
    rows = subMatrix_rows;
    columns = subMatrix_columns;
}

Matrix Matrix::pooling(int pooling_rows, int pooling_columns, int stride_rows, int stride_columns){
    Matrix resultMatrix(rows / stride_rows, columns / stride_columns);
    resultMatrix.populateWithValue_(0);
    for (int result_row_index = 0; result_row_index < resultMatrix.rows; result_row_index++){
        for (int result_column_index = 0; result_column_index < resultMatrix.columns; result_column_index++){
            for (int source_row_offset = -1 * pooling_rows / 2; source_row_offset < pooling_rows / 2 + pooling_rows % 2; source_row_offset++){
                int source_row_index = result_row_index * stride_rows + source_row_offset;
                int convolution_row_index = source_row_offset + pooling_rows / 2;
                if(source_row_index >= 0 && source_row_index < rows){
                    for (int source_column_offset = -1 * pooling_columns / 2; source_column_offset < pooling_columns / 2 + pooling_columns % 2; source_column_offset++){
                        int source_column_index = result_column_index * stride_columns + source_column_offset;
                        int convolution_column_index = source_column_offset + pooling_columns / 2;
                        if (source_column_index >= 0 && source_column_index < columns){
                                if (resultMatrix.matrix[result_row_index][result_column_index] < matrix[source_row_index][source_column_index]){
                                resultMatrix.matrix[result_row_index][result_column_index] = matrix[source_row_index][source_column_index];
                                }
                        }
                    }
                }
            }
        }
    }
return resultMatrix;
}

void Matrix::convolution_(Matrix convolutionMatrix, int stride_rows, int stride_columns, bool normalize){
    Matrix tempMatrix = convolution(*this, convolutionMatrix, stride_rows, stride_columns, normalize);
    for (int row_index = 0; row_index < rows; row_index++){
        matrix[row_index] = (float*)realloc(matrix[row_index], sizeof(float) * columns / stride_columns);
    }
    matrix = (float**)realloc(matrix, sizeof(float*) * rows / stride_rows);
    rows /= stride_rows;
    columns /= stride_columns;
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] = tempMatrix.matrix[row_index][column_index];
        }
    }
    tempMatrix.freeMatrix_();
}

void Matrix::pooling_(int pooling_rows, int pooling_columns, int stride_rows, int stride_columns){
    Matrix tempMatrix = pooling(pooling_rows, pooling_columns, stride_rows, stride_columns);
    for (int row_index = 0; row_index < rows; row_index++){
        matrix[row_index] = (float*)realloc(matrix[row_index], sizeof(float) * columns / stride_columns);
    }
    matrix = (float**)realloc(matrix, sizeof(float*) * rows / stride_rows);
    rows /= stride_rows;
    columns /= stride_columns;
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            matrix[row_index][column_index] = tempMatrix.matrix[row_index][column_index];
        }
    }
    tempMatrix.freeMatrix_();
}

Matrix Matrix::unionMatrices(Matrix upperMatrix, Matrix lowerMatrix){
    if(upperMatrix.columns != lowerMatrix.columns){
        throw std::invalid_argument("Columns of matrices must match.\n");
    }
    Matrix unionMatrix(upperMatrix.rows + lowerMatrix.rows, upperMatrix.columns);
    for (int column_index = 0; column_index < upperMatrix.columns; column_index++){
        for (int row_index = 0; row_index  < upperMatrix.rows; row_index ++){
            unionMatrix.matrix[row_index][column_index] = upperMatrix.matrix[row_index][column_index];
        }
        for (int row_index = 0; row_index  < upperMatrix.rows; row_index ++){
            unionMatrix.matrix[upperMatrix.rows + row_index][column_index] = lowerMatrix.matrix[row_index][column_index];
        }
    }
    return unionMatrix;
}

Matrix Matrix::joinMatrices(Matrix leftMatrix, Matrix rightMatrix){
    if(leftMatrix.rows != rightMatrix.rows){
        throw std::invalid_argument("Rows of matrices must match.\n");
    }
    Matrix joinMatrix(leftMatrix.rows, leftMatrix.columns  + rightMatrix.columns);
    for (int row_index = 0; row_index < leftMatrix.rows; row_index++){
        for (int column_index = 0; column_index < leftMatrix.columns; column_index++){
            joinMatrix.matrix[row_index][column_index] = leftMatrix.matrix[row_index][column_index];
        }
        for (int column_index = 0; column_index < rightMatrix.columns; column_index++){
            joinMatrix.matrix[row_index][leftMatrix.columns + column_index] = rightMatrix.matrix[row_index][column_index];
        }
    }
    return joinMatrix;
}

void Matrix::changeZeros(Matrix M){
    //Change -0.00 to 0.00
    for (int row_index = 0; row_index < M.rows; row_index++){
        for (int column_index = 0; column_index < M.columns; column_index++){
            if(distance (M.matrix[row_index][column_index], 0) < PRECISION){
                M.matrix[row_index][column_index] = 0;
            }
        }
    }
}

Matrix Matrix::dot(Matrix A, Matrix B){
    if(A.columns != B.rows){
        throw std::invalid_argument("A.columns Must Be Equal To B.rows.\n");
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

Matrix Matrix::add(Matrix A, Matrix B){
    if(A.columns != B.columns || A.rows != B.rows){
        throw std::invalid_argument("A.shape must match B.shape\n");
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

Matrix Matrix::scalar(Matrix A, float scalar){
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

float Matrix::det_rec(float **matrix, int n){
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

Matrix Matrix::reducedRowEchelonForm(Matrix M){
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

    changeZeros(reducedMatrix);
    return reducedMatrix;
}

Matrix Matrix::convolution (Matrix sourceMatrix, Matrix convolutionMatrix, int stride_rows, int stride_columns, bool normalize){
    if (sourceMatrix.rows < convolutionMatrix.rows || sourceMatrix.columns < convolutionMatrix.columns){
        throw("convolutionMatrix must be smaller or equal in size with sourceMatrix.\n");
    }
    Matrix resultMatrix(sourceMatrix.rows / stride_rows, sourceMatrix.columns / stride_columns);
    resultMatrix.populateWithValue_(0);
    for (int result_row_index = 0; result_row_index < resultMatrix.rows; result_row_index++){
        for (int result_column_index = 0; result_column_index < resultMatrix.columns; result_column_index++){
            //Calculate the bitwise sum and divide by the number of elements.
            int divide = 0; //How much elements did we sum.
            for (int source_row_offset = -1 * convolutionMatrix.rows / 2; source_row_offset < convolutionMatrix.rows / 2 + convolutionMatrix.rows % 2; source_row_offset++){
                int source_row_index = result_row_index * stride_rows + source_row_offset;
                int convolution_row_index = source_row_offset + convolutionMatrix.rows / 2;
                if(source_row_index >= 0 && source_row_index < sourceMatrix.rows){
                    for (int source_column_offset = -1 * convolutionMatrix.columns / 2; source_column_offset < convolutionMatrix.columns / 2 + convolutionMatrix.columns % 2; source_column_offset++){
                        int source_column_index = result_column_index * stride_columns + source_column_offset;
                        int convolution_column_index = source_column_offset + convolutionMatrix.columns / 2;
                        if (source_column_index >= 0 && source_column_index < sourceMatrix.columns){
                            resultMatrix.matrix[result_row_index][result_column_index] += sourceMatrix.matrix[source_row_index][source_column_index] * convolutionMatrix.matrix[convolution_row_index][convolution_column_index];
                            divide++;
                        }
                    }
                }
            }
            if (normalize && divide != 0){
                resultMatrix.matrix[result_row_index][result_column_index] /= divide;
            }
        }
    }
    return resultMatrix;
}

Matrix operator * (float scalar, Matrix M){
    int rows = M.getRows();
    int columns = M.getColumns();
    float** currentMatix = M.getMatrix();
    Matrix newMatrix(rows, columns);
    float** newMatrix_matrix = newMatrix.getMatrix();
    for (int row_index = 0; row_index < rows; row_index++){
        for (int column_index = 0; column_index < columns; column_index++){
            newMatrix_matrix[row_index][column_index] = currentMatix[row_index][column_index] * scalar;
        }
    }
    newMatrix.changeZeros_();
    return newMatrix;
}