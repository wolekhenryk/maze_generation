#include "ConsoleHandler.h"
#include "Maze.h"

constexpr int MAZE_WIDTH = 25;
constexpr int MAZE_HEIGHT = 15;

int main() {
  Maze m(30, 20);

  m.generate();

  std::this_thread::sleep_for(std::chrono::seconds(60));

  return 0;
}
