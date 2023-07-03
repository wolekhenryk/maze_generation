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

  int i, j, orig_i, orig_j;

  WORD color;

 public:
  Cell(const int i, const int j);

  enum class directions { up, down, left, right };

  [[nodiscard]] bool has_no_walls_connected() const;

  void display_cell() const;
  void change_color_and_repaint(const WORD new_color);

  void repaint_specific_wall(const WORD new_color, const directions& dir);

  void erase_left_wall();
  void erase_right_wall();
  void erase_top_wall();
  void erase_bottom_wall();

  [[nodiscard]] bool can_go_left() const;
  [[nodiscard]] bool can_go_right() const;
  [[nodiscard]] bool can_go_up() const;
  [[nodiscard]] bool can_go_down() const;

  [[nodiscard]] std::pair<int, int> get_position() const;
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

  [[nodiscard]] bool is_on_edge(const int i, const int j) const {
    return i == 0 || i == m_height - 1 || j == 0 || j == m_width - 1;
  }

 public:
  Maze(const int width, const int height);

  std::vector<std::vector<Cell>>& get_maze();

  [[nodiscard]] std::pair<int, int> get_size() const;

  void make_maze_interesting(const int percent);

  void generate(const bool is_visible);
};
