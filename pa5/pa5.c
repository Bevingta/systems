// Andrew Bevington / Gleidson De Sousa
// bevingta@bc.edu  / desousag@bc.edu

#define _DEFAULT_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MIN_DIM_POWER 3
#define MAX_DIM_POWER 10
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

void multiply(const int dim, const int * const a, int * const b, int * const c) {
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

int verify(const int dim, const int * const c1, const int * const c2) {
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      if (c1[i * dim + j] != c2[i * dim + j]) {
        return 0;
      }
    }
  }
  return 1;
}

void init(const int dim, int * const m) {
    for (int i = 0; i < dim * dim; ++i) {
        m[i] = rand() % MAX_VALUE;
    }
}

void transpose_and_multiply(const int dim, const int * const a, int * const b, int * const c) {
  transpose(dim, b);
  multiply_transpose(dim, a, b, c);
}

struct timeval run_and_time(
    void (* mult_func)(const int, const int * const, int * const, int * const),
    const int dim,
    const int * const a,
    int * const b,
    int * const c) {

    struct timeval start, end, difference;

    gettimeofday(&start, NULL);

    mult_func(dim, a, b, c);

    gettimeofday(&end, NULL);

    timersub(&end, &start, &difference);

    return difference;
} 

void run_test(const int dim) {
    int * a = (int *)calloc(dim * dim, sizeof(int));
    int * b = (int *)calloc(dim * dim, sizeof(int));
    int * c = (int *)calloc(dim * dim, sizeof(int));
    int * d = (int *)calloc(dim * dim, sizeof(int));

    printf("Testing on %d-by-%d square matrices\n", dim, dim);

    init(dim, a);
    init(dim, b);

    struct timeval mult_time = run_and_time(multiply, dim, a, b, d);
    struct timeval transpose_mult_time = run_and_time(transpose_and_multiply, dim, a, b, c);

    int result_verification = verify(dim, c, d);
    if (result_verification == 1) {
      printf("Result Agree\n");
    } else {
      printf("Results do not agree\n");
    }

    printf("Standard Multiplication: %ld seconds, %d microseconds\n", mult_time.tv_sec, (int)mult_time.tv_usec);
    printf("Multiplication with Transpose: %ld seconds, %d microseconds\n", transpose_mult_time.tv_sec, (int)transpose_mult_time.tv_usec);
    free (a);
    free (b);
    free (c);
    free (d);
}

int main() {
  
  for (int power = MIN_DIM_POWER; power <= MAX_DIM_POWER; power++) {
    run_test(1 << power);
    printf("\n");
  }


  return EXIT_SUCCESS;
}
