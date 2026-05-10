#include "performance.h"
#include <iostream>
#include <iomanip>
using namespace std;

performance::performance() { start_time = 0; end_time = 0; elapsed_sec = 0.0; }

void performance::start_timer() { start_time = clock(); }
void performance::stop_timer()  { end_time = clock(); elapsed_sec = (double)(end_time - start_time) / CLOCKS_PER_SEC; }
double performance::get_elapsed() { return elapsed_sec; }

int performance::estimate_matrix_memory(int city_count) { return city_count * city_count * sizeof(int); }
int performance::estimate_list_memory(int city_count)   { return city_count * city_count * (sizeof(int)*2 + sizeof(void*)); }

void performance::print_summary(int city_count,
                                 double bf_time, double gr_time, double cu_time,
                                 int bf_cost, int gr_cost, int cu_cost) {
    cout << endl;
    print_header("PERFORMANCE ANALYSIS");
    cout << "  Cities        : " << city_count << endl;
    cout << "  Matrix Memory : " << estimate_matrix_memory(city_count) << " bytes" << endl;
    cout << "  List Memory   : " << estimate_list_memory(city_count)   << " bytes" << endl;
    cout << endl;
    print_line(65);
    cout << left
         << setw(22) << "  Algorithm"
         << setw(10) << "Cost"
         << setw(18) << "Time (sec)"
         << setw(12) << "Complexity" << endl;
    print_line(65);

    // Brute Force row
    cout << setw(22) << "  Brute Force";
    cout << setw(10) << (bf_cost == INF ? 0 : bf_cost);
    cout << setw(18) << fixed << setprecision(6) << bf_time;
    cout << setw(12) << "O(n!)" << endl;

    // Greedy row
    cout << setw(22) << "  Greedy NN";
    cout << setw(10) << (gr_cost == INF ? 0 : gr_cost);
    cout << setw(18) << fixed << setprecision(6) << gr_time;
    cout << setw(12) << "O(n^2)" << endl;

    // Custom row
    cout << setw(22) << "  Custom Greedy";
    cout << setw(10) << (cu_cost == INF ? 0 : cu_cost);
    cout << setw(18) << fixed << setprecision(6) << cu_time;
    cout << setw(12) << "O(n^2)" << endl;

    print_line(65);
    cout << "\n  * Brute Force = exact but slow for large n" << endl;
    cout << "  * Greedy     = fast but may miss optimal"   << endl;
    cout << "  * Custom     = better than basic greedy"    << endl;
}
