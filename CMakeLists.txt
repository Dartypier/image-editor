# macros used by the app #
add_compile_definitions(APP_NAME="Editor Immagini")
add_compile_definitions(APP_VERSION="0.1.0")
##############################################################

cmake_minimum_required(VERSION 3.19)
project(image_editor)
set(CMAKE_CXX_STANDARD 11)

##QT Libs##
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Gui)
set(REQUIRED_LIBS_QUALIFIED Qt::Gui)

set(CMAKE_PREFIX_PATH "/home/jacopo/Qt/5.15.2/gcc_64/lib/cmake")
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
########################

set(SOURCES
        main.cpp
        Image.cpp
        Image.h
        utils.cpp
        utils.h
        Pixel.cpp
        Pixel.h
        CommandPattern/ICommand.h
        CommandPattern/grayScaleOptimizedCommand.cpp
        CommandPattern/grayScaleOptimizedCommand.h
        CommandPattern/CommandManager.cpp
        CommandPattern/CommandManager.h
        CommandPattern/Commands.h
        CommandPattern/colorMaskCommand.cpp
        CommandPattern/colorMaskCommand.h
        CommandPattern/flipXCommand.cpp
        CommandPattern/flipXCommand.h
        CommandPattern/flipYCommand.cpp
        CommandPattern/flipYCommand.h
        CommandPattern/flip90SxCommand.cpp
        CommandPattern/flip90SxCommand.h
        CommandPattern/flip90DxCommand.cpp
        CommandPattern/flip90DxCommand.h
        CommandPattern/contrastCommand.cpp
        CommandPattern/contrastCommand.h
        CommandPattern/brightnessCommand.cpp
        CommandPattern/brightnessCommand.h
        CommandPattern/scaleCommand.cpp
        CommandPattern/scaleCommand.h
        CommandPattern/blurCommand.cpp
        CommandPattern/blurCommand.h
        CommandPattern/sharpenCommand.cpp
        CommandPattern/sharpenCommand.h
        CommandPattern/edgeDetectCommand.cpp
        CommandPattern/edgeDetectCommand.h
        CommandPattern/embossCommand.cpp
        CommandPattern/embossCommand.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

#### add GTest
add_library(core ${SOURCES})
target_link_libraries(core ${REQUIRED_LIBS_QUALIFIED})
add_subdirectory(test)
