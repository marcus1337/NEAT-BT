cmake_minimum_required(VERSION 3.1)

project(pingsim)
set (CMAKE_CXX_STANDARD 14)

include_directories(".")

add_executable(${PROJECT_NAME}
    "Main.cpp"
    "Breeder.cpp"
    "Breeder.h"
	"Coordinator.cpp"
    "Coordinator.h"
	"Culler.cpp"
    "Culler.h"
	"Evolver.cpp"
    "Evolver.h"
	"GenerationInfo.cpp"
    "GenerationInfo.h"
	"IOHandler.cpp"
    "IOHandler.h"
	"Mutate.cpp"
    "Mutate.h"
	"Node.cpp"
    "Node.h"
	"Speciator.cpp"
    "Speciator.h"
	"Specie.cpp"
    "Specie.h"
	"Tree.cpp"
    "Tree.h"
	"TreeIterator.cpp"
    "TreeIterator.h"
	"Utils.cpp"
    "Utils.h"
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
else()
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)