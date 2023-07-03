#pragma once

#include "Maze.h"

#include <functional>
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
      // std::this_thread::sleep_for(std::chrono::milliseconds(2));
      maze.get_maze()[cell_i][cell_j].change_color_and_repaint(BACKGROUND_RED);
      if (top_cell.get_position() == goal_cell) {
        grid[cell_i][cell_j].change_color_and_repaint(BACKGROUND_BLUE);
        break;
      }

      if (cell_j < m_w - 1 &&
          (top_cell.can_go_right() || grid[cell_i][cell_j + 1].can_go_left()) &&
          !visited[cell_i][cell_j + 1]) {
        visited[cell_i][cell_j + 1] = true;
        q.push(grid[cell_i][cell_j + 1]);
        parents[cell_i][cell_j + 1] = {cell_i, cell_j};
      }
      if (cell_i < m_h - 1 &&
          (top_cell.can_go_down() || grid[cell_i + 1][cell_j].can_go_up()) &&
          !visited[cell_i + 1][cell_j]) {
        visited[cell_i + 1][cell_j] = true;
        q.push(grid[cell_i + 1][cell_j]);
        parents[cell_i + 1][cell_j] = {cell_i, cell_j};
      }
      if (cell_j > 0 &&
          (top_cell.can_go_left() || grid[cell_i][cell_j - 1].can_go_right()) &&
          !visited[cell_i][cell_j - 1]) {
        visited[cell_i][cell_j - 1] = true;
        q.push(grid[cell_i][cell_j - 1]);
        parents[cell_i][cell_j - 1] = {cell_i, cell_j};
      }
      if (cell_i > 0 &&
          (top_cell.can_go_up() || grid[cell_i - 1][cell_j].can_go_down()) &&
          !visited[cell_i - 1][cell_j]) {
        visited[cell_i - 1][cell_j] = true;
        q.push(grid[cell_i - 1][cell_j]);
        parents[cell_i - 1][cell_j] = {cell_i, cell_j};
      }
    }

    int path_length = 0;
    auto current = goal_cell;
    while (current != std::make_pair(0, 0)) {
      path_length++;
      std::this_thread::sleep_for(std::chrono::milliseconds(5));

      const auto chosen_dir =
          determine_direction(parents[current.first][current.second], current);

      current = parents[current.first][current.second];

      grid[current.first][current.second].repaint_specific_wall(BACKGROUND_BLUE,
                                                                chosen_dir);
    }

    ConsoleHandler::gotoxy(2 * m_h + 3, 4);
    ConsoleHandler::set_fore_color(FOREGROUND_RED);
    std::cout << std::endl;
    std::cout << "BFS path length is " << path_length;
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
      const auto [cell_i, cell_j] = top_cell.get_position();

      // std::this_thread::sleep_for(std::chrono::milliseconds(2));
      maze.get_maze()[cell_i][cell_j].change_color_and_repaint(BACKGROUND_RED);

      q.pop();

      if (top_cell.get_position() == goal_cell) {
        grid[cell_i][cell_j].change_color_and_repaint(BACKGROUND_BLUE);
        break;
      }

      if (cell_j < m_w - 1 &&
          (top_cell.can_go_right() || grid[cell_i][cell_j + 1].can_go_left()) &&
          !visited[cell_i][cell_j + 1]) {
        visited[cell_i][cell_j + 1] = true;
        q.push(grid[cell_i][cell_j + 1]);
        parents[cell_i][cell_j + 1] = {cell_i, cell_j};
      }
      if (cell_i < m_h - 1 &&
          (top_cell.can_go_down() || grid[cell_i + 1][cell_j].can_go_up()) &&
          !visited[cell_i + 1][cell_j]) {
        visited[cell_i + 1][cell_j] = true;
        q.push(grid[cell_i + 1][cell_j]);
        parents[cell_i + 1][cell_j] = {cell_i, cell_j};
      }
      if (cell_j > 0 &&
          (top_cell.can_go_left() || grid[cell_i][cell_j - 1].can_go_right()) &&
          !visited[cell_i][cell_j - 1]) {
        visited[cell_i][cell_j - 1] = true;
        q.push(grid[cell_i][cell_j - 1]);
        parents[cell_i][cell_j - 1] = {cell_i, cell_j};
      }
      if (cell_i > 0 &&
          (top_cell.can_go_up() || grid[cell_i - 1][cell_j].can_go_down()) &&
          !visited[cell_i - 1][cell_j]) {
        visited[cell_i - 1][cell_j] = true;
        q.push(grid[cell_i - 1][cell_j]);
        parents[cell_i - 1][cell_j] = {cell_i, cell_j};
      }
    }

    int path_length = 0;
    auto current = goal_cell;
    while (current != std::make_pair(0, 0)) {
      path_length++;
      std::this_thread::sleep_for(std::chrono::milliseconds(5));

      const auto chosen_dir =
          determine_direction(parents[current.first][current.second], current);

      current = parents[current.first][current.second];

      grid[current.first][current.second].repaint_specific_wall(BACKGROUND_BLUE,
                                                                chosen_dir);
    }

    ConsoleHandler::gotoxy(2 * m_h + 3, 4);
    ConsoleHandler::set_fore_color(FOREGROUND_RED);
    std::cout << "                                       ";
    std::cout << "DFS path length is " << path_length;
  }

  struct AStarCell {
    int i;
    int j;
    int cost;
    int heuristic;

    AStarCell(const int i, const int j, const int cost, const int heuristic)
        : i(i), j(j), cost(cost), heuristic(heuristic) {}

    // Overload the '<' operator for priority queue
    bool operator<(const AStarCell& other) const {
      return (cost + heuristic) > (other.cost + other.heuristic);
    }
  };

  static void use_astar(Maze& maze) {
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
    std::vector costs(m_h, std::vector<int>(m_w, INT_MAX));

    std::priority_queue<AStarCell> pq;
    pq.push(AStarCell(0, 0, 0, heuristic_distance(0, 0, m_h - 1, m_w - 1)));

    while (!pq.empty()) {
      const auto top_cell = pq.top();
      pq.pop();

      // For visualization purposes
      const auto [cell_i, cell_j] = std::make_pair(top_cell.i, top_cell.j);
      // std::this_thread::sleep_for(std::chrono::milliseconds(2));
      maze.get_maze()[cell_i][cell_j].change_color_and_repaint(BACKGROUND_RED);
      if (top_cell.i == goal_cell.first && top_cell.j == goal_cell.second) {
        grid[cell_i][cell_j].change_color_and_repaint(BACKGROUND_BLUE);
        break;
      }

      if (visited[cell_i][cell_j])
        continue;

      visited[cell_i][cell_j] = true;

      // Update the cost to reach the current cell
      costs[cell_i][cell_j] = top_cell.cost;

      // Expand neighbors
      if (cell_j < m_w - 1 &&
          (grid[cell_i][cell_j].can_go_right() ||
           grid[cell_i][cell_j + 1].can_go_left()) &&
          !visited[cell_i][cell_j + 1]) {
        const int new_cost = top_cell.cost + 1;
        const int heuristic =
            heuristic_distance(cell_i, cell_j + 1, m_h - 1, m_w - 1);
        pq.push(AStarCell(cell_i, cell_j + 1, new_cost, heuristic));
        parents[cell_i][cell_j + 1] = {cell_i, cell_j};
      }
      if (cell_i < m_h - 1 &&
          (grid[cell_i][cell_j].can_go_down() ||
           grid[cell_i + 1][cell_j].can_go_up()) &&
          !visited[cell_i + 1][cell_j]) {
        const int new_cost = top_cell.cost + 1;
        const int heuristic =
            heuristic_distance(cell_i + 1, cell_j, m_h - 1, m_w - 1);
        pq.push(AStarCell(cell_i + 1, cell_j, new_cost, heuristic));
        parents[cell_i + 1][cell_j] = {cell_i, cell_j};
      }
      if (cell_j > 0 &&
          (grid[cell_i][cell_j].can_go_left() ||
           grid[cell_i][cell_j - 1].can_go_right()) &&
          !visited[cell_i][cell_j - 1]) {
        const int new_cost = top_cell.cost + 1;
        const int heuristic =
            heuristic_distance(cell_i, cell_j - 1, m_h - 1, m_w - 1);
        pq.push(AStarCell(cell_i, cell_j - 1, new_cost, heuristic));
        parents[cell_i][cell_j - 1] = {cell_i, cell_j};
      }
      if (cell_i > 0 &&
          (grid[cell_i][cell_j].can_go_up() ||
           grid[cell_i - 1][cell_j].can_go_down()) &&
          !visited[cell_i - 1][cell_j]) {
        const int new_cost = top_cell.cost + 1;
        const int heuristic =
            heuristic_distance(cell_i - 1, cell_j, m_h - 1, m_w - 1);
        pq.push(AStarCell(cell_i - 1, cell_j, new_cost, heuristic));
        parents[cell_i - 1][cell_j] = {cell_i, cell_j};
      }
    }

    int path_length = 0;

    auto current = goal_cell;
    while (current != std::make_pair(0, 0)) {
      path_length++;
      std::this_thread::sleep_for(std::chrono::milliseconds(5));

      const auto chosen_dir =
          determine_direction(parents[current.first][current.second], current);

      current = parents[current.first][current.second];

      grid[current.first][current.second].repaint_specific_wall(BACKGROUND_BLUE,
                                                                chosen_dir);
    }

    ConsoleHandler::gotoxy(2 * m_h + 3, 4);
    ConsoleHandler::set_fore_color(FOREGROUND_RED);
    std::cout << "                                       ";
    std::cout << "A* path length is " << path_length;
  }

  static int heuristic_distance(int i, int j, int goal_i, int goal_j) {
    return std::abs(i - goal_i) + std::abs(j - goal_j);
  }
};
