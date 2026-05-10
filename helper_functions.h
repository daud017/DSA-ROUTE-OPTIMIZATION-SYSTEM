#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <iostream>
#include <string>
using namespace std;
const int MAX_CITIES = 20;
const int INF = 99999;
void print_line(int length);
void print_header(string title);
void clear_screen();
void pause_screen();
string get_city_label(int index);
void print_route(int route[], int city_count);
int calculate_route_cost(int route[], int city_count, int graph[][MAX_CITIES]);
#endif
