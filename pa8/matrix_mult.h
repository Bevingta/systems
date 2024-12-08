#define DIM 4
#define NUM_WORKERS 4
#define SUCCESS 0
#define FAILURE -1

typedef struct alias {
  const double * const a;
  const double * const b;
  double * const c;
  const int dim;
  const int num_workersr;
} multiply_function;


