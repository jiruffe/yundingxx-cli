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
cli_refreshAll() {
    touchwin(stdscr);
    refresh();
}

// 初始化
void
cli_init() {
    // 初始化ncurses
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
    cli_refreshAll();
}

// 结束
void
cli_deinit() {
    // 删除窗口
    delwin(win_holder.win_input);
    delwin(win_holder.win_output);
#ifdef YDXX_DEBUG
    delwin(win_holder.win_debug);
#endif
    // 关闭
    endwin();
}

// 清除输入窗口的回显
void
cli_clearWinInput() {
    wclear(win_holder.win_input);
    cli_refreshAll();
}

// 在输入窗口回显
void
cli_showInWinInput(const char *str) {
    cli_clearWinInput();
    wprintw(win_holder.win_input, str);
    cli_refreshAll();
}

// 从输入窗口读入输入
char
cli_readCharFromWinInput() {
    return wgetch(win_holder.win_input);
}

// 在输出窗口显示内容
void
cli_showInWinOutput(char dir, const char *str) {
    wprintw(win_holder.win_output, "%c %s\n", dir, str);
    cli_refreshAll();
}

#ifdef YDXX_DEBUG
// 在调试窗口显示内容
void
cli_showInWinDebug(char dir, const char *str) {
    wprintw(win_holder.win_debug, "%c %s\n", dir, str);
    cli_refreshAll();
}
#endif
