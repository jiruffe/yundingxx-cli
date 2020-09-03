cmake_minimum_required(VERSION 3.17)
project(yundingxx_cli C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(yundingxx_cli main.c api/api.c cli/cli.c cmd/cmd.c init/init.c game/game.c gnl/gnl.c)
target_link_libraries(yundingxx_cli ${CURSES_LIBRARIES})
