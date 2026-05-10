#include "graph_list.h"
#include <iostream>
using namespace std;

graph_list::graph_list() {
    city_count = 0;
    for (int i = 0; i < MAX_CITIES; i++) head[i] = NULL;
}
graph_list::~graph_list() { free_memory(); }

void graph_list::free_memory() {
    for (int i = 0; i < MAX_CITIES; i++) {
        linked_node* cur = head[i];
        while (cur != NULL) { linked_node* tmp = cur; cur = cur->next; delete tmp; }
        head[i] = NULL;
    }
}

void graph_list::add_edge(int from, int to, int weight) {
    linked_node* node = new linked_node;
    node->dest_city = to; node->edge_weight = weight; node->next = NULL;
    if (head[from] == NULL) { head[from] = node; return; }
    linked_node* cur = head[from];
    while (cur->next != NULL) cur = cur->next;
    cur->next = node;
}

void graph_list::display_list() {
    if (city_count == 0) { cout << "List is empty!" << endl; return; }
    cout << "\n  Adjacency Linked List (Dynamic - Linked Nodes):" << endl;
    print_line(45);
    for (int i = 0; i < city_count; i++) {
        cout << "  City " << get_city_label(i) << " -> ";
        linked_node* cur = head[i];
        if (!cur) cout << "(no edges)";
        while (cur) {
            cout << get_city_label(cur->dest_city) << "(" << cur->edge_weight << ")";
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << endl;
    }
    print_line(45);
}

void graph_list::build_from_matrix(int matrix[][MAX_CITIES], int count) {
    free_memory();
    city_count = count;
    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++)
            if (i != j && matrix[i][j] > 0)
                add_edge(i, j, matrix[i][j]);
}

int graph_list::get_weight(int from, int to) {
    if (from < 0 || from >= city_count) return INF;
    linked_node* cur = head[from];
    while (cur) { if (cur->dest_city == to) return cur->edge_weight; cur = cur->next; }
    return INF;
}
