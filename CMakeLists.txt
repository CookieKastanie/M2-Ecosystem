cmake_minimum_required(VERSION 3.1.0)
project("Ecosystem")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/include")

## Files
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")

if(WIN32)
    set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icon/ecosystem.rc)
endif()

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON} src/main.cpp
"include/Ecosystem/simulation/Simulation.hpp" "src/simulation/Simulation.cpp" "src/simulation/Terrain.cpp" "include/Ecosystem/entities/Vegetal.hpp" "src/entities/Animal.cpp" "src/entities/Vegetal.cpp" "src/utils/Random.cpp" "include/Ecosystem/entities/Entity.hpp" "src/entities/Entity.cpp" "include/Ecosystem/simulation/Cell.hpp" "src/simulation/Cell.cpp" "include/Ecosystem/app/MouseCamera.hpp" "src/app/MouseCamera.cpp" "include/Ecosystem/app/AppLayer.hpp" "src/app/AppLayer.cpp" "include/Ecosystem/entities/Bunny.hpp" "include/Ecosystem/entities/Fox.hpp" "src/entities/Bunny.cpp" "src/entities/Fox.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})

if(WIN32)
    set_target_properties(${PROJECT_NAME}
    PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
               LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

#lib externe
add_subdirectory(Akila)
target_link_libraries(${PROJECT_NAME} PUBLIC Akila)

#Copy resources
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
