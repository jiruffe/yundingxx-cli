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

#include "init.h"

#include <locale.h>

#include "../cli/cli.h"
#include "../game/game.h"

// 初始化全部
void
init_all() {
    // 允许中文
#if defined(__linux__)
    setlocale(LC_ALL, "zh_CN.UTF-8");
#elif defined(__unix__)
    setlocale(LC_ALL, "zh_CN.UTF-8");
#elif defined(_WIN32)
    setlocale(LC_ALL, "zh-CN");
#elif defined(_WIN64)
    setlocale(LC_ALL, "zh-CN");
#elif defined(__APPLE__)
    setlocale(LC_ALL, "zh_CN.UTF-8");
#else
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif
    // 初始化cli
    cli_init();
    // 初始化游戏
    game_init();
}

// 结束全部
void
deinit_all() {
    cli_deinit();
}
