# Target 9 Game

Target 9 is a puzzle game where the objective is to change all the numbers in a grid to equal 9. You achieve this by making moves that involve increasing the numbers in the selected row and column by one. If a number reaches 9, it resets to 1 after the move. The game features a user-friendly interface with undo, redo, and hint options, and the difficulty can be adjusted with a slider.

<img width="519" height="649" alt="Image" src="https://github.com/user-attachments/assets/49a5b1dd-0cb3-4acf-bb21-b2da4192beda" />

## About the Game

The game presents a grid of numbers. When you select a cell, all numbers in that cell's row and column are incremented by one. The goal is to make every cell in the grid display the number 9. If a cell's value becomes 10 (i.e., it was 9 and was incremented), it wraps around to 1.

## Features

* Intuitive User Interface: Designed with user experience in mind.

* Undo/Redo Functionality: Allows players to reverse or re-apply moves.

* Hint System: Provides assistance by suggesting the next optimal move.

* Adjustable Difficulty: A slider allows players to set the game's initial complexity.

## Building the Project

The project uses CMake to manage the build process.

### Prerequisites (Windows)

To build on Windows, you will need:

MinGW-w64: Download and install MinGW-w64.

Qt6 Packages: Inside your MinGW-w64 installation, install the following packages:

`mingw-w64-x86_64-qt6-base`

`mingw-w64-x86_64-toolchain`

Environment Variables: Add the `bin` and `lib` directories of your MinGW-w64 installation to your system's PATH environment variable. For detailed instructions, refer to the VS Code guide on setting up C++ development with MinGW.

### General Build Instructions

1. Clone the repository:
  
    `git clone <repository_url>`
    
    `cd target-9-game`

2. Create a build directory:
  It's good practice to build outside the source directory.
  
    `mkdir build`
  
    `cd build`

3. Run CMake to configure the project:

    `cmake ..`

    If you have multiple generators (e.g., Visual Studio on Windows), you might need to specify one:
  
    `cmake .. -G "MinGW Makefiles" # For MinGW on Windows`

     or

     `cmake .. -G "Unix Makefiles" # For Linux/macOS`

5. Build the project:
  
    `cmake --build .`
  
    This command will compile the source code and create the executable in build directory.

## Testing

The project incorporates unit tests using the GTest framework.

To run the tests:

1. Ensure the project has been built (as per the "Building the Project" section).

2. Navigate to the build directory.

3. Run the test executable:

    `./GameLogicTestRunner # On Linux/macOS`
   
    or
   
    `./GameLogicTestRunner.exe # On Windows`

## Technologies Used

* C++: Core programming language.

* Qt6 Framework: Used for developing the cross-platform graphical user interface.

* CMake: Build system generator.

* GTest: Unit testing framework.
