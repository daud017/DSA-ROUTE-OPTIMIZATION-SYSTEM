#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    graph_loaded = false;
    bf_time = gr_time = cu_time = 0.0;
    bf_cost = gr_cost = cu_cost = 0;

    setup_ui();
    setup_menu();

    setWindowTitle("Route Optimization System - TSP");
    setMinimumSize(1100, 700);
    setStyleSheet("background-color: #f5f5f5;");
}

MainWindow::~MainWindow() {}

// =============================================
// UI SETUP
// =============================================

void MainWindow::setup_ui()
{
    // ---- Central widget and main layout ----
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout* main_layout = new QHBoxLayout(central);
    main_layout->setSpacing(10);
    main_layout->setContentsMargins(10, 10, 10, 10);

    // ==========================================
    // LEFT PANEL
    // ==========================================
    QGroupBox* left_panel = new QGroupBox("Controls", central);
    left_panel->setFixedWidth(220);
    left_panel->setStyleSheet(
        "QGroupBox { font-weight: bold; font-size: 13px; "
        "background-color: white; border: 1px solid #ccc; border-radius: 6px; padding-top: 15px; }"
        );

    QVBoxLayout* left_layout = new QVBoxLayout(left_panel);
    left_layout->setSpacing(10);
    left_layout->setContentsMargins(12, 12, 12, 12);

    // File label
    file_label = new QLabel("No file loaded", left_panel);
    file_label->setWordWrap(true);
    file_label->setStyleSheet("color: #888; font-size: 11px;");

    // City count label
    city_count_label = new QLabel("Cities: -", left_panel);
    city_count_label->setStyleSheet("font-size: 12px; color: #333;");

    // Load button
    load_button = new QPushButton("Load Graph File", left_panel);
    load_button->setStyleSheet(
        "QPushButton { background-color: #3498db; color: white; border-radius: 5px; "
        "padding: 8px; font-size: 12px; font-weight: bold; }"
        "QPushButton:hover { background-color: #2980b9; }"
        );

    // Algorithm selector label
    QLabel* algo_label = new QLabel("Select Algorithm:", left_panel);
    algo_label->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;");

    // Dropdown
    algo_selector = new QComboBox(left_panel);
    algo_selector->addItem("Brute Force  O(n!)");
    algo_selector->addItem("Greedy Nearest  O(n²)");
    algo_selector->addItem("Custom Multi-Start  O(n²)");
    algo_selector->setStyleSheet(
        "QComboBox { padding: 5px; font-size: 11px; border: 1px solid #ccc; border-radius: 4px; }"
        );

    // Run one button
    run_button = new QPushButton("Run Algorithm", left_panel);
    run_button->setStyleSheet(
        "QPushButton { background-color: #2ecc71; color: white; border-radius: 5px; "
        "padding: 8px; font-size: 12px; font-weight: bold; }"
        "QPushButton:hover { background-color: #27ae60; }"
        );

    // Run all button
    run_all_button = new QPushButton("Run All & Compare", left_panel);
    run_all_button->setStyleSheet(
        "QPushButton { background-color: #9b59b6; color: white; border-radius: 5px; "
        "padding: 8px; font-size: 12px; font-weight: bold; }"
        "QPushButton:hover { background-color: #8e44ad; }"
        );

    // Save button
    save_button = new QPushButton("Save Results", left_panel);
    save_button->setStyleSheet(
        "QPushButton { background-color: #e67e22; color: white; border-radius: 5px; "
        "padding: 8px; font-size: 12px; font-weight: bold; }"
        "QPushButton:hover { background-color: #d35400; }"
        );

    // Clear button
    clear_button = new QPushButton("Clear", left_panel);
    clear_button->setStyleSheet(
        "QPushButton { background-color: #e74c3c; color: white; border-radius: 5px; "
        "padding: 8px; font-size: 12px; }"
        "QPushButton:hover { background-color: #c0392b; }"
        );

    // Add everything to left panel
    left_layout->addWidget(load_button);
    left_layout->addWidget(file_label);
    left_layout->addWidget(city_count_label);
    left_layout->addSpacing(10);
    left_layout->addWidget(algo_label);
    left_layout->addWidget(algo_selector);
    left_layout->addWidget(run_button);
    left_layout->addWidget(run_all_button);
    left_layout->addSpacing(10);
    left_layout->addWidget(save_button);
    left_layout->addWidget(clear_button);
    left_layout->addStretch();

    // ==========================================
    // MIDDLE PANEL - Graph Visualization
    // ==========================================
    QGroupBox* graph_panel = new QGroupBox("Graph Visualization", central);
    graph_panel->setStyleSheet(
        "QGroupBox { font-weight: bold; font-size: 13px; "
        "background-color: white; border: 1px solid #ccc; border-radius: 6px; padding-top: 15px; }"
        );

    QVBoxLayout* graph_layout = new QVBoxLayout(graph_panel);
    my_graph_widget = new graph_widget(graph_panel);
    graph_layout->addWidget(my_graph_widget);

    // ==========================================
    // RIGHT PANEL - Results
    // ==========================================
    QGroupBox* right_panel = new QGroupBox("Results", central);
    right_panel->setFixedWidth(300);
    right_panel->setStyleSheet(
        "QGroupBox { font-weight: bold; font-size: 13px; "
        "background-color: white; border: 1px solid #ccc; border-radius: 6px; padding-top: 15px; }"
        );

    QVBoxLayout* right_layout = new QVBoxLayout(right_panel);
    right_layout->setSpacing(8);
    right_layout->setContentsMargins(10, 12, 10, 10);

    // Result text box
    QLabel* result_label = new QLabel("Algorithm Output:", right_panel);
    result_label->setStyleSheet("font-weight: bold; color: #333;");

    result_display = new QTextEdit(right_panel);
    result_display->setReadOnly(true);
    result_display->setFixedHeight(200);
    result_display->setStyleSheet(
        "QTextEdit { background-color: #fafafa; border: 1px solid #ddd; "
        "font-family: Consolas, monospace; font-size: 11px; }"
        );

    // Comparison table
    QLabel* table_label = new QLabel("Comparison Table:", right_panel);
    table_label->setStyleSheet("font-weight: bold; color: #333;");

    compare_table = new QTableWidget(3, 3, right_panel);
    compare_table->setHorizontalHeaderLabels({"Algorithm", "Cost", "Time(s)"});
    compare_table->verticalHeader()->setVisible(false);
    compare_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    compare_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    compare_table->setStyleSheet(
        "QTableWidget { border: 1px solid #ddd; font-size: 11px; }"
        "QHeaderView::section { background-color: #3498db; color: white; padding: 4px; }"
        );

    // Fill table with placeholder rows
    QStringList algo_names = {"Brute Force", "Greedy NN", "Custom"};
    for (int i = 0; i < 3; i++) {
        compare_table->setItem(i, 0, new QTableWidgetItem(algo_names[i]));
        compare_table->setItem(i, 1, new QTableWidgetItem("-"));
        compare_table->setItem(i, 2, new QTableWidgetItem("-"));
    }

    right_layout->addWidget(result_label);
    right_layout->addWidget(result_display);
    right_layout->addSpacing(5);
    right_layout->addWidget(table_label);
    right_layout->addWidget(compare_table);
    right_layout->addStretch();

    // ==========================================
    // Combine all panels
    // ==========================================
    main_layout->addWidget(left_panel);
    main_layout->addWidget(graph_panel, 1);
    main_layout->addWidget(right_panel);

    // ==========================================
    // Connect buttons to functions
    // ==========================================
    connect(load_button,    &QPushButton::clicked, this, &MainWindow::load_graph_file);
    connect(run_button,     &QPushButton::clicked, this, &MainWindow::run_selected_algorithm);
    connect(run_all_button, &QPushButton::clicked, this, &MainWindow::run_all_algorithms);
    connect(save_button,    &QPushButton::clicked, this, &MainWindow::save_results);
    connect(clear_button,   &QPushButton::clicked, this, &MainWindow::clear_display);

    statusBar()->showMessage("Ready — Load a graph file to begin");
}

