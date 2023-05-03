/*
    getpass.h - Password-masked input in a single header.

    The MIT License (MIT)

    Copyright © 2023 Matthew MacGregor

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this  software and  associated documentation files  (the “Software”), to
    deal in the Software without restriction,  including without limitation the
    rights to  use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the  Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above  copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED “AS IS”,  WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING  BUT NOT LIMITED TO THE  WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS  BE LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef GETPASS_H
#define GETPASS_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <termios.h>
#include <unistd.h>
#define GETPASS_IS_POSIX
#endif

#if defined _WIN32 || _WIN64 || __CYGWIN__
#include <windows.h>
#define GETPASS_IS_WINDOWS
#endif

#include <stdio.h>
#include <string.h>

/// definitions

size_t
gpwd_get_password(char *password, size_t max_password_len);

/// implementation
#ifdef GETPASS_IMPL

#ifdef GETPASS_IS_POSIX
static inline int
gpwd_getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}
#endif

size_t
gpwd_get_password(char *password, size_t max_password_len) {
#ifdef GETPASS_IS_WINDOWS
    // Windows
    const char BACKSPACE = 8;
    const char RETURN = 13;
#else
    // Unix/Linux/POSIX
    const char BACKSPACE = 127;
    const char RETURN = 10;
#endif
    unsigned char character = 0;

    memset(password, 0, max_password_len);
    size_t idx = 0;

#ifdef GETPASS_IS_WINDOWS
    // Windows
    DWORD console_mode;
    DWORD dw_read;

    HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(h_in, &console_mode);
    SetConsoleMode(h_in, console_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while(ReadConsoleA(h_in, &character, 1, &dw_read, NULL) && character != RETURN && idx < max_password_len) {
#else
    // Unix/Linux/POSIX
    while((character = gpwd_getch()) != RETURN && idx < max_password_len) {
#endif
        if(character == BACKSPACE) {
            password[--idx] = 0;
        } else {
            password[idx] = character;
            idx++;
        }
    }

    // null terminate the string
    password[idx] = 0;
    return idx - 1;
}

#ifdef GETPASS_MAIN
int main(int argc, char **argv) {
    #define MAX_LEN 256
    char password[MAX_LEN];
    gpwd_get_password(password, MAX_LEN);
    printf("Password = '%s'\n", password);
    return 0;
}
#endif

#endif // GETPASS_IMPL

#ifdef __cplusplus
}
#endif

#endif // GETPASS_H