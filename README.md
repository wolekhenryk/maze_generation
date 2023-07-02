
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


## Screenshots

![Maze of size 30x30](/examples/maze_1.png)
![Maze of size 50x30](/examples/maze_2.png)

