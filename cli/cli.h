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

#include <wctype.h>

#include "../config.h"

#ifndef YUNDINGXX_CLI_CLI_H
#define YUNDINGXX_CLI_CLI_H

#ifndef YDXX_OUTPUT_DIRECTION_IN
#define YDXX_OUTPUT_DIRECTION_IN L'<'
#endif

#ifndef YDXX_OUTPUT_DIRECTION_OUT
#define YDXX_OUTPUT_DIRECTION_OUT L'>'
#endif

// 初始化
void
cli_init();

// 结束
void
cli_deinit();

// 清除输入窗口
void
cli_clearWinInput();

// 从输入窗口读入输入
void
cli_readStringFromWinInput(wint_t *dest);

// 在输出窗口显示内容
void
cli_showInWinOutput(wint_t dir, const wint_t *str);

#ifdef YDXX_DEBUG
// 在调试窗口显示内容
void
cli_showInWinDebug(const wint_t *str);
#endif

#endif //YUNDINGXX_CLI_CLI_H
