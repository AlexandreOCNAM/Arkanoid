cmake_minimum_required(VERSION 3.7)

project(Arkanoid LANGUAGES C)

find_package(SDL2 CONFIG REQUIRED)

include_directories(public)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm")

add_executable(${PROJECT_NAME}
		arkanoid.h
		arkanoid.h
		src/ball.c
		src/paddle.c
		src/ball.h
		src/graphics.c
		src/graphics.h
		src/paddle.c
		src/paddle.h
		src/brick.c
		src/brick.h
		src/brick.h
		src/paddle.h
		src/graphics.c
		src/graphics.c
		src/collisions.c
		src/collisions.h)
target_sources(${PROJECT_NAME} PRIVATE arkanoid.c)

if (TARGET SDL2::SDL2)
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main m)
else()
	target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main m)
endif()


file(COPY public/sprites.bmp
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY public/Arkanoid_sprites.bmp
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