void MainWindow::setup_menu()
{
    QMenu* file_menu = menuBar()->addMenu("File");
    file_menu->addAction("Load Graph", this, &MainWindow::load_graph_file);
    file_menu->addAction("Save Results", this, &MainWindow::save_results);
    file_menu->addSeparator();
    file_menu->addAction("Exit", this, &QWidget::close);

    QMenu* run_menu = menuBar()->addMenu("Run");
    run_menu->addAction("Run Selected Algorithm", this, &MainWindow::run_selected_algorithm);
    run_menu->addAction("Run All & Compare",      this, &MainWindow::run_all_algorithms);

    QMenu* help_menu = menuBar()->addMenu("Help");
    help_menu->addAction("About", this, [this]() {
        QMessageBox::information(this, "About",
                                 "Route Optimization System\n"
                                 "Using Travelling Salesman Problem (TSP)\n\n"
                                 "BSCS - 3rd Semester DSA Project\n\n"
                                 "Algorithms:\n"
                                 "  - Brute Force     O(n!)\n"
                                 "  - Greedy NN       O(n²)\n"
                                 "  - Custom Greedy   O(n²)");
    });
}

// =============================================
// BUTTON FUNCTIONS
// =============================================

void MainWindow::load_graph_file()
{
    QString file_path = QFileDialog::getOpenFileName(
        this,
        "Open Graph File",
        "D:/TSP_Console_final/TSP_Console_final/TSP_Project/data/",
        "Text Files (*.txt)"
        );

    if (file_path.isEmpty()) return;

    std::string path_str = file_path.toStdString();

    if (!my_matrix.load_file(path_str)) {
        QMessageBox::warning(this, "Error", "Could not load graph file!");
        return;
    }

    my_list.build_from_matrix(my_matrix.matrix, my_matrix.city_count);
    my_graph_widget->set_graph(my_matrix.matrix, my_matrix.city_count);

    graph_loaded = true;
    current_file_path = file_path;

    // Update labels
    QString short_name = QFileInfo(file_path).fileName();
    file_label->setText("File: " + short_name);
    city_count_label->setText("Cities: " + QString::number(my_matrix.city_count));

    result_display->setText("Graph loaded successfully!\n"
                            "Cities: " + QString::number(my_matrix.city_count) + "\n\n"
                                                                      "Select an algorithm and click Run.");

    statusBar()->showMessage("Graph loaded: " + short_name);
}

