#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H
#include "helper_functions.h"
#include <string>
using namespace std;

class graph_matrix {
public:
    int city_count;
    int matrix[MAX_CITIES][MAX_CITIES];
    graph_matrix();
    bool load_file(string file_name);
    void display_graph();
    int  get_distance(int from, int to);
    bool is_connected();
    void reset();
};
#endif
