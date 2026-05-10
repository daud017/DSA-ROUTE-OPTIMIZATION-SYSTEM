#ifndef TSP_CUSTOM_H
#define TSP_CUSTOM_H
#include "helper_functions.h"

class tsp_custom {
public:
    int best_cost;
    int best_route[MAX_CITIES];
    int city_count;
    int graph[MAX_CITIES][MAX_CITIES];
    tsp_custom();
    void improved_route(int matrix[][MAX_CITIES], int count);
    int  run_greedy_from(int start, int temp_route[]);
    void show_result();
};
#endif