void MainWindow::run_selected_algorithm()
{
    if (!graph_loaded) {
        QMessageBox::warning(this, "Warning", "Please load a graph file first!");
        return;
    }

    int choice = algo_selector->currentIndex();
    QString output = "";

    if (choice == 0) {
        // Brute Force
        my_timer.start_timer();
        my_brute.calculate_route(my_matrix.matrix, my_matrix.city_count);
        my_timer.stop_timer();
        bf_time = my_timer.get_elapsed();
        bf_cost = my_brute.best_cost;

        output += "=== Brute Force TSP ===\n";
        if (bf_cost == INF) {
            output += "No valid route found.\n";
        } else {
            output += "Route: ";
            for (int i = 0; i < my_matrix.city_count; i++)
                output += QString(QChar('A' + my_brute.best_route[i])) + (i < my_matrix.city_count - 1 ? " -> " : "");
            output += " -> " + QString(QChar('A' + my_brute.best_route[0])) + "\n";
            output += "Cost: " + QString::number(bf_cost) + "\n";
            output += "Time: " + QString::number(bf_time, 'f', 6) + " sec\n";
            my_graph_widget->set_route(my_brute.best_route, my_matrix.city_count);
        }

    } else if (choice == 1) {
        // Greedy
        my_timer.start_timer();
        my_greedy.greedy_route(my_matrix.matrix, my_matrix.city_count, 0);
        my_timer.stop_timer();
        gr_time = my_timer.get_elapsed();
        gr_cost = my_greedy.total_cost;

        output += "=== Greedy Nearest Neighbour ===\n";
        if (gr_cost == INF) {
            output += "No valid route found.\n";
        } else {
            output += "Route: ";
            for (int i = 0; i < my_matrix.city_count; i++)
                output += QString(QChar('A' + my_greedy.route[i])) + (i < my_matrix.city_count - 1 ? " -> " : "");
            output += " -> " + QString(QChar('A' + my_greedy.route[0])) + "\n";
            output += "Cost: " + QString::number(gr_cost) + "\n";
            output += "Time: " + QString::number(gr_time, 'f', 6) + " sec\n";
            my_graph_widget->set_route(my_greedy.route, my_matrix.city_count);
        }

    } else {
        // Custom
        my_timer.start_timer();
        my_custom.improved_route(my_matrix.matrix, my_matrix.city_count);
        my_timer.stop_timer();
        cu_time = my_timer.get_elapsed();
        cu_cost = my_custom.best_cost;

        output += "=== Custom Multi-Start Greedy ===\n";
        if (cu_cost == INF) {
            output += "No valid route found.\n";
        } else {
            output += "Route: ";
            for (int i = 0; i < my_matrix.city_count; i++)
                output += QString(QChar('A' + my_custom.best_route[i])) + (i < my_matrix.city_count - 1 ? " -> " : "");
            output += " -> " + QString(QChar('A' + my_custom.best_route[0])) + "\n";
            output += "Cost: " + QString::number(cu_cost) + "\n";
            output += "Time: " + QString::number(cu_time, 'f', 6) + " sec\n";
            my_graph_widget->set_route(my_custom.best_route, my_matrix.city_count);
        }
    }

    result_display->setText(output);
    statusBar()->showMessage("Algorithm completed.");
}

