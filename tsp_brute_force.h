#ifndef TSP_BRUTE_FORCE_H
#define TSP_BRUTE_FORCE_H
#include "helper_functions.h"

class tsp_brute_force {
public:
    int best_cost;
    int best_route[MAX_CITIES];
    int city_count;
    int graph[MAX_CITIES][MAX_CITIES];
    tsp_brute_force();
    void calculate_route(int matrix[][MAX_CITIES], int count);
    void recursive_search(int current_route[], bool visited[], int depth, int current_cost);
    void show_result();
};
#endif
