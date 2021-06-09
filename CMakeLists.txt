# macros used by the app #
add_compile_definitions(APP_NAME="Image Editor")
add_compile_definitions(APP_VERSION="1.0.0")
##############################################################

cmake_minimum_required(VERSION 3.19)
project(image_editor)
set(CMAKE_CXX_STANDARD 11)

##QT Libs##
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt::Gui Qt::Widgets)

set(CMAKE_PREFIX_PATH "/home/jacopo/Qt/5.15.2/gcc_64/lib/cmake")
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
########################

set(BACKEND
        backend/main.cpp
        backend/Image.cpp
        backend/Image.h
        backend/utils.cpp
        backend/utils.h
        backend/Pixel.cpp
        backend/Pixel.h
        backend/CommandPattern/ICommand.h
        backend/CommandPattern/grayScaleCommand.cpp
        backend/CommandPattern/grayScaleCommand.h
        backend/CommandPattern/CommandManager.cpp
        backend/CommandPattern/CommandManager.h
        backend/CommandPattern/Commands.h
        backend/CommandPattern/colorMaskCommand.cpp
        backend/CommandPattern/colorMaskCommand.h
        backend/CommandPattern/flipXCommand.cpp
        backend/CommandPattern/flipXCommand.h
        backend/CommandPattern/flipYCommand.cpp
        backend/CommandPattern/flipYCommand.h
        backend/CommandPattern/rotateAntiClockwiseCommand.cpp
        backend/CommandPattern/rotateAntiClockwiseCommand.h
        backend/CommandPattern/rotateClockwiseCommand.cpp
        backend/CommandPattern/rotateClockwiseCommand.h
        backend/CommandPattern/contrastCommand.cpp
        backend/CommandPattern/contrastCommand.h
        backend/CommandPattern/brightnessCommand.cpp
        backend/CommandPattern/brightnessCommand.h
        backend/CommandPattern/scaleCommand.cpp
        backend/CommandPattern/scaleCommand.h
        backend/CommandPattern/blurCommand.cpp
        backend/CommandPattern/blurCommand.h
        backend/CommandPattern/sharpenCommand.cpp
        backend/CommandPattern/sharpenCommand.h
        backend/CommandPattern/edgeDetectCommand.cpp
        backend/CommandPattern/edgeDetectCommand.h
        backend/CommandPattern/embossCommand.cpp
        backend/CommandPattern/embossCommand.h
        backend/CommandPattern/utils.cpp
        backend/CommandPattern/utils.h)

set(FRONTEND
        frontend/MainWindow.cpp
        frontend/MainWindow.h
        frontend/MainWindow.ui
        frontend/resources.qrc
        frontend/InputDialog.cpp
        frontend/InputDialog.h)

add_executable(${PROJECT_NAME} ${BACKEND} ${FRONTEND})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

#### add GTest
add_library(core ${BACKEND})
target_link_libraries(core ${REQUIRED_LIBS_QUALIFIED})
add_subdirectory(backend/test)
