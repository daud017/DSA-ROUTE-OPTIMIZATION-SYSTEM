#include "gui.h"
#include <iostream>
#include <iomanip>
using namespace std;

gui::gui() { bf_time = gr_time = cu_time = 0.0; }

void gui::display_menu() {
    int choice = 0;
    while (true) {
        clear_screen();
        cout << endl;
        print_line(55);
        cout << "      ROUTE OPTIMIZATION SYSTEM  -  TSP" << endl;
        cout << "         Delivery Route Optimizer" << endl;
        print_line(55);
        cout << "  1.  Load Graph from File"          << endl;
        cout << "  2.  Display Graph Representations" << endl;
        cout << "  3.  Visualize Graph (ASCII)"       << endl;
        cout << "  4.  Run ALL Algorithms + Compare"  << endl;
        cout << "  5.  Run Single Algorithm"          << endl;
        cout << "  6.  Performance Analysis"          << endl;
        cout << "  7.  Save Results to File"          << endl;
        cout << "  0.  Exit"                          << endl;
        print_line(55);
        cout << "  Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: load_graph();            break;
            case 2: choose_representation(); break;
            case 3:
                draw_ascii_graph();
                draw_ascii_route();
                pause_screen();
                break;
            case 4: run_all_algorithms(); break;
            case 5: select_algorithm();   break;
            case 6:
                perf.print_summary(g_matrix.city_count,
                    bf_time, gr_time, cu_time,
                    bf_solver.best_cost,
                    gr_solver.total_cost,
                    cu_solver.best_cost);
                pause_screen();
                break;
            case 7: save_to_file(); break;
            case 0:
                cout << "\n  Goodbye!\n" << endl;
                return;
            default:
                cout << "\n  Invalid choice. Try again." << endl;
                pause_screen();
        }
    }
}

void gui::load_graph() {
    clear_screen();
    print_header("LOAD GRAPH FROM FILE");
    fmgr.list_graph_files();
    cout << "\n  Enter filename (e.g. data/graph_4.txt): ";
    string fname; cin >> fname;

    bool ok = g_matrix.load_file(fname);
    if (!ok) { cout << "\n  Failed to load file." << endl; pause_screen(); return; }

    g_list.build_from_matrix(g_matrix.matrix, g_matrix.city_count);
    cout << "\n  Graph loaded! Cities: " << g_matrix.city_count << endl;

    if (g_matrix.city_count > 10)
        cout << "  WARNING: Large graph - Brute Force will be slow!" << endl;
    if (!g_matrix.is_connected())
        cout << "  WARNING: Graph may be disconnected!" << endl;

    pause_screen();
}

void gui::choose_representation() {
    if (g_matrix.city_count == 0) {
        cout << "\n  Please load a graph first!" << endl; pause_screen(); return;
    }
    clear_screen();
    print_header("GRAPH REPRESENTATION");
    cout << "  1. Adjacency Matrix  (Static  - 2D Array)"     << endl;
    cout << "  2. Adjacency List    (Dynamic - Linked List)"  << endl;
    cout << "  3. Both"                                        << endl;
    cout << "\n  Choice: ";
    int choice; cin >> choice; cout << endl;
    if (choice == 1 || choice == 3) g_matrix.display_graph();
    if (choice == 2 || choice == 3) g_list.display_list();
    pause_screen();
}

void gui::select_algorithm() {
    if (g_matrix.city_count == 0) {
        cout << "\n  Please load a graph first!" << endl; pause_screen(); return;
    }
    if (g_matrix.city_count == 1) {
        cout << "\n  Only 1 city. Nothing to compute." << endl; pause_screen(); return;
    }
    clear_screen();
    print_header("SELECT ALGORITHM");
    cout << "  1. Brute Force    (Exact     - O(n!) )" << endl;
    cout << "  2. Greedy NN      (Fast      - O(n^2))" << endl;
    cout << "  3. Custom Greedy  (Improved  - O(n^2))" << endl;
    cout << "\n  Choice: ";
    int choice; cin >> choice; cout << endl;

    if (choice == 1) {
        cout << "  Running Brute Force..." << endl;
        perf.start_timer();
        bf_solver.calculate_route(g_matrix.matrix, g_matrix.city_count);
        perf.stop_timer(); bf_time = perf.get_elapsed();
        bf_solver.show_result();
        cout << "  Time : " << bf_time << " sec" << endl;
    } else if (choice == 2) {
        cout << "  Running Greedy..." << endl;
        perf.start_timer();
        gr_solver.greedy_route(g_matrix.matrix, g_matrix.city_count, 0);
        perf.stop_timer(); gr_time = perf.get_elapsed();
        gr_solver.show_result();
        cout << "  Time : " << gr_time << " sec" << endl;
    } else if (choice == 3) {
        cout << "  Running Custom Greedy..." << endl;
        perf.start_timer();
        cu_solver.improved_route(g_matrix.matrix, g_matrix.city_count);
        perf.stop_timer(); cu_time = perf.get_elapsed();
        cu_solver.show_result();
        cout << "  Time : " << cu_time << " sec" << endl;
    } else {
        cout << "  Invalid choice." << endl;
    }
    pause_screen();
}

