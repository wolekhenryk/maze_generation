#pragma once

#include <Windows.h>
#include <iostream>

class ConsoleHandler {
 public:
  static void set_console_utf8_encoding() {
    // Get the current console's output handle
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the console mode to enable UTF-8 encoding
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Set the console output mode to handle UTF-8 characters
    DWORD consoleMode;
    GetConsoleMode(consoleHandle, &consoleMode);
    SetConsoleMode(consoleHandle,
                   consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
  }

  static void resize_console(const int rows, const int cols) {
    const HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the screen buffer size
    COORD
    buffer_size;
    buffer_size.X = cols;
    buffer_size.Y = rows;
    SetConsoleScreenBufferSize(console_handle, buffer_size);

    // Set the console window size
    SMALL_RECT window_size;
    window_size.Left = 0;
    window_size.Top = 0;
    window_size.Right = cols - 1;
    window_size.Bottom = rows - 1;
    SetConsoleWindowInfo(console_handle, TRUE, &window_size);
  }

  static void draw_pixel(const int x,
                         const int y,
                         const char pixel_char,
                         const WORD color) {
    gotoxy(x, y);
    set_text_color(color);
    std::cout << pixel_char << pixel_char;
    reset_text_color();
  }

  static void gotoxy(const int y, const int x) {
    COORD cursor_coord;
    cursor_coord.X = x * 2;
    cursor_coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_coord);
  }

  static void clrscr() {
    const HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    constexpr COORD scroll_offset = {0, 0};
    SMALL_RECT scroll_rect;
    CHAR_INFO fill;
    GetConsoleScreenBufferInfo(console_handle, &screen_buffer_info);
    scroll_rect.Left = 0;
    scroll_rect.Top = 0;
    scroll_rect.Right = screen_buffer_info.dwSize.X - 1;
    scroll_rect.Bottom = screen_buffer_info.dwSize.Y - 1;
    fill.Char.AsciiChar = ' ';
    fill.Attributes = screen_buffer_info.wAttributes;
    ScrollConsoleScreenBuffer(console_handle, &scroll_rect, nullptr,
                              scroll_offset, &fill);
    gotoxy(0, 0);
  }

  static void set_text_color(const WORD color) {
    const HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(console_handle, &screen_buffer_info);
    WORD attributes = screen_buffer_info.wAttributes;
    attributes &= ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
                    BACKGROUND_INTENSITY);
    attributes |= color;
    SetConsoleTextAttribute(console_handle, attributes);
  }

  static void set_fore_color(const WORD foreground_color) {
    const HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(console_handle, &screen_buffer_info);
    WORD attributes = screen_buffer_info.wAttributes;
    attributes &= ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
                    BACKGROUND_INTENSITY);
    attributes |= foreground_color;
    SetConsoleTextAttribute(console_handle, attributes);
  }

  static void reset_text_color() {
    set_text_color(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
  }

  static void setCursorPosition(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
  }

  static void display_string_at_position(const std::string& str, int x, int y) {
    setCursorPosition(x, y);
    DWORD numCharsWritten;
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), str.c_str(), str.length(),
                 &numCharsWritten, nullptr);
  }
};
