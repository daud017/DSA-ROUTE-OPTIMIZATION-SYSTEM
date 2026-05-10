#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QMenuBar>
#include <QStatusBar>

#include "graph_widget.h"
#include "graph_matrix.h"
#include "graph_list.h"
#include "tsp_brute_force.h"
#include "tsp_greedy.h"
#include "tsp_custom.h"
#include "performance.h"
#include "file_manager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void load_graph_file();
    void run_selected_algorithm();
    void run_all_algorithms();
    void save_results();
    void clear_display();

private:
    // ---- Left Panel Widgets ----
    QPushButton* load_button;
    QPushButton* run_button;
    QPushButton* run_all_button;
    QPushButton* save_button;
    QPushButton* clear_button;
    QComboBox*   algo_selector;
    QLabel*      file_label;
    QLabel*      city_count_label;

    // ---- Right Panel Widgets ----
    graph_widget*  my_graph_widget;
    QTextEdit*     result_display;
    QTableWidget*  compare_table;

    // ---- Backend Objects ----
    graph_matrix      my_matrix;
    graph_list        my_list;
    tsp_brute_force   my_brute;
    tsp_greedy        my_greedy;
    tsp_custom        my_custom;
    performance       my_timer;
    file_manager      my_file_manager;

    // ---- State ----
    bool graph_loaded;
    QString current_file_path;

    double bf_time, gr_time, cu_time;
    int    bf_cost, gr_cost, cu_cost;

    // ---- Setup Functions ----
    void setup_ui();
    void setup_menu();
    void update_compare_table();
    void show_result_text(QString text);
};

#endif // MAINWINDOW_H