void MainWindow::run_all_algorithms()
{
    if (!graph_loaded) {
        QMessageBox::warning(this, "Warning", "Please load a graph file first!");
        return;
    }

    // Run Brute Force
    my_timer.start_timer();
    my_brute.calculate_route(my_matrix.matrix, my_matrix.city_count);
    my_timer.stop_timer();
    bf_time = my_timer.get_elapsed();
    bf_cost = my_brute.best_cost;

    // Run Greedy
    my_timer.start_timer();
    my_greedy.greedy_route(my_matrix.matrix, my_matrix.city_count, 0);
    my_timer.stop_timer();
    gr_time = my_timer.get_elapsed();
    gr_cost = my_greedy.total_cost;

    // Run Custom
    my_timer.start_timer();
    my_custom.improved_route(my_matrix.matrix, my_matrix.city_count);
    my_timer.stop_timer();
    cu_time = my_timer.get_elapsed();
    cu_cost = my_custom.best_cost;

    // Show best route (custom usually best)
    if (cu_cost != INF)
        my_graph_widget->set_route(my_custom.best_route, my_matrix.city_count);

    // Build output text
    QString output = "=== All Algorithms Run ===\n\n";

    output += "[1] Brute Force:\n";
    output += "    Cost: " + (bf_cost == INF ? QString("No route") : QString::number(bf_cost)) + "\n";
    output += "    Time: " + QString::number(bf_time, 'f', 6) + " sec\n\n";

    output += "[2] Greedy NN:\n";
    output += "    Cost: " + (gr_cost == INF ? QString("No route") : QString::number(gr_cost)) + "\n";
    output += "    Time: " + QString::number(gr_time, 'f', 6) + " sec\n\n";

    output += "[3] Custom Greedy:\n";
    output += "    Cost: " + (cu_cost == INF ? QString("No route") : QString::number(cu_cost)) + "\n";
    output += "    Time: " + QString::number(cu_time, 'f', 6) + " sec\n";

    result_display->setText(output);
    update_compare_table();
    statusBar()->showMessage("All algorithms completed.");
}

void MainWindow::update_compare_table()
{
    auto set_row = [this](int row, int cost, double time) {
        compare_table->item(row, 1)->setText(cost == INF ? "N/A" : QString::number(cost));
        compare_table->item(row, 2)->setText(QString::number(time, 'f', 6));
    };

    set_row(0, bf_cost, bf_time);
    set_row(1, gr_cost, gr_time);
    set_row(2, cu_cost, cu_time);

    // Highlight best cost row in green
    int best = bf_cost;
    if (gr_cost < best) best = gr_cost;
    if (cu_cost < best) best = cu_cost;
    int costs[3] = {bf_cost, gr_cost, cu_cost};
    for (int i = 0; i < 3; i++) {
        QColor row_color = (costs[i] == best && best != INF)
        ? QColor(200, 255, 200)
        : Qt::white;
        for (int j = 0; j < 3; j++)
            compare_table->item(i, j)->setBackground(row_color);
    }
}

void MainWindow::save_results()
{
    if (!graph_loaded) {
        QMessageBox::warning(this, "Warning", "No results to save!");
        return;
    }

    QString save_path = QFileDialog::getSaveFileName(
        this, "Save Results",
        "D:/TSP_GUI/TSP_GUI/output/results.txt",
        "Text Files (*.txt)"
        );

    if (save_path.isEmpty()) return;

    my_file_manager.save_results(
        save_path.toStdString(),
        bf_cost, my_brute.best_route,
        gr_cost, my_greedy.route,
        cu_cost, my_custom.best_route,
        my_matrix.city_count
        );

    QMessageBox::information(this, "Saved", "Results saved to:\n" + save_path);
    statusBar()->showMessage("Results saved.");
}

void MainWindow::clear_display()
{
    result_display->clear();
    my_graph_widget->clear_route();

    for (int i = 0; i < 3; i++) {
        compare_table->item(i, 1)->setText("-");
        compare_table->item(i, 2)->setText("-");
        for (int j = 0; j < 3; j++)
            compare_table->item(i, j)->setBackground(Qt::white);
    }

    bf_cost = gr_cost = cu_cost = 0;
    bf_time = gr_time = cu_time = 0.0;

    statusBar()->showMessage("Cleared.");
}
