
# maze_generation

This project aims to demonstrate the capabilities of stack-based backtracking. I decided to visualize it in the best way in my view - generating complex, complete and high-quality mazes.




## Installation

Requirements:
- Windows OS (this project is platform-specific)
- C++ compiler, preferably **MSVC C++17** or higher

Instructions:
```bash
  1. Download the repo on your machine
  2. Open visual studio and choose File->Open->Project/Solution
```


    
## Documentation

This is a console application. After compiling and running, the user is asked for 2 32-bit signed integers. The first one denotes the width of the maze, and the other denotes the height. Please note that with font size 18 mazes with height exceeding 30 will often not fit on the screen. The program is specifically designed to sleep for 10 milliseconds at each stack's iteration to beautifully visualize the maze creation.

## Solver

Recently a solver was added. It performs a stunning visualization, marking red cells which have been visited, and marking green the shortest diagonal path. I have plans on extending the options of algorithm choices. As of today, BFS and DFS are avaibale.


## Future plans
I intend to add the possibility to solve each maze which has been created. This opens up a chance to perform benchmarking between 4 most commonly used pathfinding algorithms:
- Breadth-first search
- Depth-first search
- Dijkstra's algorithm
- A* algorithm

## Screenshots

These screenshots represent solved mazes using Breadth-first search

![Maze of size 50x30](/examples/maze_6.png)
![Solved maze](/examples/maze_5.png)
