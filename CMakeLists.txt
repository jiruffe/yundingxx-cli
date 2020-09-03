cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME yundingxx_cli)
project(${PROJECT_NAME} C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
find_package(libwebsockets REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS} ${LIBWEBSOCKETS_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.c api/api.c cli/cli.c cmd/cmd.c init/init.c game/game.c gnl/gnl.c)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} ${LIBWEBSOCKETS_LIBRARIES})
