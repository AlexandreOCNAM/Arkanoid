cmake_minimum_required(VERSION 3.7)

project(Arkanoid LANGUAGES C)

find_package(SDL2 CONFIG REQUIRED)

include_directories(public)


add_executable(${PROJECT_NAME}
		arkanoid.h
		arkanoid.h
		includes/ball.h
		src/ball.c
		includes/window.h)
target_sources(${PROJECT_NAME} PRIVATE arkanoid.c)

if (TARGET SDL2::SDL2)
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
else()
	target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main m)
endif()



file(COPY public/sprites.bmp
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)	

