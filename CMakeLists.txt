cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(GalaxyDimensionOpti CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(includes ${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

set(SOURCES
	sources/main.cpp
	sources/star.cpp
	sources/block.cpp
	sources/utils.cpp
	sources/vector.cpp

	includes/block.h
	includes/star.h
	includes/utils.h
	includes/vector.h)

set(COMPILE_OPTIONS
	-pipe
	-march=native
	-Wall
	-Wextra
	-Winline
	-Wno-inline
	-pedantic
	-fno-fast-math
	-funroll-loops
	-flto
	-fuse-ld=gold
	-fuse-linker-plugin)

set(LINKER_OPTIONS
	-Wl,--sort-common,--as-needed
	-flto
	-fuse-ld=gold
	-fuse-linker-plugin)

set(LINKER_FLAGS
	stdc++)

add_executable(GalDimOpti ${SOURCES})
target_compile_definitions(GalDimOpti PRIVATE $<$<CONFIG:DEBUG>:_GLIBCXX_DEBUG>)
target_compile_options(GalDimOpti PRIVATE ${COMPILE_OPTIONS})
target_link_options(GalDimOpti PRIVATE ${LINKER_OPTIONS})
target_link_libraries(GalDimOpti ${LINKER_FLAGS} ${SDL2_LIBRARIES} pthread)