#include "Maze.h"

constexpr WORD BACKGROUND_WHITE =
    BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

Cell::Cell(const int i, const int j)
    : left_wall(true),
      down_wall(true),
      right_wall(true),
      top_wall(true),
      i(2 * i + 2),
      j(2 * j + 1),
      orig_i(i),
      orig_j(j),
      color(BACKGROUND_WHITE) {}

bool Cell::has_no_walls_connected() const {
  return left_wall && down_wall && right_wall && top_wall;
}

void Cell::display_cell() const {
  ConsoleHandler::draw_pixel(i, j, ' ', color);

  if (!left_wall)
    ConsoleHandler::draw_pixel(i, j - 1, ' ', color);
  if (!right_wall)
    ConsoleHandler::draw_pixel(i, j + 1, ' ', color);
  if (!top_wall)
    ConsoleHandler::draw_pixel(i - 1, j, ' ', color);
  if (!down_wall)
    ConsoleHandler::draw_pixel(i + 1, j, ' ', color);
}

void Cell::change_color_and_repaint(const WORD new_color) {
  color = new_color;
  display_cell();
}

void Cell::repaint_specific_wall(const WORD new_color, const directions& dir) {
  color = new_color;
  ConsoleHandler::draw_pixel(i, j, ' ', color);

  if (dir == directions::down)
    ConsoleHandler::draw_pixel(i + 1, j, ' ', color);
  if (dir == directions::left)
    ConsoleHandler::draw_pixel(i, j - 1, ' ', color);
  if (dir == directions::right)
    ConsoleHandler::draw_pixel(i, j + 1, ' ', color);
  if (dir == directions::up)
    ConsoleHandler::draw_pixel(i - 1, j, ' ', color);
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

bool Cell::can_go_left() const {
  return !left_wall;
}

bool Cell::can_go_right() const {
  return !right_wall;
}

bool Cell::can_go_up() const {
  return !top_wall;
}

bool Cell::can_go_down() const {
  return !down_wall;
}

std::pair<int, int> Cell::get_position() const {
  return std::make_pair(orig_i, orig_j);
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

std::vector<std::vector<Cell>>& Maze::get_maze() {
  return maze;
}

std::pair<int, int> Maze::get_size() const {
  return std::make_pair(m_width, m_height);
}

void Maze::make_maze_interesting(const int percent) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution i_random(0, m_height - 1);
  std::uniform_int_distribution j_random(0, m_width - 1);
  std::uniform_int_distribution random_w(0, 3);

  const auto total_count = percent * m_width * m_height;
  const auto altered_walls = total_count / 100;

  for (int i = 0; i < altered_walls; i++) {
    const auto random_wall = random_w(gen);

    const auto i_r = i_random(gen);
    const auto j_r = j_random(gen);

    if (is_on_edge(i_r, j_r))
      continue;

    if (random_wall == 0) {
      maze[i_r][j_r].erase_bottom_wall();
      maze[i_r + 1][j_r].erase_top_wall();
    }
    if (random_wall == 1) {
      maze[i_r][j_r].erase_left_wall();
      maze[i_r][j_r - 1].erase_right_wall();
    }
    if (random_wall == 2) {
      maze[i_r][j_r].erase_right_wall();
      maze[i_r][j_r + 1].erase_left_wall();
    }
    if (random_wall == 3) {
      maze[i_r][j_r].erase_top_wall();
      maze[i_r - 1][j_r].erase_bottom_wall();
    }

    maze[i_r][j_r].display_cell();
  }
}

void Maze::generate(const bool is_visible) {
  ConsoleHandler::resize_console(m_height * 2 + 2, m_width * 4 + 2);
  std::vector visited(m_height, std::vector(m_width, false));
  std::stack<std::pair<int, int>> maze_stack;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution dist(0, 3);

  maze_stack.push(std::make_pair(0, 0));
  visited[0][0] = true;

  while (!maze_stack.empty()) {
    const auto curr_pos = maze_stack.top();
    const auto [curr_i, curr_j] = curr_pos;
    if (!maze[curr_i][curr_j].has_no_walls_connected() && is_visible) {
      maze[curr_i][curr_j].display_cell();
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
