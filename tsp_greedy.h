#ifndef TSP_GREEDY_H
#define TSP_GREEDY_H
#include "helper_functions.h"

class tsp_greedy {
public:
    int total_cost;
    int route[MAX_CITIES];
    int city_count;
    int graph[MAX_CITIES][MAX_CITIES];
    tsp_greedy();
    void greedy_route(int matrix[][MAX_CITIES], int count, int start_city);
    void show_result();
};
#endif
