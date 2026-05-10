#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H
#include "helper_functions.h"

struct linked_node {
    int dest_city;
    int edge_weight;
    linked_node* next;
};

class graph_list {
public:
    int city_count;
    linked_node* head[MAX_CITIES];
    graph_list();
    ~graph_list();
    void add_edge(int from, int to, int weight);
    void display_list();
    void build_from_matrix(int matrix[][MAX_CITIES], int count);
    int  get_weight(int from, int to);
    void free_memory();
};
#endif
