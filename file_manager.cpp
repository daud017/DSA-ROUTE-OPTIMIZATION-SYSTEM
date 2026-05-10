#include "file_manager.h"
#include <iostream>
#include <fstream>
using namespace std;

void file_manager::save_results(string filename,
                                 int bf_cost, int bf_route[],
                                 int gr_cost, int gr_route[],
                                 int cu_cost, int cu_route[],
                                 int city_count) {
    ofstream fout(filename.c_str());
    if (!fout.is_open()) { cout << "ERROR: Cannot write to " << filename << endl; return; }

    fout << "============================================" << endl;
    fout << "   ROUTE OPTIMIZATION SYSTEM - TSP RESULTS" << endl;
    fout << "============================================" << endl;
    fout << "Cities: " << city_count << endl << endl;

    // Brute Force
    fout << "[1] Brute Force TSP  (O(n!))" << endl;
    if (bf_cost == INF) { fout << "   No valid route." << endl; }
    else {
        fout << "   Route : ";
        for (int i = 0; i < city_count; i++) {
            fout << (char)('A' + bf_route[i]);
            if (i < city_count - 1) fout << " -> ";
        }
        fout << " -> " << (char)('A' + bf_route[0]) << endl;
        fout << "   Cost  : " << bf_cost << endl;
    }
    fout << endl;

    // Greedy
    fout << "[2] Greedy Nearest Neighbour  (O(n^2))" << endl;
    if (gr_cost == INF) { fout << "   No valid route." << endl; }
    else {
        fout << "   Route : ";
        for (int i = 0; i < city_count; i++) {
            fout << (char)('A' + gr_route[i]);
            if (i < city_count - 1) fout << " -> ";
        }
        fout << " -> " << (char)('A' + gr_route[0]) << endl;
        fout << "   Cost  : " << gr_cost << endl;
    }
    fout << endl;

    // Custom
    fout << "[3] Custom Improved Greedy  (O(n^2))" << endl;
    if (cu_cost == INF) { fout << "   No valid route." << endl; }
    else {
        fout << "   Route : ";
        for (int i = 0; i < city_count; i++) {
            fout << (char)('A' + cu_route[i]);
            if (i < city_count - 1) fout << " -> ";
        }
        fout << " -> " << (char)('A' + cu_route[0]) << endl;
        fout << "   Cost  : " << cu_cost << endl;
    }
    fout << endl;

    // Comparison table
    fout << "============================================" << endl;
    fout << "COMPARISON TABLE" << endl;
    fout << "============================================" << endl;
    fout << "Algorithm          | Cost  | Complexity" << endl;
    fout << "-------------------|-------|------------" << endl;
    fout << "Brute Force        | " << (bf_cost == INF ? 0 : bf_cost) << "   | O(n!)" << endl;
    fout << "Greedy NN          | " << (gr_cost == INF ? 0 : gr_cost) << "   | O(n^2)" << endl;
    fout << "Custom Greedy      | " << (cu_cost == INF ? 0 : cu_cost) << "   | O(n^2)" << endl;

    fout.close();
    cout << "  Results saved to: " << filename << endl;
}

bool file_manager::file_exists(string filename) {
    ifstream fin(filename.c_str());
    return fin.good();
}

void file_manager::list_graph_files() {
    cout << "\n  Available graph files:" << endl;
    cout << "    data/graph_4.txt  (4 cities)" << endl;
    cout << "    data/graph_5.txt  (5 cities)" << endl;
    cout << "    data/graph_8.txt  (8 cities)" << endl;
}
