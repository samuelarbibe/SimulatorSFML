cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME "AI_TMS")

project(${PROJECT_NAME} VERSION 1.0.0 DESCRIPTION "Artificially-intelligent traffic managent system" LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

##############################  Qt  ###################################
set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt/5.15.0)
find_package(Qt5 COMPONENTS Core Gui Widgets Charts PrintSupport REQUIRED)

#############################  SFML  ##################################
set(SFML_DIR /usr/local/Cellar/sfml/2.5.1)
find_package(SFML COMPONENTS system window graphics REQUIRED)

set(project_sources
        public/qcustomplot.cpp
        src/sim/simulator/Engine.cpp
        src/sim/map/Intersection.cpp
        src/sim/map/Lane.cpp
        src/main.cpp
        src/sim/map/Road.cpp
        src/sim/simulator/Vehicle.cpp
        src/sim/map/Map.cpp
        src/ui/widgets/QsfmlCanvas.cpp
        src/sim/simulator/Settings.cpp
        src/ui/mainwindow.cpp
        src/sim/simulator/DataBox.cpp
        src/sim/simulator/DataBox.hpp
        src/sim/map/Route.cpp
        src/sim/map/Route.hpp
        src/sim/map/Phase.cpp
        src/sim/map/Phase.hpp
        src/sim/map/Light.cpp
        src/sim/map/Light.hpp
        src/sim/simulator/Simulation.cpp
        src/sim/simulator/Simulation.hpp
        src/ui/widgets/SimModel.cpp
        src/ui/widgets/SimModel.hpp
        src/sim/map/Cycle.cpp
        src/sim/map/Cycle.hpp
        src/sim/simulator/Set.cpp
        src/sim/simulator/Set.hpp
        src/sim/neural_network/NeuralNet.cpp
        src/sim/neural_network/NeuralNet.hpp
        src/sim/neural_network/Neuron.cpp
        src/sim/neural_network/Neuron.hpp
        )

set(project_headers
        resources/fonts/Roboto/Roboto-Bold.ttf
        public/json.hpp
        public/qcustomplot.h
        src/sim/simulator/Engine.hpp
        src/sim/map/Intersection.hpp
        src/sim/map/Lane.hpp
        src/sim/map/Road.hpp
        src/sim/simulator/Vehicle.hpp
        src/sim/map/Map.hpp
        src/ui/widgets/QsfmlCanvas.hpp
        src/ui/mainwindow.h
        src/sim/simulator/Settings.hpp
        src/sim/simulator/DataBox.cpp
        src/sim/simulator/DataBox.hpp
        src/sim/map/Route.cpp
        src/sim/map/Route.hpp
        src/sim/map/Phase.cpp
        src/sim/map/Phase.hpp
        src/sim/map/Light.cpp
        src/sim/map/Light.hpp
        src/sim/simulator/Simulation.cpp
        src/sim/simulator/Simulation.hpp
        src/ui/widgets/SimModel.cpp
        src/ui/widgets/SimModel.hpp
        src/sim/map/Cycle.cpp
        src/sim/map/Cycle.hpp
        src/sim/simulator/Set.cpp
        src/sim/simulator/Set.hpp
        src/sim/neural_network/NeuralNet.cpp
        src/sim/neural_network/NeuralNet.hpp
        src/sim/neural_network/Neuron.cpp
        src/sim/neural_network/Neuron.hpp
        )

set(project_ui ${PROJECT_SOURCE_DIR}/src/ui/mainwindow.ui)
# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})

add_executable(${PROJECT_NAME}
        ${project_sources}
        ${project_headers}
        ${ui_wrap}
        ${moc_sources}
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        sfml-graphics
        sfml-window
        sfml-system

        Qt5::Widgets
        Qt5::PrintSupport
        Qt5::Core
        Qt5::Charts
        Qt5::Gui
        )


#install(TARGETS TMS DESTINATION bin)
