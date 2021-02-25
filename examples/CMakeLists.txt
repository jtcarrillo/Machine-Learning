cmake_minimum_required(VERSION 3.5)

project(csv_reader C CXX)

add_executable(${PROJECT_NAME} csv_reader.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ../extern/)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
