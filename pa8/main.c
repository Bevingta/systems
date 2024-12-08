#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

int verify(const double * const m1, const double * const m2, const int dim) {
  for (int i = 0; i <  dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (m1[i * dim + j] != m2[i * dim + j]) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}

void * mmap_checked(const int dim) {
  void *c = mmap(NULL, dim * dim * sizeof(double), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (c == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }
  return c;
}

void munmap_checked(void *c, const int dim) {
  if (munmap(c, dim * dim * sizeof(double)) == -1) {
    perror("munmap");
    exit(EXIT_FAILURE);
  }
}

pid_t fork_checked() {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  return pid;
}

void multiply_chunk(const double * const a, const double * const b, double * const c, const int row_start, const int chunk) {
  for (int i = row_start; i < (row_start + chunk); i++) {
    for (int j = 0; j < DIM; j++) {
      for (int k = 0; k < DIM; k++) {
        c[i * DIM + j] += a[i * DIM + k] * b[k * DIM + j];
      }
    }
  }
}

void multiply_parallel_threads(const double * const a, const double * const b, double * const c, const int dim, const int num_workers) {
  num_threads = num_workers - 1;

}

void multiply_parallel_processes(const double * const a, const double * const b, double * const c, const int dim, const int num_workers) {

    int chunk_size = dim / num_workers;
    int num_procs = num_workers - 1;

    int i = 0;
    for (; i < num_procs; i++) {
        pid_t pid = fork_checked();
                if (!pid) {
            //debugging print
            printf("Worker %d starting at row %d to row %d\n", i, i * chunk_size, chunk_size + i * chunk_size);

            multiply_chunk(a, b, c, i * chunk_size, chunk_size);
            exit(EXIT_SUCCESS);
        }
    }
    multiply_chunk(a, b, c, i * chunk_size, dim - i * chunk_size);
    while (wait(NULL) > 0);
    printf("Computation complete.\n");
}

void multiply_serial(const double * const a, const double * const b, double * const c, const int dim) {
  multiply_chunk(a, b, c, 0, dim);
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

  void *c = mmap_checked(DIM); 

  double c2[DIM * DIM];
  for (int i = 0; i < DIM * DIM; i++) {
    c2[i] = 0;
  }

  init_matrix(a, DIM);
  init_matrix(b, DIM);

  multiply_serial(a, b, c2, DIM);
  multiply_parallel_processes(a, b, c, DIM, NUM_WORKERS);

  if (verify(c, c2, DIM) == SUCCESS) {
    printf("Matrices are equal.\n");
    return EXIT_SUCCESS;
  print_matrix(c2, DIM);  } else {
    printf("Matrices are not equal.\n");
    printf("Matrix C:\n");
    print_matrix(c, DIM);
    munmap_checked(c, DIM);
    printf("Matrix C2:\n");
    return EXIT_FAILURE;
  }
}
