/**
 * @file MatrixMath.c
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
 * 
 * 
 */

#include <MatrixMath.h>
#include <Board.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define MAT_TEST

void MatrixPrint(double mat[3][3])
{
	// printf("Output of MatrixPrint():\n");

	for (int a = 0; a < 3; a += 1)
	{
		printf("%f | %f | %f\n", mat[a][0], mat[a][1], mat[a][2]);
	}
}

void MatrixCopy(double mat1[3][3], double mat2[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat2[i][j] = mat1[i][j];
        }
    }
}


int IsValidMatrix(double mat[3][3])
{
	// Check if each row has 3 elements
	return 1;
}

int MatrixEquals(double mat1[3][3], double mat2[3][3])
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			if (mat1[a][b] != mat2[a][b])
			{
				return 0;
			}
		}
	}

	return 1;
}

void MatrixAdd(double mat1[3][3], double mat2[3][3], double result[3][3])
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			result[a][b] = mat1[a][b] + mat2[a][b];
		}
	}
}

void MatrixSub(double mat1[3][3], double mat2[3][3], double result[3][3])
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			result[a][b] = mat1[a][b] - mat2[a][b];
		}
	}
}

void MatrixMultiply(double mat1[3][3], double mat2[3][3], double result[3][3])
{
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			result[a][b] = 0; // Initialize result matrix element to 0
			for (int k = 0; k < 3; k++)
			{
				result[a][b] += mat1[a][k] * mat2[k][b];
			}
		}
	}
}

void MatrixScalarAdd(double x, double mat[3][3], double result[3][3])
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			result[a][b] = mat[a][b] + x;
		}
	}
}

void MatrixScalarMultiply(double x, double mat[3][3], double result[3][3])
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			result[a][b] = mat[a][b] * x;
		}
	}
}

double MatrixTrace(double mat[3][3])
{
	return mat[0][0] + mat[1][1] + mat[2][2];
}

void MatrixTranspose(double mat[3][3], double result[3][3])
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			result[b][a] = mat[a][b];
		}
	}
}

void MatrixSubmatrix(int i, int j, double mat[3][3], double result[2][2])
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			// skip the row and column that we don't want to include
			if (a == i || b == j)
			{
				continue;
			}

			// calculate the location for the result
			int aa, bb;

			if (a > i)
			{
				aa = a - 1;
			}
			else
			{
				aa = a;
			}

			if (b > j)
			{
				bb = b - 1;
			}
			else
			{
				bb = b;
			}

			result[aa][bb] = mat[a][b];
		}
	}
}

double MatrixDeterminant(double mat[3][3])
{
	// set each position value as a constant to plug into
	double a = mat[0][0];
	double b = mat[0][1];
	double c = mat[0][2];
	double d = mat[1][0];
	double e = mat[1][1];
	double f = mat[1][2];
	double g = mat[2][0];
	double h = mat[2][1];
	double i = mat[2][2];

	// just followed a formula idk
	return (a * (e * i - f * h)) - (b * (d * i - f * g)) + c * (d * h - e * g);
}

int MatrixInverse(double mat[3][3], double result[3][3])
{
	// Calculate determinant using MatrixDeterminant function
	double det = MatrixDeterminant(mat);
	// Check if determinant is nonzero (matrix is invertible)
	if (MatrixDeterminant(mat) == 0)
	{
		return FALSE;
	}

	// Calculate the inverse matrix using adjugate matrix
	result[0][0] = (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) / det;
	result[0][1] = (mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2]) / det;
	result[0][2] = (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) / det;
	result[1][0] = (mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2]) / det;
	result[1][1] = (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) / det;
	result[1][2] = (mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2]) / det;
	result[2][0] = (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) / det;
	result[2][1] = (mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1]) / det;
	result[2][2] = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) / det;
	return TRUE;
}

void MatrixExponetial(double (*mat)[DIM]) 
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			mat[a][b] = exp(mat[a][b]);
		}
	}
}

void MatrixSin(double (*mat)[DIM]) 
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			mat[a][b] = sin(mat[a][b]);
		}
	}
}

void MatrixCosine(double (*mat)[DIM]) 
{
	for (int a = 0; a <= 2; a += 1)
	{
		for (int b = 0; b <= 2; b += 1)
		{
			mat[a][b] = cos(mat[a][b]);
		}
	}
}

// Function to extract Euler angles from Direction Cosine Matrix (DCM)
EulerAngles ExtractEuler(double (*dcm)[DIM]) {
    EulerAngles angles;
    // Calculate pitch (θ)
	if (dcm[0][2] >= 1) {
        dcm[0][2] = 1;
    } else if (dcm[0][2] <= -1) {
        dcm[0][2] = -1;
    }
    angles.pitch = asin(-dcm[0][2]);
    // Calculate yaw (ψ)
    angles.yaw = atan2(dcm[0][1], dcm[0][0]);
    // Calculate roll (φ)
    angles.roll = atan2(dcm[1][2], dcm[2][2]);
    return angles;
}

// #define MAT_TEST
#ifdef MAT_TEST
int main(void)
{
	BOARD_Init();
	// Test the functions
	double mat1[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	double mat2[3][3] = {{9.0, 8, 7}, {6, 5, 4}, {3, 2, 1}};
	double result_add[3][3], result_multiply[3][3], result_inverse[3][3];

	if (!IsValidMatrix(mat1) || !IsValidMatrix(mat2))
	{
		printf("Invalid matrices.\n");
		return 1;
	}

	// Add matrices
	MatrixAdd(mat1, mat2, result_add);
	printf("Addition:\n");
	MatrixPrint(result_add);

	// Sub matrices
	MatrixSub(mat2, mat1, mat2);
	printf("Subtaction:\n");
	MatrixPrint(mat2);

	
	// Multiply matrices
	MatrixMultiply(mat1, mat2, mat2);
	printf("Multiplication:\n");
	MatrixPrint(result_multiply);

	// Calculate inverse of mat1
	printf("Inverse:\n");
	if (MatrixInverse(mat2, result_inverse)) {
		MatrixPrint(result_inverse);
	} else {
		printf("Matrix is not invertible\r\n");
	}

	// Scalar Matrix (result is we CAN put the same matrix as result here)
	MatrixScalarMultiply(3, mat2, mat2);
	printf("Scalar Multiplication:\n");
	MatrixPrint(mat2);
	// Matrix Exponential e^x
	MatrixExponetial(mat1);
	printf("Matrix Exponential\n");
	MatrixPrint(mat1);
	
	
	// Return at end
	return 0;
}
#endif