#include "ConsoleHandler.h"
#include "Maze.h"
#include "Solver.h"

int main() {
  ConsoleHandler::set_console_utf8_encoding();

  int w, h;
  std::cout << "Dimensions (width, height) separated by space or newline: ";
  std::cin >> w >> h;
  Maze m(w, h);

  ConsoleHandler::clrscr();

  m.generate(false);
  m.make_maze_interesting(50);

  Solver::use_astar(m);

  std::this_thread::sleep_for(std::chrono::seconds(3600));

  return 0;
}
