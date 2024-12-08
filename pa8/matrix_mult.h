#define DIM 1024 
#define NUM_WORKERS 4
#define SUCCESS 0
#define FAILURE -1

typedef void (*multiply_function)(const double * const, const double * const, double * const, const int, const int);

typedef struct {
    const double* a;
    const double* b;
    double* c;
    int row_start;
    int chunk_size;
} ThreadArgs;
