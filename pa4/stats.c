#include <stdio.h>
#include <stdlib.h>

double mean_squared_error(const int * values, const int num, double mean) {
    double sum_of_squared_errors = 0.0;
    const int * end = values + num;
    for ( ; values < end; ++values) {
        double error = *values - mean;
        sum_of_squared_errors += error * error;
    }
    return sum_of_squared_errors / num;
}


long sum(const int * values, const int num, double * const mean) {
    long result = 0;
    const int * end = values + num;
    for ( ; values < end; ++values) {
        result += *values;
    }
    *mean = (double)result / num;
    return result;
}

int main(int argc, char ** argv) {
    int num;
    puts("How many integer values will you enter?");
    printf("> ");
    scanf("%d", &num);
    int * values = calloc(num, sizeof(*values));
    printf("Please enter %d integers.\n", num);
    for (int i = 0; i < num; ++i) {
        printf("> ");
        scanf("%d", values + i);
    }
    double mean;
    long total = sum(values, num, &mean);
    double mse = mean_squared_error(values, num, mean);
    printf("Sum: %ld\n", total);
    printf("Mean: %f\n", mean);
    printf("Mean squared error: %f\n", mse);
    return EXIT_SUCCESS;
}
