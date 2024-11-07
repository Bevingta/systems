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
    int *c = (int *)calloc(DIM * DIM, sizeof(int));
    
    for (int i = 0; i < DIM * DIM; ++i) {
        a[i] = rand() % MAX_VALUE;
	b[i] = rand() % MAX_VALUE;
    }
    
    printf("A: \n");
    print(DIM, a);
 
    printf("B: \n");
    print(DIM, b);
    
    multiply(DIM, a, b, c);

    printf("MATRIX C:\n");
    print(DIM, c);

    free(a);
    free(b);
    free(c);

    return 0;

}
