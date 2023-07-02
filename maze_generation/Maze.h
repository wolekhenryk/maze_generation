#pragma once

#include <chrono>
#include <functional>
#include <random>
#include <stack>
#include <thread>
#include <utility>
#include <vector>

#include "ConsoleHandler.h"

constexpr int MAX_ATTEMPTS = 12;

class Cell {
  bool left_wall;
  bool down_wall;
  bool right_wall;
  bool top_wall;

  int i, j;

 public:
  Cell(const int i, const int j);

  [[nodiscard]] bool has_no_walls_connected() const;

  void display_cell() const;

  void erase_left_wall();
  void erase_right_wall();
  void erase_top_wall();
  void erase_bottom_wall();
};

class Maze {
  int m_width, m_height;

  std::vector<std::vector<Cell>> maze;

  enum class directions { up, down, left, right };

  [[nodiscard]] bool invalid_coords(const int i, const int j) const;

  [[nodiscard]] bool invalid_coords(const std::pair<int, int>& pos) const;

  [[nodiscard]] bool has_neighbors(
      const std::pair<int, int>& pos,
      const std::vector<std::vector<bool>>& visited) const;

  static directions choose_direction(const int value);

  static std::pair<int, int> new_position(
      const std::pair<int, int>& current_pos,
      const directions& dir);

  static void erase_specific_wall(const directions& dir, Cell& cell);

 public:
  Maze(const int width, const int height);

  void generate();
};
