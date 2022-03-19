# ImGui sources
file(GLOB_RECURSE IMGUI_SOURCES ImGui/imgui.cpp ImGui/imgui_widgets.cpp ImGui/imgui_draw.cpp ImGui/imgui_tables.cpp ImGui/imgui-SFML.cpp)

# Dimension3D sources
file(GLOB_RECURSE DIM_SOURCES Dimension3D/sources/*.cpp)

# Create library
add_library(Libraries STATIC ${IMGUI_SOURCES} ${DIM_SOURCES})

# Includes
target_include_directories(Libraries PUBLIC ImGui)
target_include_directories(Libraries PUBLIC Dimension3D/includes)

# linker flags
add_link_options(-lmingw32 -lgdi32 -luser32 -lkernel32 -ladvapi32 -lshell32 -lgcc -lmoldname -lmingwex -lmsvcrt -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32)

# SFML
if(MSVC)

	if(X64_BITS)
		set(LIB_SFML_PATH SFML/VS/x64)
	else()
		set(LIB_SFML_PATH SFML/VS/x86)
	endif()

elseif(MINGW)

	if(X64_BITS)
		set(LIB_SFML_PATH SFML/MinGW/x64)
	else()
		set(LIB_SFML_PATH SFML/MinGW/x86)
	endif()

elseif(APPLE)

	set(LIB_SFML_PATH SFML/Clang/x64)

else()

	set(LIB_SFML_PATH SFML/GCC/x64)

endif()

if(MINGW OR MSVC)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2.5.1 COMPONENTS REQUIRED system window graphics PATHS ${LIB_SFML_PATH})
target_link_libraries(Libraries PUBLIC sfml-system sfml-window sfml-graphics)

# GLM
target_include_directories(Libraries PUBLIC GLM)

# OpenGL
if (MINGW OR MSVC)
	add_definitions(-DGLEW_STATIC)
	add_subdirectory(GLEW EXCLUDE_FROM_ALL)
	target_link_libraries(Libraries PRIVATE libglew_static)
else()
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
	target_link_libraries(Libraries PUBLIC OpenGL::OpenGL GLEW::GLEW)
endif()
