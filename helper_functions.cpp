#include "helper_functions.h"
#include <iostream>
using namespace std;

void print_line(int length) {
    for (int i = 0; i < length; i++) cout << "-";
    cout << endl;
}

void print_header(string title) {
    print_line(55);
    cout << "  " << title << endl;
    print_line(55);
}

void clear_screen() {
    system("cls");
}

void pause_screen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

string get_city_label(int index) {
    string label = "";
    label += (char)('A' + index);
    return label;
}

void print_route(int route[], int city_count) {
    for (int i = 0; i < city_count; i++) {
        cout << get_city_label(route[i]);
        if (i < city_count - 1) cout << " -> ";
    }
    cout << " -> " << get_city_label(route[0]);
    cout << endl;
}

int calculate_route_cost(int route[], int city_count, int graph[][MAX_CITIES]) {
    int total = 0;
    for (int i = 0; i < city_count - 1; i++) {
        int from = route[i], to = route[i+1];
        if (graph[from][to] == 0) return INF;
        total += graph[from][to];
    }
    int last = route[city_count-1], first = route[0];
    if (graph[last][first] == 0) return INF;
    total += graph[last][first];
    return total;
}
