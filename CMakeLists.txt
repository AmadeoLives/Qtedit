cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_NAME Qtedit)

project(${TARGET_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAXE_CXX_COMPILER g++)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core )
find_package(Qt6 REQUIRED )

qt_standard_project_setup()

FILE(GLOB CXXSRC src/*.cpp)
FILE(GLOB HEADERSRC src/*.h)

qt_add_executable(${TARGET_NAME}
    ${CXXSRC}
    ${HEADERSRC}
)

qt_add_resources(${TARGET_NAME} "images"
    PREFIX "/"
    FILES 
)

target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic-errors)

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Widgets )
