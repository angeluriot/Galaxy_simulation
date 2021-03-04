cmake_minimum_required(VERSION 3.10)

project(Galaxy_simulation)

file(GLOB PROJ_SRC
    "sources/*.cpp"
    "includes/*.h"
)

# Ajout de flags d'optimisation: -O3 et -march=native, -pthread pour les threads sous linux, -std=c++11 pour la norme C++11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -march=native -O3")

if ((NOT DEFINED VCPKG_TARGET_TRIPLET) AND ("${CMAKE_CXX_COMPILER}" MATCHES  g\\+\\+\\.exe) AND (${CMAKE_SIZEOF_VOID_P} EQUAL 4))
    message("Configuiration pour MinGW 32")
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/dependencies/SFML/lib/cmake/SFML" CACHE FILEPATH "The directory containing a CMake configuration file for SFML.")
endif()

add_executable(Galaxy_simulation ${PROJ_SRC})
target_include_directories(Galaxy_simulation PRIVATE ${CMAKE_SOURCE_DIR}/includes)

find_package(SFML COMPONENTS system window graphics REQUIRED)
target_link_libraries(Galaxy_simulation PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
 #       sfml-main
    )
target_include_directories(Galaxy_simulation PRIVATE ${SFML_INCLUDE_DIR} sfml-graphics sfml-window sfml-network sfml-system)