file(GLOB LinHop_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DGLEW_STATIC)
set(GLEW_STATIC_LIBRARIES TRUE)

set(TARGET_NAME "LinHop")

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/${TARGET_NAME}/bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(${TARGET_NAME} ${LinHop_SRC})

add_custom_target(copy_assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${TARGET_NAME}/res ${CMAKE_SOURCE_DIR}/${TARGET_NAME}/bin/res
)
add_dependencies(${TARGET_NAME} copy_assets)

target_link_options(${TARGET_NAME} PRIVATE /SUBSYSTEM:WINDOWS)

target_link_libraries(${TARGET_NAME}
	glew32s
	glfw3
	opengl32
	User32
	Gdi32
	Shell32
	glm
	stb_image
	freetype
	sndfile
	portaudio
)
