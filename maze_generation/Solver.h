#pragma once

#include "Maze.h"

#include <queue>
#include <stack>
#include <vector>

using dir = Cell::directions;

class Solver {
  static dir determine_direction(const std::pair<int, int>& curr_pos,
                                 const std::pair<int, int>& parent_pos) {
    const auto [curr_i, curr_j] = curr_pos;
    const auto [parent_i, parent_j] = parent_pos;

    if (curr_i > parent_i)
      return dir::up;
    if (curr_i < parent_i)
      return dir::down;
    if (curr_j > parent_j)
      return dir::left;
    if (curr_j < parent_j)
      return dir::right;

    throw std::invalid_argument("Invalid arg in det dir!");
  }

 public:
  static void use_bfs(Maze& maze) {
    for (auto& row : maze.get_maze()) {
      for (auto& x : row)
        x.change_color_and_repaint(BACKGROUND_RED | BACKGROUND_GREEN |
                                   BACKGROUND_BLUE);
    }

    const auto [m_w, m_h] = maze.get_size();
    const auto goal_cell = std::make_pair(m_h - 1, m_w - 1);

    auto& grid = maze.get_maze();
    std::vector visited(m_h, std::vector(m_w, false));
    std::vector parents(m_h, std::vector<std::pair<int, int>>(m_w));

    std::queue<Cell> q;
    q.push(grid[0][0]);
    visited[0][0] = true;

    while (!q.empty()) {
      // For visualization purposes
      const auto top_cell = q.front();
      q.pop();

      const auto [cell_i, cell_j] = top_cell.get_position();
      if (top_cell.get_position() == goal_cell) {
        grid[cell_i][cell_j].change_color_and_repaint(BACKGROUND_BLUE);
        break;
      }

      if (top_cell.can_go_right() && cell_j < m_w - 1 &&
          !visited[cell_i][cell_j + 1]) {
        visited[cell_i][cell_j + 1] = true;
        q.push(grid[cell_i][cell_j + 1]);
        parents[cell_i][cell_j + 1] = {cell_i, cell_j};
      }
      if (top_cell.can_go_down() && cell_i < m_h - 1 &&
          !visited[cell_i + 1][cell_j]) {
        visited[cell_i + 1][cell_j] = true;
        q.push(grid[cell_i + 1][cell_j]);
        parents[cell_i + 1][cell_j] = {cell_i, cell_j};
      }
      if (top_cell.can_go_left() && cell_j > 0 &&
          !visited[cell_i][cell_j - 1]) {
        visited[cell_i][cell_j - 1] = true;
        q.push(grid[cell_i][cell_j - 1]);
        parents[cell_i][cell_j - 1] = {cell_i, cell_j};
      }
      if (top_cell.can_go_up() && cell_i > 0 && !visited[cell_i - 1][cell_j]) {
        visited[cell_i - 1][cell_j] = true;
        q.push(grid[cell_i - 1][cell_j]);
        parents[cell_i - 1][cell_j] = {cell_i, cell_j};
      }
    }

    auto current = goal_cell;
    while (current != std::make_pair(0, 0)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(5));

      const auto chosen_dir =
          determine_direction(parents[current.first][current.second], current);

      current = parents[current.first][current.second];

      grid[current.first][current.second].repaint_specific_wall(BACKGROUND_BLUE,
                                                                chosen_dir);
    }
  }

  static void use_dfs(Maze& maze) {
    for (auto& row : maze.get_maze()) {
      for (auto& x : row)
        x.change_color_and_repaint(BACKGROUND_RED | BACKGROUND_GREEN |
                                   BACKGROUND_BLUE);
    }

    const auto [m_w, m_h] = maze.get_size();
    const auto goal_cell = std::make_pair(m_h - 1, m_w - 1);

    auto& grid = maze.get_maze();
    std::vector visited(m_h, std::vector(m_w, false));
    std::vector parents(m_h, std::vector<std::pair<int, int>>(m_w));

    std::stack<Cell> q;
    q.push(grid[0][0]);
    visited[0][0] = true;

    while (!q.empty()) {
      // For visualization purposes
      const auto top_cell = q.top();
      q.pop();

      const auto [cell_i, cell_j] = top_cell.get_position();
      if (top_cell.get_position() == goal_cell) {
        grid[cell_i][cell_j].change_color_and_repaint(BACKGROUND_BLUE);
        break;
      }

      if (top_cell.can_go_right() && cell_j < m_w - 1 &&
          !visited[cell_i][cell_j + 1]) {
        visited[cell_i][cell_j + 1] = true;
        q.push(grid[cell_i][cell_j + 1]);
        parents[cell_i][cell_j + 1] = {cell_i, cell_j};
      }
      if (top_cell.can_go_down() && cell_i < m_h - 1 &&
          !visited[cell_i + 1][cell_j]) {
        visited[cell_i + 1][cell_j] = true;
        q.push(grid[cell_i + 1][cell_j]);
        parents[cell_i + 1][cell_j] = {cell_i, cell_j};
      }
      if (top_cell.can_go_left() && cell_j > 0 &&
          !visited[cell_i][cell_j - 1]) {
        visited[cell_i][cell_j - 1] = true;
        q.push(grid[cell_i][cell_j - 1]);
        parents[cell_i][cell_j - 1] = {cell_i, cell_j};
      }
      if (top_cell.can_go_up() && cell_i > 0 && !visited[cell_i - 1][cell_j]) {
        visited[cell_i - 1][cell_j] = true;
        q.push(grid[cell_i - 1][cell_j]);
        parents[cell_i - 1][cell_j] = {cell_i, cell_j};
      }
    }

    auto current = goal_cell;
    while (current != std::make_pair(0, 0)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(5));

      const auto chosen_dir =
          determine_direction(parents[current.first][current.second], current);

      current = parents[current.first][current.second];

      grid[current.first][current.second].repaint_specific_wall(BACKGROUND_BLUE,
                                                                chosen_dir);
    }
  }
};
