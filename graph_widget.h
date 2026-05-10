#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QWidget>
#include <QPainter>
#include "helper_functions.h"

class graph_widget : public QWidget
{
    Q_OBJECT

public:
    explicit graph_widget(QWidget* parent = nullptr);

    // Store the graph matrix
    int city_matrix[MAX_CITIES][MAX_CITIES];
    int city_count;

    // Store the best route to highlight
    int best_route[MAX_CITIES];
    int route_length;
    bool has_route;

    // Functions
    void set_graph(int matrix[][MAX_CITIES], int count);
    void set_route(int route[], int length);
    void clear_route();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    // City positions on screen
    float city_x[MAX_CITIES];
    float city_y[MAX_CITIES];

    void calculate_positions();
    void draw_edges(QPainter& p);
    void draw_route(QPainter& p);
    void draw_cities(QPainter& p);
};

#endif // GRAPH_WIDGET_H
