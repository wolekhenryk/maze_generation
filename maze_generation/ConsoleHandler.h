#pragma once

#include <Windows.h>
#include <iostream>

class ConsoleHandler {
 public:
  static void resize_console(const int rows, const int cols) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the screen buffer size
    COORD bufferSize;
    bufferSize.X = cols;
    bufferSize.Y = rows;
    SetConsoleScreenBufferSize(consoleHandle, bufferSize);

    // Set the console window size
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = cols - 1;
    windowSize.Bottom = rows - 1;
    SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize);
  }

  static void draw_pixel(const int x,
                         const int y,
                         const char pixelChar,
                         const WORD color) {
    gotoxy(x, y);
    set_text_color(color);
    std::cout << pixelChar << pixelChar;
    reset_text_color();
  }

  static void gotoxy(const int y, const int x) {
    COORD cursorCoord;
    cursorCoord.X = x * 2;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorCoord);
  }

  static void clrscr() {
    const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    constexpr COORD scrollOffset = {0, 0};
    SMALL_RECT scrollRect;
    CHAR_INFO fill;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = screenBufferInfo.dwSize.X - 1;
    scrollRect.Bottom = screenBufferInfo.dwSize.Y - 1;
    fill.Char.AsciiChar = ' ';
    fill.Attributes = screenBufferInfo.wAttributes;
    ScrollConsoleScreenBuffer(consoleHandle, &scrollRect, nullptr, scrollOffset,
                              &fill);
    gotoxy(0, 0);
  }

  static void set_text_color(const WORD color) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
    WORD attributes = screenBufferInfo.wAttributes;
    attributes &= ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
                    BACKGROUND_INTENSITY);
    attributes |= color;
    SetConsoleTextAttribute(consoleHandle, attributes);
  }

  static void reset_text_color() {
    set_text_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
  }
};
