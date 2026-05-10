#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include "helper_functions.h"
#include <string>
using namespace std;

class file_manager {
public:
    void save_results(string filename,
                      int bf_cost, int bf_route[],
                      int gr_cost, int gr_route[],
                      int cu_cost, int cu_route[],
                      int city_count);
    bool file_exists(string filename);
    void list_graph_files();
};
#endif
