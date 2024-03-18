#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
/**
 * @file
 *
 * @section DESCRIPTION
 *
 * This file implements a basic 3x3 matrix math library. Basic matrix operations are provided along
 * with the matrix inverse function (though that function cannot handle singular matrices).
 *
 * Matrices are defined in row-major order, so that the matrix:
 *   0 1 2
 *   3 4 5
 *   6 7 8
 * is represented by the array `double mat[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};`.
 */

/**
 * FP_DELTA defines the tolerance for testing equality for floating-point numbers. 
 * Used within MatrixEquals() 
 * Also used to compare scalar return values, such as the result of MatrixTrace().
 */
#define FP_DELTA 0.0001

/**
 * To avoid using magic numbers, use this macro to iterate over 3 dimensions:
 *  */
#define DIM 3

typedef struct {
    double roll;  // φ
    double pitch; // θ
    double yaw;   // ψ
} EulerAngles;


/******************************************************************************
 * Matrix Display:
 *****************************************************************************/
/**
 * MatrixPrint displays a 3x3 array to standard output with clean, readable, 
 * consistent formatting.  
 * @param: mat, pointer to a 3x3 double array
 * @return: none
 * The printed matrix should be aligned in a grid when called with positive or
 *  negative numbers.  It should be able to display at least FP_DELTA precision, and
 *  should handle numbers as large as 999.0 or -999.0
 */
void MatrixPrint(double mat[3][3]);


/******************************************************************************
 * Matrix - Matrix Operations
 *****************************************************************************/

/**
 * MatrixCopy copies mat1 into mat2
 * @param: mat1, pointer to a 3x3 double array
 * @param: mat2, pointer to a 3x3 double array
 * @return: n/a
 * mat2 is modified by this function.
 */
void MatrixCopy(double mat1[3][3], double mat2[3][3]);

/**
 * MatrixEquals checks if the two matrix arguments are equal (to within FP_DELTA).
 * @param: mat1, pointer to a 3x3 double array
 * @param: mat2, pointer to a 3x3 double array
 * @return: TRUE if and only if every element of mat1 is within FP_DELTA of the corresponding element of mat2,  otherwise return FALSE
 * Neither mat1 nor mat2 is modified by this function.
 */
int MatrixEquals(double mat1[3][3], double mat2[3][3]);

/**
 * MatrixAdd performs an element-wise matrix addition operation on two 3x3 matrices and 
 * "returns" the result by modifying the third argument.
 * @param: mat1, pointer to a summand 3x3 matrix
 * @param: mat2, pointer to a summand 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the sum of mat1 and mat2.
 * @return:  None
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixAdd(double mat1[3][3], double mat2[3][3], double result[3][3]);

/**
 * MatrixSub performs an element-wise matrix subtraction operation on two 3x3 matrices and 
 * "returns" the result by modifying the third argument.
 * @param: mat1, pointer to a first 3x3 matrix
 * @param: mat2, pointer to a second 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the result of mat1 - mat2.
 * @return:  None
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixSub(double mat1[3][3], double mat2[3][3], double result[3][3]);

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and "returns" the result by modifying the third argument.
 * @param: mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix product of mat1 and mat2.
 * @return: none
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixMultiply(double mat1[3][3], double mat2[3][3], double result[3][3]);


/******************************************************************************
 * Matrix - Scalar Operations
 *****************************************************************************/

/**
 * MatrixScalarAdd performs the addition of a matrix and a scalar.  Each element of the matrix is increased by x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar double
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarAdd(double x, double mat[3][3], double result[3][3]);

/**
 * MatrixScalarMultiply performs the multiplication of a matrix and a scalar.
 * Each element of the matrix is multiplied x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar double
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat * x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarMultiply(double x, double mat[3][3], double result[3][3]);


/******************************************************************************
 * Unary Matrix Operations
 *****************************************************************************/

/**
 * MatrixTrace calculates the trace of a 3x3 matrix.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the trace of mat
 */
double MatrixTrace(double mat[3][3]);

/**
 * MatrixTranspose calculates the transpose of a matrix and "returns" the
 * result through the second argument.
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to transpose of mat
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixTranspose(double mat[3][3], double result[3][3]);

/**
 * MatrixSubmatrix finds a submatrix of a 3x3 matrix that is 
 * formed by removing the i-th row and the j-th column.  The 
 * submatrix is "returned" by modifying the final argument.
 * 
 * @param: i, a row of the matrix, INDEXING FROM 0
 * @param: j, a column of the matrix, INDEXING FROM 0
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 2x2 matrix
 * @return: none
 * 
 * mat is not modified by this function.  Result is modified by this function.
 */
void MatrixSubmatrix(int i, int j, double mat[3][3], double result[2][2]);

/**
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a double.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the determinant of mat
 * mat is not modified by this function.
 * */
double MatrixDeterminant(double mat[3][3]);


/* MatrixInverse calculates the inverse of a matrix and
 * "returns" the result by modifying the second argument.
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 3x3 matrix that is modified to contain the inverse of mat
 * @return: return true or false if matrix is invertible based on determinant == 0 -> not invertable 
 * mat is not modified by this function.  result is modified by this function.
 */
int MatrixInverse(double mat[3][3], double result[3][3]);

/* MatrixExponential changes each element in a 3x3 matrix to e^x where x is the prior value of that element
 * @param: mat, a pointer to a 3x3 matrix
 * mat is modified by this function.
 */
void MatrixExponetial(double (*mat)[DIM]);

/* MatrixSin changes each element in a 3x3 matrix to sin(x) where x is the prior value of that element
 * @param: mat, a pointer to a 3x3 matrix
 * mat is modified by this function.
 */
void MatrixSin(double (*mat)[DIM]);

/* MatrixCosine changes each element in a 3x3 matrix to cosin(x) where x is the prior value of that element
 * @param: mat, a pointer to a 3x3 matrix
 * mat is modified by this function.
 */
void MatrixCosine(double (*mat)[DIM]);

/* ExtractEuler calculates euler angles and
 * "returns" the angles.
 * @param: dcm, a pointer to a 3x3 DCM rotational matrix
 * @return: len() = 3 array of Euler Angles
 * dcm is not modified by this function.
 */
EulerAngles ExtractEuler(double (*dcm)[DIM]);

#endif // MATRIX_MATH_H
