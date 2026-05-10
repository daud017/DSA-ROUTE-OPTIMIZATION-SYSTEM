#include "graph_matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

graph_matrix::graph_matrix() { city_count = 0; reset(); }

void graph_matrix::reset() {
    for (int i = 0; i < MAX_CITIES; i++)
        for (int j = 0; j < MAX_CITIES; j++)
            matrix[i][j] = 0;
}

bool graph_matrix::load_file(string file_name) {
    ifstream fin(file_name.c_str());
    if (!fin.is_open()) { cout << "ERROR: Cannot open file: " << file_name << endl; return false; }
    fin >> city_count;
    if (fin.fail() || city_count <= 0) { cout << "ERROR: Empty or invalid file." << endl; fin.close(); return false; }
    if (city_count == 1) { cout << "WARNING: Only 1 city. No route possible." << endl; fin.close(); return true; }
    if (city_count > MAX_CITIES) { cout << "WARNING: Too many cities. Capping at " << MAX_CITIES << endl; city_count = MAX_CITIES; }
    reset();
    for (int i = 0; i < city_count; i++) {
        for (int j = 0; j < city_count; j++) {
            int val; fin >> val;
            if (fin.fail()) { cout << "ERROR: Not enough data in file." << endl; fin.close(); return false; }
            if (val < 0) { cout << "WARNING: Negative distance set to 0." << endl; val = 0; }
            matrix[i][j] = val;
        }
    }
    fin.close();
    return true;
}

void graph_matrix::display_graph() {
    if (city_count == 0) { cout << "Graph is empty!" << endl; return; }
    cout << "\n  Adjacency Matrix (Static - 2D Array):" << endl;
    print_line(40);
    cout << "      ";
    for (int i = 0; i < city_count; i++) cout << setw(5) << get_city_label(i);
    cout << endl;
    print_line(40);
    for (int i = 0; i < city_count; i++) {
        cout << "  " << get_city_label(i) << "  |";
        for (int j = 0; j < city_count; j++) cout << setw(5) << matrix[i][j];
        cout << endl;
    }
    print_line(40);
}

int graph_matrix::get_distance(int from, int to) {
    if (from < 0 || from >= city_count || to < 0 || to >= city_count) return INF;
    return matrix[from][to];
}

bool graph_matrix::is_connected() {
    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++)
            if (i != j && matrix[i][j] == 0) return false;
    return true;
}
