/*
 *    MIT License
 *
 *    Copyright (c) 2020 Jiruffe
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */

#include "cli.h"

#include <ncurses.h>

#include "../config.h"

static struct win_holder {
    WINDOW *win_input;
    WINDOW *win_output;
#ifdef YDXX_DEBUG
    WINDOW *win_debug;
#endif
} win_holder;

// 刷新全部显示
static
void
refresh_all() {
    touchwin(stdscr);
    refresh();
}

// 初始化ncurses
void
init_ncurses() {
    // 初始化
    initscr();
    // 禁用行缓冲、禁用CTRL+C
    raw();
    // 禁用默认回显
    noecho();
    // 禁用光标显示
    curs_set(0);
    // 创建各个窗口
    win_holder.win_input = subwin(stdscr, 1, COLS, LINES - 1, 0);
#ifdef YDXX_DEBUG
    win_holder.win_output = subwin(stdscr, LINES - 1, COLS / 2, 0, 0);
    win_holder.win_debug = subwin(stdscr, LINES - 1, COLS / 2, 0, COLS / 2);
#else
    win_holder.win_output = subwin(stdscr, LINES - 1, COLS, 0, 0);
#endif
    // 刷新
    refresh_all();
}

// 结束ncurses
void
deinit_ncurses() {
    delwin(win_holder.win_input);
    delwin(win_holder.win_output);
#ifdef YDXX_DEBUG
    delwin(win_holder.win_debug);
#endif
    endwin();
}

// 清除输入窗口的回显
void
clear_win_input() {
    wclear(win_holder.win_input);
    refresh_all();
}

// 在输入窗口回显
void
show_in_win_input(const char *str) {
    clear_win_input();
    wprintw(win_holder.win_input, str);
    refresh_all();
}

// 从输入窗口读入输入
char
read_c_from_win_input() {
    return wgetch(win_holder.win_input);
}

// 在输出窗口显示内容
void
show_in_win_output(char dir, const char *str) {
    wprintw(win_holder.win_output, "%c %s\n", dir, str);
    refresh_all();
}

#ifdef YDXX_DEBUG
// 在调试窗口显示内容
void
show_in_win_debug(char dir, const char *str) {
    wprintw(win_holder.win_debug, "%c %s\n", dir, str);
    refresh_all();
}
#endif
