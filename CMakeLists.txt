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
"src/simulation/Terrain.cpp" "include/Ecosystem/entities/Vegetal.hpp" "src/entities/Animal.cpp" "src/entities/Vegetal.cpp" "src/utils/Random.cpp" "include/Ecosystem/entities/Entity.hpp" "src/entities/Entity.cpp" "include/Ecosystem/simulation/Cell.hpp" "src/simulation/Cell.cpp" "include/Ecosystem/app/MouseCamera.hpp" "src/app/MouseCamera.cpp" "include/Ecosystem/app/AppLayer.hpp" "src/app/AppLayer.cpp" "include/Ecosystem/entities/Bunny.hpp" "include/Ecosystem/entities/Fox.hpp" "src/entities/Bunny.cpp" "src/entities/Fox.cpp")
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
