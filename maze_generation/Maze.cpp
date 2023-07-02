#include "Maze.h"

Cell::Cell(const int i, const int j)
    : left_wall(true),
      down_wall(true),
      right_wall(true),
      top_wall(true),
      i(2 * i + 2),
      j(2 * j + 1) {}

bool Cell::has_no_walls_connected() const {
  return left_wall && down_wall && right_wall && top_wall;
}

void Cell::display_cell() const {
  ConsoleHandler::draw_pixel(i, j, ' ', BACKGROUND_BLUE);

  if (!left_wall)
    ConsoleHandler::draw_pixel(i, j - 1, ' ', BACKGROUND_BLUE);
  if (!right_wall)
    ConsoleHandler::draw_pixel(i, j + 1, ' ', BACKGROUND_BLUE);
  if (!top_wall)
    ConsoleHandler::draw_pixel(i - 1, j, ' ', BACKGROUND_BLUE);
  if (!down_wall)
    ConsoleHandler::draw_pixel(i + 1, j, ' ', BACKGROUND_BLUE);
}

void Cell::erase_left_wall() {
  left_wall = false;
}

void Cell::erase_right_wall() {
  right_wall = false;
}

void Cell::erase_top_wall() {
  top_wall = false;
}

void Cell::erase_bottom_wall() {
  down_wall = false;
}

bool Maze::invalid_coords(const int i, const int j) const {
  return i < 0 || j < 0 || i >= m_height || j >= m_width;
}

bool Maze::invalid_coords(const std::pair<int, int>& pos) const {
  return invalid_coords(pos.first, pos.second);
}

bool Maze::has_neighbors(const std::pair<int, int>& pos,
                         const std::vector<std::vector<bool>>& visited) const {
  const auto [i, j] = pos;

  if (i > 0 && !visited[i - 1][j])
    return true;
  if (j > 0 && !visited[i][j - 1])
    return true;
  if (i < m_height - 1 && !visited[i + 1][j])
    return true;
  if (j < m_width - 1 && !visited[i][j + 1])
    return true;

  return false;
}

Maze::directions Maze::choose_direction(const int value) {
  if (value == 0)
    return directions::up;
  if (value == 1)
    return directions::down;
  if (value == 2)
    return directions::left;
  if (value == 3)
    return directions::right;

  throw std::invalid_argument("Invalid arg at choose_direction");
}

std::pair<int, int> Maze::new_position(const std::pair<int, int>& current_pos,
                                       const directions& dir) {
  const auto [i, j] = current_pos;

  if (dir == directions::down)
    return std::make_pair(i + 1, j);
  if (dir == directions::up)
    return std::make_pair(i - 1, j);
  if (dir == directions::right)
    return std::make_pair(i, j + 1);
  if (dir == directions::left)
    return std::make_pair(i, j - 1);

  throw std::invalid_argument("Invalid arg at new_position");
}

void Maze::erase_specific_wall(const directions& dir, Cell& cell) {
  if (dir == directions::down)
    cell.erase_bottom_wall();
  if (dir == directions::up)
    cell.erase_top_wall();
  if (dir == directions::right)
    cell.erase_right_wall();
  if (dir == directions::left)
    cell.erase_left_wall();
}

Maze::Maze(const int width, const int height)
    : m_width(width), m_height(height) {
  for (int i = 0; i < height; i++) {
    std::vector<Cell> temp_vec;
    temp_vec.reserve(width);
    for (int j = 0; j < width; j++) {
      temp_vec.emplace_back(i, j);
    }
    maze.push_back(temp_vec);
  }
}

void Maze::generate() {
  ConsoleHandler::resize_console(m_height * 2 + 12, m_width * 4 + 2);
  std::vector visited(m_height, std::vector(m_width, false));
  std::stack<std::pair<int, int>> maze_stack;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 3);

  maze_stack.push(std::make_pair(0, 0));
  visited[0][0] = true;

  while (!maze_stack.empty()) {
    const auto curr_pos = maze_stack.top();
    const auto [curr_i, curr_j] = curr_pos;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (!maze[curr_i][curr_j].has_no_walls_connected()) {
      maze[curr_i][curr_j].display_cell();
    }

    // Check if the current cell has any unvisited neighbors
    bool has_unvisited_neighbors = false;
    if (curr_i > 0 && !visited[curr_i - 1][curr_j])
      has_unvisited_neighbors = true;
    else if (curr_j > 0 && !visited[curr_i][curr_j - 1])
      has_unvisited_neighbors = true;
    else if (curr_i < m_height - 1 && !visited[curr_i + 1][curr_j])
      has_unvisited_neighbors = true;
    else if (curr_j < m_width - 1 && !visited[curr_i][curr_j + 1])
      has_unvisited_neighbors = true;

    if (has_unvisited_neighbors) {
      // Choose a random unvisited neighbor
      while (true) {
        const int random_index = dist(gen) % 4;
        directions random_direction = choose_direction(random_index);

        if (const auto [next_i, next_j] =
                new_position(curr_pos, random_direction);
            !invalid_coords(next_i, next_j) && !visited[next_i][next_j]) {
          // Remove the wall between the current cell and the chosen neighbor
          erase_specific_wall(random_direction, maze[curr_i][curr_j]);

          // Mark the chosen neighbor as visited and push it onto the stack
          visited[next_i][next_j] = true;
          maze_stack.push(std::make_pair(next_i, next_j));
          break;
        }
      }
    } else {
      // Backtrack if there are no unvisited neighbors
      maze_stack.pop();
    }
  }

  for (const auto& row : maze) {
    for (const auto& x : row)
      x.display_cell();
  }
}
