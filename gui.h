#ifndef GUI_H
#define GUI_H

#include "helper_functions.h"
#include "graph_matrix.h"
#include "graph_list.h"
#include "tsp_brute_force.h"
#include "tsp_greedy.h"
#include "tsp_custom.h"
#include "performance.h"
#include "file_manager.h"
#include <string>
using namespace std;

// -----------------------------------------------
// gui class - pure console interface
// Works in Visual Studio 2022 without any extra libs
// -----------------------------------------------
class gui {
public:
    graph_matrix    g_matrix;
    graph_list      g_list;
    tsp_brute_force bf_solver;
    tsp_greedy      gr_solver;
    tsp_custom      cu_solver;
    performance     perf;
    file_manager    fmgr;
    double bf_time, gr_time, cu_time;

    gui();
    void display_menu();
    void load_graph();
    void choose_representation();
    void select_algorithm();
    void run_all_algorithms();
    void show_results();
    void save_to_file();
    void draw_ascii_graph();
    void draw_ascii_route();
};
#endif
