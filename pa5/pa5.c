#include <stdio.h>
#include <stdlib.h>

#define DIM 4
#define MAX_VALUE 20

void transpose(const int dim, int * const m) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < i; ++j) {
	        int temp = m[i * dim + j];
	        m[i * dim + j] = m[j * dim + i];
	        m[j * dim + i] = temp;
	    }  
    }
}

void multiply(const int dim, const int * const a, const int * const b, int * const c) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
	        c[i * dim + j] = 0;
	        for (int k = 0; k < dim; ++k) {
	            c[i * dim + j] += a[i * dim + k] * b[k * dim + j];
	        }
	    }
    }
}

void multiply_transpose(const int dim, const int * const a, const int * const b_t, int * const c) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
                c[i * dim + j] = 0;
            for (int k = 0; k < dim; ++k) {
                c[i * dim + j] += a[i * dim + k] * b_t[j * dim + k];
            }
        }
    }
}

void print(const int dim, const int * const m) {
    for (int i = 0; i < dim; ++i) {
    	for (int j = 0; j < dim; ++j) {
	    printf("%4d  ", m[i * dim + j]);
	}
	printf("\n");
    }
    printf("\n");
}

int main(int argc, char ** argv) {
    int *a = (int *)calloc(DIM * DIM, sizeof(int));
    int *b = (int *)calloc(DIM * DIM, sizeof(int));
    int *c1 = (int *)calloc(DIM * DIM, sizeof(int));
    int *c2 = (int *)calloc(DIM * DIM, sizeof(int));

    for (int i = 0; i < DIM * DIM; ++i) {
        a[i] = rand() % MAX_VALUE;
	    b[i] = rand() % MAX_VALUE;
    }
    
    printf("A: \n");
    print(DIM, a);
 
    printf("B: \n");
    print(DIM, b);
    
    multiply(DIM, a, b, c1);
    printf("C:\n");
    print(DIM, c1);

    transpose(DIM, b);

    printf("B_T:\n");
    print(DIM, b);

    multiply_transpose(DIM, a, b, c2);
    printf("C Transposed:\n");
    print(DIM, c2);

    free(a);
    free(b);
    free(c1);
    free(c2);

    return 0;

}
