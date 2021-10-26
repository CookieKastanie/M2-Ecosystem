cmake_minimum_required(VERSION 3.1.0)
project("Ecosystem")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/include")

## Files
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
#file(GLOB_RECURSE HEADER CONFIGURE_DEPENDS "${INC_DIR}/${PROJECT_NAME}/*.hpp")

#add_executable(${PROJECT_NAME} ${SRC} ${HEADER})
add_executable(${PROJECT_NAME})
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp
src/Terrain.cpp "include/Ecosystem/Vegetal.hpp" "src/Animal.cpp" "src/Vegetal.cpp" "src/Random.cpp" "include/Ecosystem/Entity.hpp" "src/Entity.cpp" "include/Ecosystem/Cell.hpp" "src/Cell.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})


#lib externe
add_subdirectory(Akila)
target_link_libraries(${PROJECT_NAME} PUBLIC Akila)
