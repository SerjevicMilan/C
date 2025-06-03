#include "ex2.h"
#include <omp.h>

double dotp_naive(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    for (int i = 0; i < arr_size; i++)
        global_sum += x[i] * y[i];
    return global_sum;
}

// Critical Keyword
double dotp_critical(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    #pragma omp parallel for
    for (int i = 0; i < arr_size; i++)
    {
        #pragma omp critical
        global_sum += x[i] * y[i];
    }
    // Use the critical keyword here!
    return global_sum;
}

// Reduction Keyword
double dotp_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    #pragma omp parallel for reduction(+:global_sum)
    for (int i = 0; i < arr_size; i++)
    {
        global_sum += x[i] * y[i];
    }
    return global_sum;
}

// Manual Reduction
double dotp_manual_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    int num_threads = omp_get_max_threads();
    double thread_sums[num_threads];

     for (int i = 0; i < num_threads; i++) {
        thread_sums[i] = 0.0;
    }
    // Do NOT use the `reduction` directive here!
    #pragma omp parallel
    {
        // TODO: Parallel Section
        int current_thread = omp_get_thread_num();
         double local_sum = 0.0;
        #pragma omp for
        for (int i = 0; i < arr_size; i++)
        {
            local_sum += x[i] * y[i];
        }
        thread_sums[current_thread] = local_sum;
    }

    for (int i = 0; i < num_threads; i++)
    {
        global_sum += thread_sums[i];
    }

    return global_sum;
}
