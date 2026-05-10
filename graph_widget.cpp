#include "graph_widget.h"
#include <QtMath>

graph_widget::graph_widget(QWidget* parent) : QWidget(parent)
{
    city_count = 0;
    route_length = 0;
    has_route = false;

    for (int i = 0; i < MAX_CITIES; i++) {
        best_route[i] = 0;
        city_x[i] = 0;
        city_y[i] = 0;
        for (int j = 0; j < MAX_CITIES; j++)
            city_matrix[i][j] = 0;
    }

    setMinimumSize(400, 400);
    setStyleSheet("background-color: white;");
}

void graph_widget::set_graph(int matrix[][MAX_CITIES], int count)
{
    city_count = count;
    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++)
            city_matrix[i][j] = matrix[i][j];

    has_route = false;
    calculate_positions();
    update();
}

void graph_widget::set_route(int route[], int length)
{
    route_length = length;
    has_route = true;
    for (int i = 0; i < length; i++)
        best_route[i] = route[i];
    update();
}

void graph_widget::clear_route()
{
    has_route = false;
    update();
}

void graph_widget::calculate_positions()
{
    float cx = width() / 2.0f;
    float cy = height() / 2.0f;
    float w = (float)width();
    float h = (float)height();
    float radius = (w < h ? w : h) / 2.0f - 50;

    for (int i = 0; i < city_count; i++) {
        float angle = 2.0f * M_PI * i / city_count - M_PI / 2.0f;
        city_x[i] = cx + radius * cos(angle);
        city_y[i] = cy + radius * sin(angle);
    }
}

void graph_widget::draw_edges(QPainter& p)
{
    QPen edge_pen(QColor(200, 200, 200), 1);
    p.setPen(edge_pen);

    QFont small_font = p.font();
    small_font.setPointSize(8);
    p.setFont(small_font);

    for (int i = 0; i < city_count; i++) {
        for (int j = i + 1; j < city_count; j++) {
            if (city_matrix[i][j] > 0) {
                p.drawLine((int)city_x[i], (int)city_y[i],
                           (int)city_x[j], (int)city_y[j]);

                int mid_x = (city_x[i] + city_x[j]) / 2;
                int mid_y = (city_y[i] + city_y[j]) / 2;
                p.setPen(QColor(100, 100, 100));
                p.drawText(mid_x - 10, mid_y - 5, 25, 15,
                           Qt::AlignCenter,
                           QString::number(city_matrix[i][j]));
                p.setPen(edge_pen);
            }
        }
    }
}

void graph_widget::draw_route(QPainter& p)
{
    if (!has_route || route_length == 0) return;

    QPen route_pen(QColor(0, 120, 255), 3);
    p.setPen(route_pen);

    for (int i = 0; i < route_length - 1; i++) {
        int from = best_route[i];
        int to   = best_route[i + 1];
        p.drawLine((int)city_x[from], (int)city_y[from],
                   (int)city_x[to],   (int)city_y[to]);
    }

    int last  = best_route[route_length - 1];
    int first = best_route[0];
    p.drawLine((int)city_x[last], (int)city_y[last],
               (int)city_x[first], (int)city_y[first]);
}

void graph_widget::draw_cities(QPainter& p)
{
    int circle_size = 36;

    for (int i = 0; i < city_count; i++) {
        int x = (int)city_x[i] - circle_size / 2;
        int y = (int)city_y[i] - circle_size / 2;

        p.setBrush(QColor(52, 152, 219));
        p.setPen(QPen(QColor(30, 100, 180), 2));
        p.drawEllipse(x, y, circle_size, circle_size);

        p.setPen(Qt::white);
        QFont city_font;
        city_font.setPointSize(12);
        city_font.setBold(true);
        p.setFont(city_font);
        p.drawText(x, y, circle_size, circle_size,
                   Qt::AlignCenter,
                   QString(QChar('A' + i)));
    }
}

void graph_widget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if (city_count == 0) {
        p.setPen(QColor(150, 150, 150));
        QFont f;
        f.setPointSize(12);
        p.setFont(f);
        p.drawText(rect(), Qt::AlignCenter,
                   "Load a graph file to see visualization");
        return;
    }

    calculate_positions();
    draw_edges(p);
    draw_route(p);
    draw_cities(p);
}
