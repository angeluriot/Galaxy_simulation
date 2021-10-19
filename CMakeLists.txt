cmake_minimum_required(VERSION 3.10)

# Project
project(Galaxy_simulation)

# Sources
file(GLOB_RECURSE SOURCES sources/*.cpp)
file(GLOB_RECURSE HEADERS includes/*.hpp includes/*.h)

if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# C++ 17
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC includes)

# linker flags
add_link_options(-lmingw32 -lgdi32 -luser32 -lkernel32 -ladvapi32 -lshell32 -lgcc -lmoldname -lmingwex -lmsvcrt -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32)

# Set VS properties
if(MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus")
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	set_property(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()

# libraries
add_subdirectory(libraries)
target_link_libraries(${PROJECT_NAME} PUBLIC Libraries)

if(UNIX)
	# Find CUDA for OpenCL headers (optional, for Nvidia GPU only)
	find_package(CUDA 11.0)

	if (CUDA_FOUND)
		include_directories(${CUDA_INCLUDE_DIRS})
	endif()

	# Pthreads
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif()

# OpenCL
find_package(OpenCL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenCL::OpenCL)

# Dimension3D
target_include_directories(${PROJECT_NAME} PUBLIC libraries/Dimension3D/includes)

# SFML
if(MSVC)

	if(X64_BITS)
		set(SFML_PATH libraries/SFML/VS/x64)
	else()
		set(SFML_PATH libraries/SFML/VS/x86)
	endif()

elseif(MINGW)

	if(X64_BITS)
		set(SFML_PATH libraries/SFML/MinGW/x64)
	else()
		set(SFML_PATH libraries/SFML/MinGW/x86)
	endif()

elseif(APPLE)

	set(SFML_PATH libraries/SFML/Clang/x64)

else()

	set(SFML_PATH libraries/SFML/GCC/x64)

endif()

if(MINGW OR MSVC)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2.5.1 COMPONENTS REQUIRED system window graphics PATHS ${SFML_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-system sfml-window sfml-graphics)

# GLM
target_include_directories(${PROJECT_NAME} PUBLIC libraries/GLM)

# OpenGL
if (MINGW OR MSVC)
	add_definitions(-DGLEW_STATIC)
	target_link_libraries(${PROJECT_NAME} PRIVATE libglew_static)
else()
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::OpenGL GLEW::GLEW)
endif()

# Copy resources and shaders sur binary directory
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
