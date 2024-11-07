// Andrew Bevington / Gleidson De Sousa
// bevingta@bc.edu  / desousag@bc.edu

#include <stdio.h>
#include <stdlib.h>

#define DIM 3
#define MAX_VALUE 20

void print(const int dim, const int * const m) {
    for (int i = 0; i < dim; ++i) {
    	for (int j = 0; j < dim; ++j) {
	    printf("%4d  ", m[i * dim + j]);
	}
	printf("\n");
    }
    printf("\n");
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

void transpose(const int dim, int * const m) {
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < i; j++) {
      int temp = m[i * dim + j];
      m[i * dim + j] = m[j * dim + i];
      m[j * dim + i] = temp;
    }
  }
  print(dim, m);
}

void multiply_transpose(const int dim, const int * const a, const int * const b_t, int * const c) {
  // going to multiply a[0] by b_t[0], a[1] by b_t[1], etc.
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      c[i * dim + j] = 0;
      for (int k = 0; k < dim; ++k) {
        c[i * dim + j] += a[i * dim + k] * b_t[i * dim + k];
      }
    }
  }  
}

int main(int argc, char ** argv) {
    int * a = (int *)calloc(DIM * DIM, sizeof(int));
    int * b = (int *)calloc(DIM * DIM, sizeof(int));
    int * c = (int *)calloc(DIM * DIM, sizeof(int));
    //remove in submission
    int * d = (int *)calloc(DIM * DIM, sizeof(int));

    for (int i = 0; i < DIM * DIM; ++i) {
        a[i] = rand() % MAX_VALUE;
        b[i] = rand() % MAX_VALUE;
    }

    multiply(DIM, a, b, d);
    
    printf("A: \n");
    print(DIM, a);
    printf("Transposed: \n");
    transpose(DIM, a);
 
    printf("B: \n");
    print(DIM, b);
    printf("Transposed: \n");
    transpose(DIM, b);
    multiply_transpose(DIM, a, b, c);

    printf("C: \n");
    print(DIM, c);

    printf("D: \n");
    print(DIM, d);
}
