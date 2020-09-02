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

#include "../cli/cli.h"
#include "../api/api.h"

#ifndef YDXX_COMMAND_STRING_MAX_LENGTH
#define YDXX_COMMAND_STRING_MAX_LENGTH 1024
#endif

#ifndef YDXX_COMMAND_SEPARATOR
#define YDXX_COMMAND_SEPARATOR " "
#endif

#ifndef YDXX_COMMAND_KEY_PROCESS
#define YDXX_COMMAND_KEY_PROCESS '\n'
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
    char *original_string;
    size_t original_string_length;
    command_type_enum command_type;
    size_t argc;
    char **argv;
} command_t;

// 命令转换
static
int
cast_command(command_t *command, char *command_string) {
    command->original_string = command_string;
    command->original_string_length = strlen(command_string);
    // 用空格分割
    char *token = strtok(command_string, YDXX_COMMAND_SEPARATOR);
    // 确定命令类型
    if (!strcmp("quit", token)) {
        command->command_type = QUIT;
    } else if (!strcmp("login", token)) {
        command->command_type = LOGIN;
    } else {
        command->command_type = UNKNOWN;
    }
    // 参数
    command->argc = 0;
    while (token = strtok(NULL, YDXX_COMMAND_SEPARATOR)) {
        command->argv[command->argc++] = token;
    }
    return 0;
}

// 接收命令
void
receiving_and_processing_command() {

    char key;
    char tmp_key[2] = {0};
    char command_string[YDXX_COMMAND_STRING_MAX_LENGTH + 1] = {0};
    command_t *command = (command_t *) malloc(sizeof(command_t));
    command->argv = (char **) malloc(sizeof(char) * YDXX_COMMAND_ARG_MAX_QUANTITY * (YDXX_COMMAND_ARG_MAX_LENGTH + 1));

    while (true) {
        // 在最底下显示现在的命令内容
        show_in_win_input(command_string);
        // 读入输入
        key = read_c_from_win_input();
        if (!isprint(key)) {
            if (YDXX_COMMAND_KEY_PROCESS == key) {
                // 清空现在显示的输入
                clear_win_input();
                // 显示一行表示接收到命令
                show_in_win_output(YDXX_OUTPUT_DIRECTION_IN, command_string);
                // 处理命令
                cast_command(command, command_string);
                switch (command->command_type) {
                    case QUIT:
                        goto lb_exit;
                    case UNKNOWN:
                    default:
                        break;
                }
                // 最后清空字符串
                memset(command_string, 0, sizeof(command_string));
            }
            continue;
        }
        // 拼接到命令
        tmp_key[0] = key;
        strcat(command_string, tmp_key);
    }

    lb_exit:
    free(command->argv);
    free(command);

}

