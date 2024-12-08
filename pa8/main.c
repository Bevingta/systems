#include <sys/mman.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "matrix_mult.h"

typedef struct RunArgs {
    multiply_function func;
    double * product;
    const int num_workers;
    const char * const name;
    const bool verify;
} RunArgs;

void print_matrix(const double * const matrix, int dim) {
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

void* multiply_chunk_thread(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    for (int i = args->row_start; i < (args->row_start + args->chunk_size); i++) {
        for (int j = 0; j < DIM; j++) {
            for (int k = 0; k < DIM; k++) {
                args->c[i * DIM + j] += args->a[i * DIM + k] * args->b[k * DIM + j];
            }
        }
    }
    
    return NULL;
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

void multiply_parallel_threads(const double* const a, const double* const b, double* const c, 
                             const int dim, const int num_workers) {
    pthread_t* threads = malloc((num_workers - 1) * sizeof(pthread_t));
    ThreadArgs* thread_args = malloc(num_workers * sizeof(ThreadArgs));
    
    int chunk_size = dim / num_workers;
    int num_threads = num_workers - 1;
    int i = 0;
    
    // Create threads for all but the last chunk
    for (; i < num_threads; i++) {
        thread_args[i].a = a;
        thread_args[i].b = b;
        thread_args[i].c = c;
        thread_args[i].row_start = i * chunk_size;
        thread_args[i].chunk_size = chunk_size;
        
        pthread_create(&threads[i], NULL, multiply_chunk_thread, &thread_args[i]);
    }
    
    // Main thread handles the last chunk
    thread_args[i].a = a;
    thread_args[i].b = b;
    thread_args[i].c = c;
    thread_args[i].row_start = i * chunk_size;
    thread_args[i].chunk_size = dim - i * chunk_size;
    multiply_chunk_thread(&thread_args[i]);
    
    // Wait for all threads to complete
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    free(threads);
    free(thread_args);
}

void multiply_parallel_processes(const double * const a, const double * const b, double * const c, const int dim, const int num_workers) {

    double * shared_c = mmap_checked(dim);

    int chunk_size = dim / num_workers;
    int num_procs = num_workers - 1;

    int i = 0;
    for (; i < num_procs; i++) {
        pid_t pid = fork_checked();
        if (!pid) {
            multiply_chunk(a, b, shared_c, i * chunk_size, chunk_size);
            exit(EXIT_SUCCESS);
        }
    }
    multiply_chunk(a, b, shared_c, i * chunk_size, dim - (i * chunk_size));
    while (wait(NULL) > 0);
    
    for (int i = 0; i < dim * dim; i++) {
        c[i] = shared_c[i];
    }

    munmap_checked(shared_c, dim);
}

void multiply_serial(const double * const a, const double * const b, double * const c, const int dim, const int num_workers)
{
    multiply_chunk(a, b, c, 0, dim);
}

void init_matrix(double * matrix, int dim) {
  for (int i = 0; i < dim; i++) {
    for (int j = 1; j <= dim; j++) {
      matrix[i * dim + j - 1] = i * dim + j;
    }
  }
  int matrix_length = dim * dim;
}

struct timeval time_diff(struct timeval *start, struct timeval *end) {
    struct timeval diff;
    
    // Calculate the difference in seconds and microseconds
    diff.tv_sec = end->tv_sec - start->tv_sec;
    diff.tv_usec = end->tv_usec - start->tv_usec;
    
    // Handle case where we need to borrow from seconds
    if (diff.tv_usec < 0) {
        diff.tv_sec--;  // Borrow one second
        diff.tv_usec += 1000000;  // Add 1 million microseconds
    }
    
    return diff;
}

void print_elapsed_time(struct timeval *start, struct timeval *end, const char * const name) {
    struct timeval diff = time_diff(start, end);
    
    printf("The %s algorithm took ", name);
    
    // Handle seconds
    if (diff.tv_sec > 0) {
        printf("%ld second%s", diff.tv_sec, diff.tv_sec == 1 ? "" : "s");
        if (diff.tv_usec > 0) {
            printf(" and ");
        }
    }
    
    // Handle microseconds
    if (diff.tv_usec > 0 || diff.tv_sec == 0) {
        printf("%ld microsecond%s", (long)diff.tv_usec, diff.tv_usec == 1 ? "" : "s");
    }
    
    printf("\n");
}

void print_verification(const double * const m1, const double * const m2, const int dim, const char * const name) {
    if (verify(m1, m2, dim) == SUCCESS) {
        printf("The %s algorithm produced the correct result\n", name);
    } else {
        printf("The %s algorithm produced an incorrect result\n", name);
    }
}

void run_and_time(
    multiply_function multiply_matrices,
    const double * const a,
    const double * const b,
    double * const c,
    const double * const gold,
    const int dim,
    const char * const name,
    const int num_workers,
    const bool verify_result
) {
    struct timeval start, end;
    
    printf("\nRunning %s multiplication algorithm...\n", name);
    
    // Get start time
    gettimeofday(&start, NULL);
    
    // Run multiplication
    multiply_matrices(a, b, c, dim, num_workers);
    
    // Get end time
    gettimeofday(&end, NULL);
    
    // Print timing results
    print_elapsed_time(&start, &end, name);
   
    // Verify result if requested
    if (verify_result) {
        print_verification(c, gold, dim, name);
    }
}

int main() {
    int size = DIM * DIM;
    double * matrix_a = calloc(size, sizeof(double));
    double * matrix_b = calloc(size, sizeof(double));
    init_matrix(matrix_a, DIM);
    init_matrix(matrix_b, DIM);
    RunArgs args[] = {
        {multiply_serial, NULL, 1, "serial", false},
        {multiply_parallel_processes, NULL, NUM_WORKERS, "parallel processes", true},
        {multiply_parallel_threads, NULL, NUM_WORKERS, "parallel threads", true}
    };
    const int num_functions = sizeof(args) / sizeof(args[0]);
    for (int i = 0; i < num_functions; ++i) {
       args[i].product = calloc(size, sizeof(double));
    }
    for (int i = 0; i < num_functions; ++i) {
        run_and_time(
                args[i].func,
                matrix_a,
                matrix_b,
                args[i].product,
                args[0].product,
                DIM,
                args[i].name,
                args[i].num_workers,
                args[i].verify
                );
    }
    for (int i = 0; i < num_functions; ++i) {
        free(args[i].product);
    }
    return EXIT_SUCCESS;
}

