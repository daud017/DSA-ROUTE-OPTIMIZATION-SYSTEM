#include "tsp_greedy.h"
#include <iostream>
using namespace std;

tsp_greedy::tsp_greedy() {
    total_cost = 0; city_count = 0;
    for (int i = 0; i < MAX_CITIES; i++) { route[i] = 0; for (int j = 0; j < MAX_CITIES; j++) graph[i][j] = 0; }
}

void tsp_greedy::greedy_route(int matrix[][MAX_CITIES], int count, int start_city) {
    city_count = count; total_cost = 0;
    for (int i = 0; i < city_count; i++) for (int j = 0; j < city_count; j++) graph[i][j] = matrix[i][j];
    bool visited[MAX_CITIES];
    for (int i = 0; i < city_count; i++) visited[i] = false;
    int current = start_city; visited[current] = true; route[0] = current;
    for (int step = 1; step < city_count; step++) {
        int nearest = -1, nearest_dist = INF;
        for (int next = 0; next < city_count; next++) {
            if (!visited[next] && graph[current][next] > 0 && graph[current][next] < nearest_dist) {
                nearest_dist = graph[current][next]; nearest = next;
            }
        }
        if (nearest == -1) { total_cost = INF; return; }
        visited[nearest] = true; route[step] = nearest; total_cost += nearest_dist; current = nearest;
    }
    int ret = graph[current][start_city];
    if (ret == 0) { total_cost = INF; return; }
    total_cost += ret;
}

void tsp_greedy::show_result() {
    cout << "\n  [Greedy Nearest Neighbour]" << endl;
    if (total_cost == INF) { cout << "  No valid route found." << endl; return; }
    cout << "  Route      : "; print_route(route, city_count);
    cout << "  Total Cost : " << total_cost << endl;
}
