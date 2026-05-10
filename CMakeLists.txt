cmake_minimum_required(VERSION 3.19)
project(TSP_GUI LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(TSP_GUI
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    graph_widget.h
    graph_widget.cpp
    graph_matrix.h
    graph_matrix.cpp
    graph_list.h
    graph_list.cpp
    tsp_brute_force.h
    tsp_brute_force.cpp
    tsp_greedy.h
    tsp_greedy.cpp
    tsp_custom.h
    tsp_custom.cpp
    performance.h
    performance.cpp
    file_manager.h
    file_manager.cpp
    helper_functions.h
    helper_functions.cpp
)

target_link_libraries(TSP_GUI
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

include(GNUInstallDirs)

install(TARGETS TSP_GUI
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TSP_GUI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
