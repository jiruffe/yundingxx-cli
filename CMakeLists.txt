cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_STANDARD 99)
set(PROJECT_NAME yundingxx_cli)
project(${PROJECT_NAME} C)

include(FindPkgConfig)
pkg_check_modules(PKGS REQUIRED ncurses libuv libevent openssl libwebsockets)

include_directories(${PKGS_INCLUDE_DIRS})
link_directories(${PKGS_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} main.c api/api.c cli/cli.c cmd/cmd.c game/game.c gnl/gnl.c init/init.c)

target_link_libraries(${PROJECT_NAME} ${PKGS_LDFLAGS})
