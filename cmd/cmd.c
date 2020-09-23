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

#include "cmd.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <wctype.h>
#include <wchar.h>

#include "../config.h"
#include "../cli/cli.h"
#include "../api/api.h"
#include "../gnl/gnl.h"

#ifndef YDXX_COMMAND_STRING_MAX_LENGTH
#define YDXX_COMMAND_STRING_MAX_LENGTH 1024
#endif

#ifndef YDXX_COMMAND_SEPARATOR
#define YDXX_COMMAND_SEPARATOR L" "
#endif

#ifndef YDXX_COMMAND_ARG_MAX_QUANTITY
#define YDXX_COMMAND_ARG_MAX_QUANTITY 8
#endif

#ifndef YDXX_COMMAND_ARG_MAX_LENGTH
#define YDXX_COMMAND_ARG_MAX_LENGTH 128
#endif

// 命令类型枚举
typedef
enum COMMAND_TYPE_ENUM {
    UNKNOWN,
    QUIT,
    LOGIN,
} command_type_enum;

// 命令结构
typedef
struct COMMAND {
    wchar_t *original_string;
    size_t original_string_length;
    command_type_enum command_type;
    size_t argc;
    wchar_t argv[YDXX_COMMAND_ARG_MAX_QUANTITY][YDXX_COMMAND_ARG_MAX_LENGTH];
} command_t;

// 初始化
void
cmd_init() {
    cli_showInWinOutput(L"%c yundingxx-cli\n"
                                                   "  云顶修仙命令行版\n"
                                                   "  version: 1.0\n"
                                                   "  https://github.com/jiruffe/yundingxx-cli\n"
                                                   "  \n"
                                                   "  命令用法:\n"
                                                   "  \n"
                                                   "  quit\n"
                                                   "  退出\n"
                                                   "  \n"
                                                   "  login <username> <password>\n"
                                                   "  登录\n"
                                                   "  ", YDXX_OUTPUT_DIRECTION_OUT);
}

// 命令转换
static
int
cmd_castCommand(command_t *command, wchar_t *command_string) {
    command->original_string = command_string;
    command->original_string_length = wcslen(command_string);
    // 用空格分割
    wchar_t *buffer;
    wchar_t *token = wcstok(command_string, YDXX_COMMAND_SEPARATOR, &buffer);
    // 确定命令类型
    if (!wcscmp(L"quit", token)) {
        command->command_type = QUIT;
    } else if (!wcscmp(L"login", token)) {
        command->command_type = LOGIN;
    } else {
        command->command_type = UNKNOWN;
    }
    // 参数
    command->argc = 0;
    while (token = wcstok(NULL, YDXX_COMMAND_SEPARATOR, &buffer)) {
        wcscpy(command->argv[command->argc], token);
        command->argc++;
    }
    return 0;
}

// 接收命令
void
cmd_receivingAndProcessingCommand() {

    wchar_t command_string[YDXX_COMMAND_STRING_MAX_LENGTH + 1] = {0};
    command_t *command = (command_t *) malloc(sizeof(command_t));

    while (true) {
        // 读入输入
        cli_readStringFromWinInput(command_string);
        if (wcslen(command_string)) {
            // 显示一行表示接收到命令
            cli_showInWinOutput(L"%c %ls", YDXX_OUTPUT_DIRECTION_IN, command_string);
            // 处理命令
            cmd_castCommand(command, command_string);
            switch (command->command_type) {
                case QUIT: {
                    goto lb_exit;
                }
                case LOGIN: {
                    if (command->argc != 2) {
                        cli_showInWinOutput(L"%c Error: LOGIN Expected 2 arguments but received %u!", YDXX_OUTPUT_DIRECTION_OUT, command->argc);
                        break;
                    }
                    break;
                }
                case UNKNOWN:
                default: {
                    cli_showInWinOutput(L"%c Unknown command!", YDXX_OUTPUT_DIRECTION_OUT);
                    break;
                }
            }
            // 最后清空字符串
            memset(command_string, 0, sizeof(command_string));
        }
    }

    lb_exit:
    free(command);

}

