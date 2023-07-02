#include "ConsoleHandler.h"
#include "Maze.h"

int main() {
  int w, h;
  std::cout << "Dimensions (width, height) separated by space or newline: ";
  std::cin >> w >> h;
  Maze m(w, h);

  ConsoleHandler::clrscr();

  m.generate();

  std::this_thread::sleep_for(std::chrono::seconds(3600));

  return 0;
}
