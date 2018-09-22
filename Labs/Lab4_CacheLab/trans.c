/*
 *
 *
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, l;
	int b;
	int temp1, temp2, temp3, temp4, temp5, temp6;
	int T1;
	if (M == 64)
	{
		b = 8;
		for (i = 0; i < N; i += b)
		{
			for (j = 0; j < M; j += b)
			{
				for (k = 0; k < 4; k++)
				{
					for (l = 0; l < 4; l++)
					{
						if (i + k != j + l)
						{
							B[j + l][i + k] = A[i + k][j + l];
							B[j + l][i + k + 4] = A[i + k][j + (l + 1) % 4 + 4];
						}
						else
						{
							T1 = l;
							temp1 = A[i + k][j + l];
							temp2 = A[i + k][j + (l + 1) % 4 + 4];
						}
					}
					if (i == j)
					{
						B[j + T1][i + k] = temp1;
						B[j + T1][i + k + 4] = temp2;
					}
				}
				for (k = 0; k < 4; k++)
				{
					temp1 = A[i + k + 4][j + 4];
					temp2 = A[i + k + 4][j + 3];
					B[j + 4][i + k] = B[j + 3][i + k + 4];
					B[j + 4][i + k + 4] = temp1;
					B[j + 3][i + k + 4] = temp2;
				}
				for (k = 0; k < 3; k++)
				{
					if (i == j)
					{
						temp3 = A[i + k + 5][j + k];
						temp4 = A[i + k + 5][j + k + 5];
						temp5 = A[i + k + 4][j + k];
						temp6 = A[i + k + 4][j + k + 5];
					}
					for (l = 0; l < 4; l++)
					{
						if (l == k && i == j)
						{
							temp1 = temp5;
							temp2 = temp6;
						}
						else if (k + 1 == l && i == j)
						{
							temp1 = temp3;
							temp2 = temp4;
						}
						else
						{
							temp1 = A[i + l + 4][j + k];
							temp2 = A[i + l + 4][j + k + 5];
						}
						B[j + k + 5][i + l] = B[j + k][i + l + 4];
						B[j + k + 5][i + l + 4] = temp2;
						B[j + k][i + l + 4] = temp1;
					}
				}
			}
		}
	}
	else
	{
		if (M == 32)
			b = 8;
		else
			b = 23;
		for (i = 0; i < N; i += b)
		{
			for (j = 0; j < M; j += b)
			{
				for (k = i; k < i + b && k < N; k++)
				{
					for (l = j; l < j + b && l < M; l++)
					{
						if (k != l)
						{
							B[l][k] = A[k][l];
						}
						else
						{
							temp1 = A[k][l];
							T1 = l;
						}
					}
					if (i == j)
					{
						B[T1][T1] = temp1;
					}
				}
			}
		}
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

