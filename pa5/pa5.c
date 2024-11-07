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

  print(dim, a);
  print(dim, b_t);

  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      c[i * dim + j] = 0;
      for (int k = 0; k < dim; ++k) {
        c[i * dim + j] += a[i * dim + k] * b_t[j * dim + k];  // Changed this line
      }
    }
  }  
}

int verify(const int dim, const int * const c1, const int * const c2) {
  //verify the two solution matrices are the same
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      if (c1[i * dim + j] != c2[i * dim + j]) {
        return 0;
      }
    }
  }
  return 1;
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
 
    printf("B: \n");
    print(DIM, b);
    printf("Transposed: \n");
    transpose(DIM, b);

    multiply_transpose(DIM, a, b, c);

    int result_verification = verify(DIM, c, d);
    if (result_verification == 1) {
      printf("The two matrices are the same\n");
    } else {
      printf("The two matrices are not the same\n");
    }

    printf("C: \n");
    print(DIM, c);

    printf("D: \n");
    print(DIM, d);
}
