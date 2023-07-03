#include "ConsoleHandler.h"
#include "Maze.h"
#include "Solver.h"

int main() {
  int w, h;
  std::cout << "Dimensions (width, height) separated by space or newline: ";
  std::cin >> w >> h;
  Maze m(w, h);

  ConsoleHandler::clrscr();

  m.generate(false);
  m.make_maze_interesting(15);

  Solver::use_bfs(m);

  std::this_thread::sleep_for(std::chrono::seconds(3600));

  return 0;
}
