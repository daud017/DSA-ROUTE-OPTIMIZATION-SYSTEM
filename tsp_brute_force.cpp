#include "tsp_brute_force.h"
#include <iostream>
using namespace std;

tsp_brute_force::tsp_brute_force() {
    best_cost = INF; city_count = 0;
    for (int i = 0; i < MAX_CITIES; i++) { best_route[i] = 0; for (int j = 0; j < MAX_CITIES; j++) graph[i][j] = 0; }
}

void tsp_brute_force::calculate_route(int matrix[][MAX_CITIES], int count) {
    city_count = count; best_cost = INF;
    for (int i = 0; i < city_count; i++) for (int j = 0; j < city_count; j++) graph[i][j] = matrix[i][j];
    bool visited[MAX_CITIES]; int current_route[MAX_CITIES];
    for (int i = 0; i < city_count; i++) { visited[i] = false; current_route[i] = 0; }
    visited[0] = true; current_route[0] = 0;
    recursive_search(current_route, visited, 1, 0);
}

void tsp_brute_force::recursive_search(int current_route[], bool visited[], int depth, int current_cost) {
    if (depth == city_count) {
        int last = current_route[depth-1];
        int go_back = graph[last][0];
        if (go_back == 0 && last != 0) return;
        int total = current_cost + go_back;
        if (total < best_cost) { best_cost = total; for (int i = 0; i < city_count; i++) best_route[i] = current_route[i]; }
        return;
    }
    for (int next = 0; next < city_count; next++) {
        if (!visited[next]) {
            int from = current_route[depth-1];
            int weight = graph[from][next];
            if (weight == 0) continue;
            if (current_cost + weight >= best_cost) continue;
            visited[next] = true; current_route[depth] = next;
            recursive_search(current_route, visited, depth+1, current_cost + weight);
            visited[next] = false;
        }
    }
}

void tsp_brute_force::show_result() {
    cout << "\n  [Brute Force TSP]" << endl;
    if (best_cost == INF) { cout << "  No valid route found." << endl; return; }
    cout << "  Best Route : "; print_route(best_route, city_count);
    cout << "  Total Cost : " << best_cost << endl;
}
