#include <sys/types.h>

#define DIM 1024 
#define NUM_WORKERS 4
#define SUCCESS 0
#define FAILURE -1

typedef void (*multiply_function)(const double * const, const double * const, double * const, const int, const int);

void init_matrix(double * matrix, int dim);
void multiply_chunk(const double * const a, const double * const b, double * const c, const int row_start, const int chunk_size);
void multiply_parallel_threads(const double * const a, const double * const b, double * const c, const int dim, const int num_workers);
void multiply_parallel_processes(const double * const a, const double * const b, double * const c, const int dim, const int num_workers);
void multiply_serial(const double * const a, const double * const b, double * const c, const int dim, const int num_workers);
void* multiply_chunk_thread(void* arg);
void munmap_checked(void *c, const int dim);
pid_t fork_checked();
double* multiply_matrices(const double * const a, const double * const b, const int dim, const int num_workers, multiply_function func);
int verify(const double * const m1, const double * const m2, const int dim);
void print_elapsed_time(struct timeval *start, struct timeval *end, const char * const name);
void print_verification(const double * const m1, const double * const m2, const int dim, const char * const name);
void run_and_time(multiply_function multiply_matrices, const double * const a, const double * const b, double * const c, const double * const gold, const int dim, const char * const name, const int num_workers, const bool verify_result);
struct timeval time_diff(struct timeval *start, struct timeval *end);


typedef struct {
    const double* a;
    const double* b;
    double* c;
    int row_start;
    int chunk_size;
} ThreadArgs;
