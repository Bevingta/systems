#include <stdio.h>
#include <stdlib.h>

#include "matrix_mult.h"

void print_matrix(double * matrix, int dim) {
  printf("[ ");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%f ", matrix[i * dim + j]);
    }
    printf("\n");
  }
  printf("]\n");
}

void multiply_serial(const double * const a, const double * const b, double * const c, const int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      for (int k = 0; k < dim; k++) {
        c[i * dim + j] += a[i * dim + k] * b[k * dim + j];
      }
    }
  }
}

void init_matrix(double * matrix, int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 1; j <= dim; j++) {
      matrix[i * dim + j - 1] = i * dim + j;
    }
  }
  int matrix_length = dim * dim;
  for (int i = 0; i < matrix_length; i++) {
    printf("%f ", matrix[i]);
  }
  printf("\n");
}

int main() {
  double a[DIM * DIM];
  double b[DIM * DIM];
  double c[DIM * DIM];

  for (int i = 0; i < DIM * DIM; i++) {
    c[i] = 0;
  }

  init_matrix(a, DIM);
  init_matrix(b, DIM);
  multiply_serial(a, b, c, DIM);
  print_matrix(c, DIM);
  return 0;
}
