#include "tsp_custom.h"
#include <iostream>
using namespace std;

tsp_custom::tsp_custom() {
    best_cost = INF; city_count = 0;
    for (int i = 0; i < MAX_CITIES; i++) {
        best_route[i] = 0;
        for (int j = 0; j < MAX_CITIES; j++) graph[i][j] = 0;
    }
}

// Run greedy from one starting city, return cost
int tsp_custom::run_greedy_from(int start, int temp_route[]) {
    bool visited[MAX_CITIES];
    for (int i = 0; i < city_count; i++) visited[i] = false;
    int current = start, cost = 0;
    visited[current] = true; temp_route[0] = current;

    for (int step = 1; step < city_count; step++) {
        int nearest = -1, nearest_dist = INF;
        for (int next = 0; next < city_count; next++) {
            if (!visited[next] && graph[current][next] > 0 && graph[current][next] < nearest_dist) {
                nearest_dist = graph[current][next]; nearest = next;
            }
        }
        if (nearest == -1) return INF;
        visited[nearest] = true; temp_route[step] = nearest;
        cost += nearest_dist; current = nearest;
    }
    int ret = graph[current][start];
    if (ret == 0) return INF;
    return cost + ret;
}

// Try every city as start point, keep the best result
void tsp_custom::improved_route(int matrix[][MAX_CITIES], int count) {
    city_count = count; best_cost = INF;
    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++)
            graph[i][j] = matrix[i][j];

    for (int start = 0; start < city_count; start++) {
        int temp_route[MAX_CITIES];
        int temp_cost = run_greedy_from(start, temp_route);
        if (temp_cost < best_cost) {
            best_cost = temp_cost;
            for (int i = 0; i < city_count; i++) best_route[i] = temp_route[i];
        }
    }
}

void tsp_custom::show_result() {
    cout << "\n  [Custom Improved Greedy]" << endl;
    if (best_cost == INF) { cout << "  No valid route found." << endl; return; }
    cout << "  Best Route : "; print_route(best_route, city_count);
    cout << "  Total Cost : " << best_cost << endl;
}
