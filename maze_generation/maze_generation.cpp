#include "ConsoleHandler.h"
#include "Maze.h"

constexpr int MAZE_WIDTH = 25;
constexpr int MAZE_HEIGHT = 15;

int main() {
  Maze m(20, 20);

  // m.display();
  m.generate();

  std::this_thread::sleep_for(std::chrono::seconds(60));

  return 0;
}
