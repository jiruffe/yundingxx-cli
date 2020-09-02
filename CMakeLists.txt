cmake_minimum_required(VERSION 3.17)
project(yundingxx_cli C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(yundingxx_cli main.c api/api.h api/api.c cli/cli.h cli/cli.c cmd/cmd.h cmd/cmd.c init/init.c init/init.h config.h game/game.c game/game.h gnl/gnl.c gnl/gnl.h)
target_link_libraries(yundingxx_cli ${CURSES_LIBRARIES})
