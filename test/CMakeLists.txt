cmake_minimum_required(VERSION 3.19)

add_subdirectory(./lib/)
set(gtest_SOURCE_DIR ./lib/gooltest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_TEST_FILE
        runAll.cpp ImageTest.cpp utilsTest.cpp TestPixel.cpp TestCommandManager.cpp)

add_executable(runAllTests ${SOURCE_TEST_FILE})
target_link_libraries(runAllTests gtest gtest_main core)