void gui::run_all_algorithms() {
    if (g_matrix.city_count == 0) {
        cout << "\n  Please load a graph first!" << endl; pause_screen(); return;
    }
    if (g_matrix.city_count == 1) {
        cout << "\n  Only 1 city. Nothing to compute." << endl; pause_screen(); return;
    }
    clear_screen();
    print_header("RUNNING ALL ALGORITHMS");

    cout << "\n  [1/3] Brute Force..." << endl;
    perf.start_timer();
    bf_solver.calculate_route(g_matrix.matrix, g_matrix.city_count);
    perf.stop_timer(); bf_time = perf.get_elapsed();
    cout << "        Done. Time: " << bf_time << " sec" << endl;

    cout << "  [2/3] Greedy Nearest Neighbour..." << endl;
    perf.start_timer();
    gr_solver.greedy_route(g_matrix.matrix, g_matrix.city_count, 0);
    perf.stop_timer(); gr_time = perf.get_elapsed();
    cout << "        Done. Time: " << gr_time << " sec" << endl;

    cout << "  [3/3] Custom Improved Greedy..." << endl;
    perf.start_timer();
    cu_solver.improved_route(g_matrix.matrix, g_matrix.city_count);
    perf.stop_timer(); cu_time = perf.get_elapsed();
    cout << "        Done. Time: " << cu_time << " sec" << endl;

    show_results();
    draw_ascii_route();
    pause_screen();
}

void gui::show_results() {
    cout << endl;
    print_line(60);
    cout << "  RESULTS SUMMARY" << endl;
    print_line(60);

    bf_solver.show_result();
    cout << "  Time : " << bf_time << " sec" << endl;

    gr_solver.show_result();
    cout << "  Time : " << gr_time << " sec" << endl;

    cu_solver.show_result();
    cout << "  Time : " << cu_time << " sec" << endl;

    print_line(60);
    cout << left
         << setw(22) << "\n  Algorithm"
         << setw(10) << "Cost"
         << setw(16) << "Time(sec)"
         << setw(10) << "Big-O" << endl;
    print_line(60);
    cout << setw(22) << "  Brute Force"
         << setw(10) << (bf_solver.best_cost  == INF ? 0 : bf_solver.best_cost)
         << setw(16) << bf_time << setw(10) << "O(n!)"   << endl;
    cout << setw(22) << "  Greedy NN"
         << setw(10) << (gr_solver.total_cost == INF ? 0 : gr_solver.total_cost)
         << setw(16) << gr_time << setw(10) << "O(n^2)"  << endl;
    cout << setw(22) << "  Custom Greedy"
         << setw(10) << (cu_solver.best_cost  == INF ? 0 : cu_solver.best_cost)
         << setw(16) << cu_time << setw(10) << "O(n^2)"  << endl;
    print_line(60);
}

void gui::save_to_file() {
    if (g_matrix.city_count == 0) {
        cout << "\n  No graph loaded!" << endl; pause_screen(); return;
    }
    fmgr.save_results("output/results.txt",
        bf_solver.best_cost,  bf_solver.best_route,
        gr_solver.total_cost, gr_solver.route,
        cu_solver.best_cost,  cu_solver.best_route,
        g_matrix.city_count);
    pause_screen();
}

void gui::draw_ascii_graph() {
    if (g_matrix.city_count == 0) { cout << "\n  No graph loaded!" << endl; return; }
    int n = g_matrix.city_count;
    cout << endl;
    print_header("ASCII GRAPH VISUALIZATION");
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << "  [" << get_city_label(i) << "] ";
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (i != j && g_matrix.matrix[i][j] > 0) {
                cout << "---" << g_matrix.matrix[i][j]
                     << "---> [" << get_city_label(j) << "]  ";
                found = true;
            }
        }
        if (!found) cout << "(no connections)";
        cout << endl;
    }

    cout << endl;
    print_line(40);
    cout << "\n  Distance Table:" << endl;
    cout << "       ";
    for (int i = 0; i < n; i++) cout << setw(6) << get_city_label(i);
    cout << endl;
    print_line(40);
    for (int i = 0; i < n; i++) {
        cout << "  [" << get_city_label(i) << "] |";
        for (int j = 0; j < n; j++) cout << setw(6) << g_matrix.matrix[i][j];
        cout << endl;
    }
    print_line(40);
}

void gui::draw_ascii_route() {
    if (cu_solver.best_cost == INF || cu_solver.best_cost == 0) {
        cout << "\n  (Run algorithms first to see route)" << endl;
        return;
    }
    int n  = g_matrix.city_count;
    int* rt = cu_solver.best_route;

    cout << endl;
    print_header("BEST ROUTE  (Custom Greedy)");
    cout << endl;

    // Top border
    cout << "  ";
    for (int i = 0; i <= n; i++) cout << "+-------+";
    cout << endl;

    // City labels row
    cout << "  ";
    for (int i = 0; i < n; i++)  cout << "|   " << get_city_label(rt[i]) << "   |";
    cout << "|   " << get_city_label(rt[0]) << "   |";
    cout << endl;

    // Bottom border
    cout << "  ";
    for (int i = 0; i <= n; i++) cout << "+-------+";
    cout << endl;

    // Cost arrows
    cout << "  ";
    for (int i = 0; i < n - 1; i++) {
        int cost = g_matrix.matrix[rt[i]][rt[i+1]];
        cout << "         -" << cost << "->";
    }
    int ret_cost = g_matrix.matrix[rt[n-1]][rt[0]];
    cout << "         -" << ret_cost << "->" << endl;

    cout << endl;
    cout << "  Full Path  : "; print_route(rt, n);
    cout << "  Total Cost : " << cu_solver.best_cost << endl;
    cout << endl;
}
