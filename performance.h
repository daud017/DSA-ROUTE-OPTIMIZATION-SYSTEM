#ifndef PERFORMANCE_H
#define PERFORMANCE_H
#include "helper_functions.h"
#include <time.h>

class performance {
public:
    clock_t start_time;
    clock_t end_time;
    double  elapsed_sec;
    performance();
    void   start_timer();
    void   stop_timer();
    double get_elapsed();
    int    estimate_matrix_memory(int city_count);
    int    estimate_list_memory(int city_count);
    void   print_summary(int city_count,
                         double bf_time, double gr_time, double cu_time,
                         int bf_cost, int gr_cost, int cu_cost);
};
#endif
